# Disparity_to_3d

This repository contains the files required to convert a Disparity image computed from a stereo camera to a 3D point cloud.

## Usage

### Setup

- Clone this repository to your suitable workspace
```bash
cmake .
make
```

### Run the codes

```bash
./convert
```

### Visualize

```bash
python3 scripts/visualizer.py
```

## Results

![Alt text](results/base_plot.png?raw=true "Visualizing on MathplotLib")
![Alt text](results/base_pcl_viewer.png?raw=true "Visualizing on pcl_viewer")