# Raytracer Project

A modern C++ raytracer built with SDL2, following "Ray Tracing in One Weekend" and beyond.

## Project Structure
```
renderer/
├── include/                    # Header files (organized by category)
│   ├── core/                  # Core application headers
│   │   └── app.hpp           # Main application class
│   ├── math/                 # Mathematical utilities
│   │   ├── vec3.hpp         # 3D vector class
│   │   └── ray.hpp          # Ray class for raytracing
│   └── rendering/           # Rendering-related headers
│       ├── camera.hpp       # Camera class
│       └── image.hpp        # Image/texture handling
├── src/                     # Source files
│   ├── main.cpp            # Entry point
│   ├── app.cpp             # Application implementation
│   ├── camera.cpp          # Camera implementation
│   └── image.cpp           # Image/texture implementation
├── obj/                     # Object files (build artifacts)
├── output/                  # Compiled executable
├── assets/                  # Resources and assets
│   ├── textures/           # Image files for materials
│   ├── models/             # 3D model files
│   └── scenes/             # Scene description files
├── tests/                   # Unit and integration tests
├── scripts/                 # Build and utility scripts
│   └── build.sh            # Main build script
└── docs/                    # Documentation
```

## Building
```bash
# Quick build using script
./scripts/build.sh

# Manual build
make              # Build the project
make clean        # Clean build artifacts

# Run the raytracer
./output/raytracer
```

## Current Features
- [x] Basic SDL2 window and rendering
- [x] Surface-to-texture pipeline for pixel output
- [x] Basic camera setup
- [x] Simple gradient rendering (proof of concept)

## Roadmap

### Core Raytracing Features
- [ ] Basic ray-sphere intersection
- [ ] Multiple objects in scene
- [ ] Basic materials (lambertian, metal, dielectric)
- [ ] Antialiasing (multisampling)
- [ ] Depth of field
- [ ] Motion blur
- [ ] Positionable camera with lookAt

### Advanced Rendering Techniques
- [ ] **Path Tracing**
  - [ ] Monte Carlo integration
  - [ ] Importance sampling
  - [ ] Russian roulette
- [ ] **Photon Mapping**
  - [ ] Photon emission and storage
  - [ ] Caustics rendering
  - [ ] Global illumination
- [ ] **Ray Marching**
  - [ ] Signed distance fields (SDFs)
  - [ ] Volumetric rendering
  - [ ] Procedural geometry

### Performance Optimizations
- [ ] **Real-time Raytracing**
  - [ ] GPU acceleration (CUDA/OpenCL)
  - [ ] Denoising algorithms
  - [ ] Temporal accumulation
- [ ] **Acceleration Structures**
  - [ ] Bounding Volume Hierarchy (BVH)
  - [ ] K-d trees
  - [ ] Octrees
- [ ] **Multi-threading**
  - [ ] Tile-based rendering
  - [ ] Thread pool implementation
  - [ ] Lock-free data structures

### Scene Management
- [ ] **Camera System**
  - [ ] First-person camera controls (WASD + mouse)
  - [ ] Smooth camera interpolation
  - [ ] Multiple camera presets
  - [ ] Camera animation/keyframes
- [ ] **Scene Loading**
  - [ ] OBJ file loading
  - [ ] Texture loading (PNG, JPG)
  - [ ] Scene description format (JSON/XML)
  - [ ] Material library system

### Advanced Materials & Lighting
- [ ] **Physically Based Rendering (PBR)**
  - [ ] Cook-Torrance BRDF
  - [ ] Metallic-roughness workflow
  - [ ] Normal mapping
  - [ ] Environment mapping
- [ ] **Complex Materials**
  - [ ] Subsurface scattering
  - [ ] Volumetric materials
  - [ ] Emissive materials
  - [ ] Procedural textures

### Output & Post-Processing
- [ ] **Image Output**
  - [ ] High dynamic range (HDR)
  - [ ] Multiple image formats
  - [ ] Animation rendering (image sequences)
- [ ] **Post-Processing**
  - [ ] Tone mapping
  - [ ] Gamma correction
  - [ ] Bloom effect
  - [ ] Color grading

### User Interface
- [ ] **Interactive Controls**
  - [ ] Real-time parameter adjustment
  - [ ] Scene manipulation
  - [ ] Render settings GUI
- [ ] **Debugging Tools**
  - [ ] Ray visualization
  - [ ] Performance profiling
  - [ ] Render statistics display

### Advanced Features
- [ ] **Volumetric Rendering**
  - [ ] Participating media
  - [ ] Clouds and fog
  - [ ] Fire and smoke simulation
- [ ] **Advanced Geometry**
  - [ ] Bezier surfaces
  - [ ] Subdivision surfaces
  - [ ] Procedural modeling
- [ ] **Animation**
  - [ ] Object animation
  - [ ] Camera paths
  - [ ] Temporal effects

## Technical Goals
- [ ] Memory-efficient scene representation
- [ ] Scalable architecture for large scenes
- [ ] Cross-platform compatibility
- [ ] Plugin system for extensibility
- [ ] Comprehensive unit testing
- [ ] Performance benchmarking suite

## Learning Objectives
This project serves as a comprehensive exploration of:
- Modern C++ programming practices
- Computer graphics algorithms
- Parallel programming techniques
- Software architecture design
- Performance optimization strategies

## References
- "Ray Tracing in One Weekend" series by Peter Shirley
- "Physically Based Rendering" by Pharr, Jakob, and Humphreys
- "Real-Time Rendering" by Möller, Haines, and Hoffman
- NVIDIA OptiX documentation
- Embree ray tracing kernels

## Contributing
This is a personal learning project, but suggestions and improvements are welcome!

---
*Last updated: June 29, 2025*
