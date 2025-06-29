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
├── build/                   # Build output directory (clean separation)
│   ├── debug/              # Debug build artifacts (object files + executable)
│   ├── release/            # Release build artifacts (object files + executable)
│   └── tests/              # Test build artifacts (test runner + object files)
├── assets/                  # Resources and assets
│   ├── textures/           # Image files for materials
│   ├── models/             # 3D model files
│   └── scenes/             # Scene description files
├── tests/                   # Unit and integration tests
│   └── unit/              # Google Test unit tests
├── docs/                    # Comprehensive documentation
├── scripts/                 # Build and utility scripts
│   └── build.sh            # Main build script
└── docs/                    # Documentation
```

## Building

The project uses a clean build system with separated debug and release builds:

```bash
# Debug build (default)
make debug        # or just 'make'
./build/debug/raytracer

# Optimized release build
make release
./build/release/raytracer

# Build and run shortcuts
make run-debug    # Build and run debug version
make run-release  # Build and run release version

# Clean builds
make clean        # Clean all build artifacts
make clean-debug  # Clean only debug build
make clean-release # Clean only release build

# Legacy cleanup (if needed)
make clean-legacy # Remove old obj/ and output/ directories
```

### Unit Tests
```bash
cd tests/unit
make test         # Build and run all unit tests
make clean        # Clean test artifacts
```

### Directory Structure
- All object files are stored in `build/debug/` or `build/release/`
- Test artifacts are stored in `build/tests/`
- Source code directories (`src/`, `include/`) remain clean
- No scattered `.o` files or executables in the source tree

### Version Control
- **Clean `.gitignore`**: The entire `build/` directory is ignored
- Only source code, documentation, and build scripts are tracked
- No build artifacts, object files, or executables in version control
- Professional setup suitable for team development

## Current Features
- [x] Basic SDL2 window and rendering
- [x] Surface-to-texture pipeline for pixel output
- [x] Basic camera setup with proper aspect ratio handling
- [x] Window resizing with responsive feedback
- [x] Debounced re-rendering to prevent performance issues
- [x] Immediate visual scaling during resize events
- [x] Memory-safe vector resizing and bounds checking
- [x] Multi-threaded tile-based rendering system
- [x] Progressive rendering (1/8 → 1/4 → 1/2 → full resolution)
- [x] Cache-optimized memory layout for pixel storage
- [x] SIMD-friendly vectorized math operations
- [x] Real-time resize preview rendering (experimental)
- [x] Aggressive compiler optimizations (-O3, -march=native, LTO)

## Performance Optimizations Implemented

### 1. Multi-threading
- Tile-based parallel rendering using all CPU cores
- 64x64 pixel tiles for optimal load balancing
- Thread-safe pixel operations

### 2. Progressive Rendering
- Renders at progressively higher resolutions: 1/8 → 1/4 → 1/2 → full
- Provides immediate visual feedback
- Reduces perceived latency

### 3. Memory Optimization
- Single contiguous pixel array instead of separate RGB channels
- Cache-aligned data structures (32-byte alignment)
- Row-major memory layout for cache efficiency

### 4. SIMD-Ready Math
- Vectorized vec3 operations with inline functions
- Cache-friendly memory alignment
- Optimized for auto-vectorization

### 5. Real-time Resize (Experimental)
- Background thread for continuous preview rendering during resize
- Low-resolution preview updates in real-time
- Automatic full-resolution render when resizing stops

### 6. Compiler Optimizations
```bash
# Debug build (default)
make

