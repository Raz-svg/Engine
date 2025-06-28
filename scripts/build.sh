#!/bin/bash

# Build script for raytracer project

set -e  # Exit on any error

echo "Building Raytracer..."

# Clean previous build
echo "Cleaning previous build..."
make clean

# Build the project
echo "Compiling..."
make

echo "Build complete!"
echo "Executable: ./output/raytracer"
echo ""
echo "To run: cd output && ./raytracer"
