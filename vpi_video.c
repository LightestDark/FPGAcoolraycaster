#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vpi_user.h"

static FILE *video_pipe = NULL;

static int vpi_video_start_calltf(char *user_data)
{
    vpiHandle systf_handle = vpi_handle(vpiSysTfCall, NULL);
    vpiHandle arg_iter = vpi_iterate(vpiArgument, systf_handle);
    s_vpi_value val;
    int width = 0;
    int height = 0;
    int fps = 0;
    const char *filename = "raycast.mp4";
    char command[512];

    if (!arg_iter) {
        vpi_printf("$vpi_video_start expects 4 arguments\n");
        return 0;
    }

    val.format = vpiIntVal;
    vpi_get_value(vpi_scan(arg_iter), &val);
    width = val.value.integer;

    vpi_get_value(vpi_scan(arg_iter), &val);
    height = val.value.integer;

    vpi_get_value(vpi_scan(arg_iter), &val);
    fps = val.value.integer;

    val.format = vpiStringVal;
    vpi_get_value(vpi_scan(arg_iter), &val);
    if (val.value.str && val.value.str[0] != '\0') {
        filename = val.value.str;
    }

    if (video_pipe) {
        return 0;
    }

    if (width <= 0 || height <= 0 || fps <= 0) {
        vpi_printf("$vpi_video_start invalid args: %dx%d @ %d fps\n", width, height, fps);
        return 0;
    }

    snprintf(command, sizeof(command),
        "ffmpeg -y -f rawvideo -pix_fmt rgb24 -s %dx%d -r %d -i - -vf format=yuv420p %s",
        width, height, fps, filename);

    video_pipe = popen(command, "w");
    if (!video_pipe) {
        vpi_printf("$vpi_video_start failed to open ffmpeg pipe\n");
        return 0;
    }

    vpi_printf("$vpi_video_start %dx%d @ %d fps -> %s\n", width, height, fps, filename);

    return 0;
}

static int vpi_video_pixel_calltf(char *user_data)
{
    vpiHandle systf_handle = vpi_handle(vpiSysTfCall, NULL);
    vpiHandle arg_iter = vpi_iterate(vpiArgument, systf_handle);
    s_vpi_value val;
    unsigned char rgb[3];

    if (!video_pipe || !arg_iter) {
        return 0;
    }

    val.format = vpiIntVal;
    vpi_get_value(vpi_scan(arg_iter), &val);
    rgb[0] = (unsigned char)val.value.integer;

    vpi_get_value(vpi_scan(arg_iter), &val);
    rgb[1] = (unsigned char)val.value.integer;

    vpi_get_value(vpi_scan(arg_iter), &val);
    rgb[2] = (unsigned char)val.value.integer;

    fwrite(rgb, 1, sizeof(rgb), video_pipe);
    return 0;
}

static int vpi_video_end_calltf(char *user_data)
{
    if (video_pipe) {
        fflush(video_pipe);
        pclose(video_pipe);
        video_pipe = NULL;
        vpi_printf("$vpi_video_end complete\n");
    }
    return 0;
}

void register_vpi_video_tasks(void)
{
    s_vpi_systf_data tf_data;

    memset(&tf_data, 0, sizeof(tf_data));
    tf_data.type = vpiSysTask;
    tf_data.tfname = "$vpi_video_start";
    tf_data.calltf = vpi_video_start_calltf;
    vpi_register_systf(&tf_data);

    memset(&tf_data, 0, sizeof(tf_data));
    tf_data.type = vpiSysTask;
    tf_data.tfname = "$vpi_video_pixel";
    tf_data.calltf = vpi_video_pixel_calltf;
    vpi_register_systf(&tf_data);

    memset(&tf_data, 0, sizeof(tf_data));
    tf_data.type = vpiSysTask;
    tf_data.tfname = "$vpi_video_end";
    tf_data.calltf = vpi_video_end_calltf;
    vpi_register_systf(&tf_data);
}

void (*vlog_startup_routines[])(void) = {
    register_vpi_video_tasks,
    0
};
