#!/usr/bin/env bash
set -euo pipefail

cd /home/ak/verilog-project

if ! command -v verilator >/dev/null 2>&1; then
  echo "verilator not found; install it (e.g. sudo apt install verilator)"
  exit 1
fi

if ! command -v ffmpeg >/dev/null 2>&1; then
  echo "ffmpeg not found; install it (e.g. sudo apt install ffmpeg)"
  exit 1
fi

rm -f raycast.mp4

verilator -cc raycaster.v --top-module vga_raycast_demo \
  --exe sim_verilator_capture.cpp --build

./obj_dir/Vvga_raycast_demo

if [[ -f raycast.mp4 ]]; then
  if command -v xdg-open >/dev/null 2>&1; then
    xdg-open raycast.mp4 >/dev/null 2>&1 || true
  fi
  if command -v mpv >/dev/null 2>&1; then
    mpv --vo=x11 --hwdec=no raycast.mp4 >/dev/null 2>&1 || true
  fi
else
  echo "raycast.mp4 was not created"
fi
