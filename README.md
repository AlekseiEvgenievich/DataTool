# DataTool

`DataTool` is a C++/ROOT-based library designed for reading, processing, and analyzing detector data in the **Crystal Eye** project.

The core of the library is the `AlgDataAction` class, which provides a high-level interface for:

- reading events from ROOT trees;
- managing run/event lifecycle;
- accessing energy deposits, hits, and pixel-level data;
- retrieving primary particle information;
- applying trigger thresholds;
- building response maps and effective area;
- performing spectrum reweighting;
- reconstructing directions and evaluating statistical metrics using ROOT tools (`TH1D`, `TH2D`, `TF1`, `TGraph`).

---

## Purpose

This library acts as an intermediate analysis layer between ROOT data files and higher-level physics analysis.

From the API structure, the detector includes:

- an Anti-Coincidence Detector (ACD);
- upper and lower calorimeter layers (CAL);
- multiple pixels per subsystem (3 pixels per layer).

Typical use cases:

- event selection;
- deposited energy analysis;
- trigger studies;
- response mapping;
- effective area calculation;
- direction reconstruction.

---

## Repository Structure

```text
DataTool/
├── CMakeLists.txt
├── include/
│   └── AlgDataAction.hh
├── src/
│   ├── AlgDataAction.cc
│   └── AlgResponseSiPM.cc
└── dylib/
