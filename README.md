# FPGA VGA Raycaster

A Doom-style raycaster implemented in Verilog, targeting FPGA hardware with a 640×480 VGA output at 60 Hz. The project is fully simulatable with [Icarus Verilog](http://iverilog.icarus.com/) and viewable in [GTKWave](http://gtkwave.sourceforge.net/). An optional Verilator + SDL2 path produces a real-time rendered video file.

---

## Features

- **640×480 @ 60 Hz VGA timing** – correct hsync/vsync pulses generated in hardware.
- **Fixed-point sin/cos LUT** – 256-entry table in Q1.14 format for fast direction vectors.
- **32×32 tile map ROM** – configurable maze with interior corridors and open areas.
- **DDA ray-march core** – marches up to 320 steps, reports first wall hit tile and distance.
- **Full per-column rendering** – wall slice height derived from ray distance, drawn each pixel clock.
- **Wall shading & distance fog** – side-based shading, checker-pattern texturing, fog falloff.
- **Sky and floor gradients** – drawn above and below the wall slice.
- **Movement controls** – forward/back, turn left/right, strafe left/right.
- **Auto-demo mode** – camera moves autonomously when no controls are pressed (great for demos/judges).
- **Live keyboard demo via VPI** – real-time input using an Icarus VPI module.
- **Frame export** – single PPM frame dump or a 1 000-frame PPM sequence, optionally encoded to MP4 with ffmpeg.
- **Verilator + SDL2 path** – compile the design with Verilator for real-time SDL2 preview and MP4 capture.

---

## Repository Structure

| File | Purpose |
|------|---------|
| `raycaster.v` | All synthesisable Verilog modules in one file |
| `tb_vga_sync.v` | Testbench – VGA timing |
| `tb_lut_map.v` | Testbench – sin/cos LUT + map ROM |
| `tb_ray_dda.v` | Testbench – DDA ray-march core |
| `tb_vga_raycast_demo.v` | Testbench – integrated rendering demo |
| `tb_vga_judge_demo.v` | Testbench – autonomous movement proof |
| `tb_vga_frame_dump.v` | Testbench – single PPM frame export |
| `tb_vga_frame_sequence.v` | Testbench – 1 000-frame PPM sequence |
| `tb_vga_vpi_demo.v` | Testbench – live VPI keyboard demo |
| `vpi_keyboard.c` | VPI module – real-time keyboard input |
| `vpi_video.c` | VPI module – video pipe to ffmpeg |
| `sim_verilator_capture.cpp` | Verilator harness with SDL2 + ffmpeg output |
| `run_raycaster_demo.sh` | Helper – build and run VPI live demo + frame sequence |
| `run_raycaster_verilator.sh` | Helper – build and run Verilator + SDL2 demo |
| `PROJECT_PROGRESS_REPORT.txt` | Detailed engineering notes and verified simulation outputs |

### Module Dependency Graph

```
tb_vga_sync.v            → raycaster.v : vga_sync
tb_lut_map.v             → raycaster.v : sin_cos_lut, map_rom
tb_ray_dda.v             → raycaster.v : ray_dda
tb_vga_raycast_demo.v    → raycaster.v : vga_raycast_demo
                                       → vga_sync, sin_cos_lut, ray_dda
tb_vga_judge_demo.v      → raycaster.v : vga_raycast_demo (auto-demo mode)
```

---

## Prerequisites

| Tool | Purpose |
|------|---------|
| `iverilog` | Icarus Verilog compiler |
| `vvp` | Icarus simulation runner |
| `gtkwave` | Waveform viewer (optional) |
| `gcc` | Build VPI shared libraries |
| `verilator` | Alternative high-speed simulation (optional) |
| `ffmpeg` | MP4 encoding (optional) |
| `libsdl2-dev` | Real-time SDL2 preview with Verilator (optional) |

Install on Debian/Ubuntu:

```bash
sudo apt install iverilog gtkwave gcc verilator ffmpeg libsdl2-dev
```

---

## Quick Start – Icarus Verilog Simulations

### 1. VGA timing test

```bash
iverilog -o vga_sync.vvp raycaster.v tb_vga_sync.v
vvp vga_sync.vvp
gtkwave vga_sync.vcd          # optional
```

### 2. Sin/cos LUT + map ROM test

```bash
iverilog -o lut_map.vvp raycaster.v tb_lut_map.v
vvp lut_map.vvp
gtkwave lut_map.vcd           # optional
```

### 3. DDA ray-march test

```bash
iverilog -o ray_dda.vvp raycaster.v tb_ray_dda.v
vvp ray_dda.vvp
gtkwave ray_dda.vcd           # optional
```

### 4. Integrated VGA raycast demo

```bash
iverilog -o vga_raycast_demo.vvp raycaster.v tb_vga_raycast_demo.v
vvp vga_raycast_demo.vvp
gtkwave vga_raycast_demo.vcd  # optional
```

### 5. Auto-demo / judge test

```bash
iverilog -o vga_judge_demo.vvp raycaster.v tb_vga_judge_demo.v
vvp vga_judge_demo.vvp
# Expected output: PASS tb_vga_judge_demo player=(574,393) angle=6
```

### 6. Single-frame PPM export

```bash
iverilog -o vga_frame_dump.vvp raycaster.v tb_vga_frame_dump.v
vvp vga_frame_dump.vvp
# Produces: judge_frame.ppm (640×480 rendered scene)
```

### 7. 1 000-frame PPM sequence

```bash
iverilog -o vga_frame_sequence.vvp raycaster.v tb_vga_frame_sequence.v
vvp vga_frame_sequence.vvp
# Produces: frame_0000.ppm … frame_0999.ppm

# Optional: encode to video
ffmpeg -framerate 8 -i frame_%04d.ppm -vf format=yuv420p raycast.mp4
```

---

## Live Keyboard Demo (VPI)

Controls: **W/S** forward/back · **Q/E** turn · **A/D** strafe · **ESC** quit

```bash
gcc -shared -fPIC -I/usr/include/iverilog -o vpi_keyboard.vpi vpi_keyboard.c
iverilog -g2012 -o vga_vpi_demo.vvp raycaster.v tb_vga_vpi_demo.v
vvp -M. -m vpi_keyboard vga_vpi_demo.vvp
```

Or use the helper script (also generates `raycast.mp4` via ffmpeg if available):

```bash
bash run_raycaster_demo.sh
```

---

## Verilator + SDL2 Real-Time Demo

```bash
bash run_raycaster_verilator.sh
```

This compiles the design with Verilator, links against SDL2 for real-time display, and pipes output through ffmpeg to produce `raycast.mp4`.

---

## Smoke Test (Full Regression)

Run all five core simulations in one shot:

```bash
iverilog -o vga_sync.vvp          raycaster.v tb_vga_sync.v          && vvp vga_sync.vvp
iverilog -o lut_map.vvp           raycaster.v tb_lut_map.v           && vvp lut_map.vvp
iverilog -o ray_dda.vvp           raycaster.v tb_ray_dda.v           && vvp ray_dda.vvp
iverilog -o vga_raycast_demo.vvp  raycaster.v tb_vga_raycast_demo.v  && vvp vga_raycast_demo.vvp
iverilog -o vga_judge_demo.vvp    raycaster.v tb_vga_judge_demo.v    && vvp vga_judge_demo.vvp
```

All five should print `PASS`.

---

## Verified Simulation Outputs

**Sin/Cos LUT**

| Angle | sin | cos |
|------:|----:|----:|
| 0 | 0 | 16384 |
| 64 | 16384 | 0 |
| 128 | 0 | −16384 |
| 192 | −16384 | 0 |

**Ray DDA from (1.5, 1.5)**

| Direction | Hit tile | Steps | Side |
|-----------|----------|------:|-----:|
| East | (15, 1) | 88 | 0 |
| South | (1, 15) | 88 | 1 |
| North-West | (0, 0) | 9 | 1 |

---

## Architecture Overview

```
Player state (position, angle)
        │
        ▼
 sin_cos_lut  ──►  direction vectors (Q1.14)
        │
        ▼
   ray_dda    ──►  wall hit tile + step distance
        │
        ▼
 Column shader ──►  wall height, shading, fog, texture
        │
        ▼
  vga_sync    ──►  640×480 hsync / vsync / RGB output
```

All arithmetic uses fixed-point integers (Q8.8 for positions, Q1.14 for trig) – no floating-point units required for synthesis.

---

## Planned Enhancements

- Per-column pipelined ray engine for true cycle-accurate synthesis.
- Hardware button mapping for physical FPGA board input.
- Richer floor/ceiling gradients and skybox colour split.
- Optional mini-map overlay.

---

## License

This project is provided as-is for educational and demonstration purposes.
