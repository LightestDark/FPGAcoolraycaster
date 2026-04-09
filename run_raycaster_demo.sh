#!/usr/bin/env bash
set -euo pipefail

cd /home/ak/verilog-project

rm -f frame_*.ppm raycast.mp4

# Build VPI keyboard module.
gcc -shared -fPIC -I/usr/include/iverilog -o vpi_keyboard.vpi vpi_keyboard.c

# Build VPI video pipe module.
gcc -shared -fPIC -I/usr/include/iverilog -o vpi_video.vpi vpi_video.c

# Live keyboard demo (ESC exits).
iverilog -g2012 -o vga_vpi_demo.vvp raycaster.v tb_vga_vpi_demo.v
vvp -M. -m vpi_keyboard vga_vpi_demo.vvp || true

# Generate video via VPI pipe into ffmpeg.
if ! command -v ffmpeg >/dev/null 2>&1; then
  echo "ffmpeg not found; cannot generate raycast.mp4"
  exit 1
fi

iverilog -g2012 -o vga_frame_sequence.vvp raycaster.v tb_vga_frame_sequence.v
vvp -M. -m vpi_video vga_frame_sequence.vvp

if [[ -f raycast.mp4 ]]; then
  if command -v xdg-open >/dev/null 2>&1; then
    xdg-open raycast.mp4 >/dev/null 2>&1 || true
  fi
  if command -v mpv >/dev/null 2>&1; then
    mpv --vo=x11 --hwdec=no raycast.mp4 >/dev/null 2>&1 || true
  fi
else
  echo "raycast.mp4 was not created; check ffmpeg output above."
fi
