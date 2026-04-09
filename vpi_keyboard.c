#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include "vpi_user.h"

static struct termios orig_termios;
static int termios_ready = 0;
static int last_mask = 0;

static void restore_termios(void) {
    if (termios_ready) {
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
        termios_ready = 0;
    }
}

static void init_termios(void) {
    struct termios t;
    if (termios_ready) return;
    if (tcgetattr(STDIN_FILENO, &orig_termios) == 0) {
        t = orig_termios;
        t.c_lflag &= ~(ICANON | ECHO);
        t.c_cc[VMIN] = 0;
        t.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
        termios_ready = 1;
        atexit(restore_termios);
    }
}

static int read_keys(void) {
    fd_set rfds;
    struct timeval tv;
    char ch;
    int mask = 0;

    init_termios();

    while (1) {
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        if (select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv) <= 0) {
            break;
        }
        if (read(STDIN_FILENO, &ch, 1) != 1) {
            break;
        }
        // Map keys: W/S forward/back, A/D strafe, Q/E turn.
        if (ch == 'w' || ch == 'W') mask |= 1 << 0;
        if (ch == 's' || ch == 'S') mask |= 1 << 1;
        if (ch == 'q' || ch == 'Q') mask |= 1 << 2;
        if (ch == 'e' || ch == 'E') mask |= 1 << 3;
        if (ch == 'a' || ch == 'A') mask |= 1 << 4;
        if (ch == 'd' || ch == 'D') mask |= 1 << 5;
        if (ch == 27) { // ESC
            mask |= 1 << 6;
        }
    }
    return mask;
}

static PLI_INT32 kbd_calltf(char *user_data) {
    int mask = read_keys();
    if (mask != 0) {
        last_mask = mask;
    } else {
        // Clear after one cycle if no new keypress.
        last_mask = 0;
    }

    vpiHandle systf = vpi_handle(vpiSysTfCall, NULL);
    vpiHandle arg = vpi_iterate(vpiArgument, systf);
    if (arg) {
        vpiHandle arg_h = vpi_scan(arg);
        s_vpi_value val;
        val.format = vpiIntVal;
        val.value.integer = last_mask;
        vpi_put_value(arg_h, &val, NULL, vpiNoDelay);
    }
    return 0;
}

static void kbd_register(void) {
    s_vpi_systf_data tf_data;
    tf_data.type = vpiSysTask;
    tf_data.tfname = "$kbd";
    tf_data.calltf = kbd_calltf;
    tf_data.compiletf = 0;
    tf_data.sizetf = 0;
    tf_data.user_data = 0;
    vpi_register_systf(&tf_data);
}

void (*vlog_startup_routines[])(void) = {
    kbd_register,
    0
};
