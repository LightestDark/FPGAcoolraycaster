#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <SDL2/SDL.h>

#include "Vvga_raycast_demo.h"
#include "verilated.h"

static FILE *open_ffmpeg_pipe(int width, int height, int fps, const char *out_name)
{
    char command[512];
    std::snprintf(command, sizeof(command),
        "ffmpeg -hide_banner -loglevel error -nostats -y -f rawvideo -pix_fmt rgb24 -s %dx%d -r %d -i - -vf format=yuv420p -preset ultrafast -threads 0 %s",
        width, height, fps, out_name);
    return popen(command, "w");
}

static struct termios saved_termios;

static void set_raw_terminal(bool enable)
{
    if (enable) {
        struct termios raw;
        tcgetattr(STDIN_FILENO, &saved_termios);
        raw = saved_termios;
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    }
}

static int read_key()
{
    unsigned char c = 0;
    int n = read(STDIN_FILENO, &c, 1);
    if (n == 1) {
        return c;
    }
    return -1;
}

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);

    const char *env_frames = std::getenv("CAP_FRAMES");
    const char *env_fps = std::getenv("CAP_FPS");
    const char *env_shift = std::getenv("CAP_SAMPLE_SHIFT");

    int frames = env_frames ? std::atoi(env_frames) : 900;
    int fps = env_fps ? std::atoi(env_fps) : 60;
    int sample_shift = env_shift ? std::atoi(env_shift) : 0; // 0=640x480, 1=320x240, 2=160x120

    if (frames <= 0) frames = 600;
    if (fps <= 0) fps = 60;
    if (sample_shift < 0) sample_shift = 0;
    if (sample_shift > 3) sample_shift = 3;

    const int cap_w = 640 >> sample_shift;
    const int cap_h = 480 >> sample_shift;

    Vvga_raycast_demo top;
    vluint64_t sim_time = 0;

    top.clk_25 = 0;
    top.rst = 1;
    top.move_fwd = 0;
    top.move_back = 0;
    top.turn_left = 0;
    top.turn_right = 0;
    top.strafe_left = 0;
    top.strafe_right = 0;
    top.manual_enable = 1;

    set_raw_terminal(true);

    FILE *pipe = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;
    std::vector<unsigned char> frame_buf(static_cast<size_t>(cap_w) * cap_h * 3);
    int frame_count = 0;
    int key_hold = 0;
    int key_code = -1;
    int pixel_index = 0;
    bool quit = false;

    std::printf("Controls: W/S forward/back, A/D turn, Q/E strafe, ESC to stop\n");
    std::printf("Capture: %d frames @ %d fps, sample_shift=%d (%dx%d)\n", frames, fps, sample_shift, cap_w, cap_h);

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        window = SDL_CreateWindow("raycaster live",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            cap_w * 2, cap_h * 2, 0);
        if (window) {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer) {
                SDL_RenderSetLogicalSize(renderer, cap_w, cap_h);
                texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
                    SDL_TEXTUREACCESS_STREAMING, cap_w, cap_h);
            }
        }
    } else {
        std::fprintf(stderr, "SDL init failed: %s\n", SDL_GetError());
    }

    const int reset_cycles = 10;
    for (int i = 0; i < reset_cycles; ++i) {
        top.clk_25 = !top.clk_25;
        top.eval();
        sim_time++;
    }
    top.rst = 0;

    while (!Verilated::gotFinish() && frame_count < frames && !quit) {
        top.clk_25 = 1;
        top.eval();

        if (top.hc == 0 && top.vc == 0) {
            if (frame_count == 0) {
                pipe = open_ffmpeg_pipe(cap_w, cap_h, fps, "raycast.mp4");
                if (!pipe) {
                    std::fprintf(stderr, "Failed to open ffmpeg pipe\n");
                    set_raw_terminal(false);
                    return 1;
                }
            }
            pixel_index = 0;
        }

        if (renderer) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                    break;
                }
            }
        }

        // Poll keyboard once per frame to update controls.
        if (top.hc == 0 && top.vc == 0) {
            int key = -1;
            while (true) {
                int next_key = read_key();
                if (next_key == -1) {
                    break;
                }
                key = next_key;
            }
            if (key == 27) {
                break;
            }
            if (key >= 'A' && key <= 'Z') {
                key = key - 'A' + 'a';
            }
            if (key != -1) {
                key_code = key;
                key_hold = 5;
                std::printf("key '%c'\n", key_code);
            }
            if (key_hold > 0) {
                key_hold--;
            }
            top.move_fwd = (key_hold > 0) && (key_code == 'w');
            top.move_back = (key_hold > 0) && (key_code == 's');
            top.turn_left = (key_hold > 0) && (key_code == 'a');
            top.turn_right = (key_hold > 0) && (key_code == 'd');
            top.strafe_left = (key_hold > 0) && (key_code == 'q');
            top.strafe_right = (key_hold > 0) && (key_code == 'e');
        }

        if (top.hc < 640 && top.vc < 480) {
            if (((top.hc & ((1 << sample_shift) - 1)) == 0) &&
                ((top.vc & ((1 << sample_shift) - 1)) == 0)) {
                unsigned char rgb[3];
                rgb[0] = static_cast<unsigned char>(top.vga_r * 17);
                rgb[1] = static_cast<unsigned char>(top.vga_g * 17);
                rgb[2] = static_cast<unsigned char>(top.vga_b * 17);
                if (pipe) {
                    std::fwrite(rgb, 1, sizeof(rgb), pipe);
                }
                if (pixel_index + 2 < static_cast<int>(frame_buf.size())) {
                    frame_buf[static_cast<size_t>(pixel_index + 0)] = rgb[0];
                    frame_buf[static_cast<size_t>(pixel_index + 1)] = rgb[1];
                    frame_buf[static_cast<size_t>(pixel_index + 2)] = rgb[2];
                }
                pixel_index += 3;
                if (texture && pixel_index == cap_w * cap_h * 3) {
                    SDL_UpdateTexture(texture, nullptr, frame_buf.data(), cap_w * 3);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
                    SDL_RenderPresent(renderer);
                }
            }
        }

        if (top.hc == 0 && top.vc == 0) {
            if (frame_count < frames) {
                frame_count++;
            }
        }

        top.clk_25 = 0;
        top.eval();
        sim_time++;
    }

    if (pipe) {
        std::fflush(pipe);
        pclose(pipe);
    }

    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();

    set_raw_terminal(false);

    std::printf("PASS verilator wrote %d frames\n", frame_count);
    return 0;
}
