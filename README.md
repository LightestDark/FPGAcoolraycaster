# FPGA VGA Raycaster

Verilog VGA raycaster with a 640x480@60Hz output, fixed-point ray traversal, simple wall texturing, distance fog, and auto-demo motion. The entire design is consolidated in `raycaster.v`, with standalone testbenches for simulation and demo capture.

## Features
- 640x480 VGA timing generator (`vga_sync`)
- 256-entry sin/cos LUT (`sin_cos_lut`)
- 32x32 map ROM (`map_rom`)
- Fixed-point ray marcher (`ray_dda`)
- Integrated VGA raycast demo (`vga_raycast_demo`) with shading, textures, fog, and auto-demo mode
- Testbenches for timing, LUT/map, ray march, auto-demo, frame dump, video sequence, and VPI keyboard input

## Repository layout
- `raycaster.v` — All RTL modules (timing, LUTs, ray marcher, and top-level demo).
- `tb_*.v` — Simulation testbenches and demos.
- `vpi_keyboard.c` — VPI module for keyboard input in Icarus Verilog.
- `vpi_video.c` — VPI module for piping frames to ffmpeg.
- `sim_verilator_capture.cpp` — Verilator + SDL live viewer and ffmpeg capture.
- `run_raycaster_demo.sh` — Icarus VPI demo + ffmpeg capture helper.
- `run_raycaster_verilator.sh` — Verilator/SDL capture helper.
- `PROJECT_PROGRESS_REPORT.txt` — Detailed progress report and verification notes.

## Requirements
Core simulation:
- Icarus Verilog (`iverilog`, `vvp`)
- GTKWave (optional) for waveform viewing

Optional extras:
- `gcc` for building VPI modules
- `ffmpeg` for MP4 capture
- `verilator` and `libsdl2-dev` for the Verilator/SDL demo

## Quick start (simulation)
From the repository root:

```sh
iverilog -o vga_sync.vvp raycaster.v tb_vga_sync.v
vvp vga_sync.vvp

iverilog -o lut_map.vvp raycaster.v tb_lut_map.v
vvp lut_map.vvp

iverilog -o ray_dda.vvp raycaster.v tb_ray_dda.v
vvp ray_dda.vvp

iverilog -o vga_raycast_demo.vvp raycaster.v tb_vga_raycast_demo.v
vvp vga_raycast_demo.vvp

iverilog -o vga_judge_demo.vvp raycaster.v tb_vga_judge_demo.v
vvp vga_judge_demo.vvp
```

## Demo outputs
### Auto-demo (no manual input)
```sh
iverilog -o vga_judge_demo.vvp raycaster.v tb_vga_judge_demo.v
vvp vga_judge_demo.vvp
```

### Render a single frame to PPM
```sh
iverilog -o vga_frame_dump.vvp raycaster.v tb_vga_frame_dump.v
vvp vga_frame_dump.vvp
# Produces judge_frame.ppm
```

### Capture a short MP4 sequence via VPI + ffmpeg
```sh
gcc -shared -fPIC -I/usr/include/iverilog -o vpi_video.vpi vpi_video.c
iverilog -g2012 -o vga_frame_sequence.vvp raycaster.v tb_vga_frame_sequence.v
vvp -M. -m vpi_video vga_frame_sequence.vvp
# Produces raycast.mp4
```

### Live keyboard demo via VPI (Icarus)
```sh
gcc -shared -fPIC -I/usr/include/iverilog -o vpi_keyboard.vpi vpi_keyboard.c
iverilog -g2012 -o vga_vpi_demo.vvp raycaster.v tb_vga_vpi_demo.v
vvp -M. -m vpi_keyboard vga_vpi_demo.vvp
```

Controls (Icarus VPI):
- **W/S**: forward/back
- **Q/E**: turn left/right
- **A/D**: strafe left/right
- **ESC**: exit

### Verilator + SDL live viewer (optional)
```sh
./run_raycaster_verilator.sh
```

Controls (Verilator SDL capture):
- **W/S**: forward/back
- **A/D**: turn left/right
- **Q/E**: strafe left/right
- **ESC**: exit

Note: The Icarus VPI demo and the Verilator SDL demo use different key mappings; follow the controls listed for the demo you run.

## Notes
- `run_raycaster_demo.sh` and `run_raycaster_verilator.sh` use a hardcoded working directory. Update the `cd` path to your local clone or run the commands manually as shown above.
- The demo’s top-level module is `vga_raycast_demo` in `raycaster.v`.