# Optimized release build
make release
```

Release build uses:
- `-O3` maximum optimization
- `-march=native` CPU-specific optimizations  
- `-flto` link-time optimization
- `-funroll-loops` loop unrolling
- `-ffast-math` aggressive math optimizations
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

## Performance Roadmap

### Completed ✅
- Multi-threaded CPU rendering with optimal tile sizes
- Progressive rendering for immediate visual feedback  
- Cache-optimized memory layout and SIMD-ready math
- Real-time resize preview system (needs debugging)
- Aggressive compiler optimizations

### Next Steps 🚀
1. **Fix Real-time Resize** - Debug segfault in background rendering thread
2. **GPU Acceleration** - Implement CUDA/OpenCL compute shaders for ray tracing
3. **Advanced Denoising** - Add temporal and spatial denoising algorithms
4. **Scene Complexity** - Add spheres, materials, and lighting models
5. **Adaptive Sampling** - Implement importance sampling for noise reduction
6. **Memory Streaming** - Large scene support with out-of-core rendering

### Expected Performance Gains
- **Multi-threading**: 4-12x speedup (depending on CPU cores)
- **Progressive rendering**: 50-90% reduction in perceived latency
- **Memory optimization**: 20-40% cache hit rate improvement
- **GPU acceleration**: 100-1000x speedup for complex scenes
- **Compiler optimization**: 15-30% raw performance improvement

The current implementation should handle window resizing much more responsively than the original single-threaded approach, with immediate scaling feedback and background progressive rendering.

## Documentation

For comprehensive technical details, see our complete documentation suite:

### Technical Reports

📚 **[Technical Report](docs/technical_report.typ)** (32 pages) - Complete raytracer analysis:
- Detailed class-by-class architecture breakdown
- Performance optimization techniques with proof of concept
- Multi-threading implementation analysis  
- Memory layout optimizations
- SIMD vectorization strategies
- Real-time resize system design
- Future enhancement roadmap
- GPU acceleration plans
- Resource references and further reading

🧪 **[Unit Testing Guide](docs/unit_testing_guide.typ)** (35 pages) - Comprehensive testing education:
- Complete introduction to unit testing concepts for beginners
- Google Test framework setup and usage
- Test organization and best practices
- Detailed explanation of every test implemented
- Advanced testing concepts (fixtures, mocking, property-based testing)
- Integration with development workflow
- Common pitfalls and solutions
- Performance testing strategies

🐧 **[Linux Commands Guide](docs/linux_commands_guide.typ)** (30 pages) - System administration tutorial:
- Analysis of specific commands used during Google Test setup
- General Linux file system navigation and troubleshooting
- Library management and installation procedures
- Systematic problem-solving methodology
- Package management and security considerations
- Advanced file operations and permissions
- Real-world troubleshooting examples and best practices

### Compiling the Documentation

All reports are written in Typst format. To compile them to PDF:

1. **Install Typst** (if not already installed):
   ```bash
   # Using Cargo (Rust package manager)
   cargo install typst-cli
   
   # Or download from https://github.com/typst/typst/releases
   ```

2. **Compile the reports**:
   ```bash
   # Technical report (raytracer architecture)
   typst compile docs/technical_report.typ docs/technical_report.pdf
   
   # Unit testing guide (testing education)
   typst compile docs/unit_testing_guide.typ docs/unit_testing_guide.pdf
   
   # Linux commands guide (system administration)
   typst compile docs/linux_commands_guide.typ docs/linux_commands_guide.pdf
   ```

3. **View the PDFs**:
   ```bash
   xdg-open docs/technical_report.pdf
   xdg-open docs/unit_testing_guide.pdf
   xdg-open docs/linux_commands_guide.pdf
   ```

## Testing

Unit tests are provided for core components using Google Test framework.

### Setting up Tests

1. **Install Google Test**:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install libgtest-dev libgtest-main-dev
   
   # Or build from source if needed
   sudo apt-get install libgtest-dev cmake
   cd /usr/src/gtest
   sudo cmake .
   sudo make
   sudo cp lib/*.a /usr/lib
   ```

2. **Build and run tests**:
   ```bash
   cd tests/unit
   make test
   ```

### Test Coverage

Current tests cover:
- **vec3**: Mathematical operations, dot/cross products, reflections
- **Ray**: Construction and parameter evaluation  
- **Camera**: Ray generation and positioning
- **Image**: Pixel operations, memory management, boundary checks

Additional tests can be added by creating new `test_*.cpp` files in the `tests/unit/` directory.

### Running Individual Test Suites

```bash
# Run all tests
make test

# Build test executable manually
make all
./test_runner

# Clean test artifacts
make clean
```

---
*Last updated: June 29, 2025*
