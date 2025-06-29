# Test Makefile for Raytracer Unit Tests
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -pthread
INCLUDES = -I../../include
LIBS = -lgtest -lgtest_main -pthread

# Build directories
BUILDDIR = ../../build/tests
OBJDIR = $(BUILDDIR)/obj

# Test source files
TEST_SOURCES = test_vec3.cpp test_camera.cpp test_ray.cpp test_main.cpp

# Main source files (only non-SDL dependent ones)
MAIN_SOURCES = ../../src/camera.cpp

# Object files
TEST_OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(TEST_SOURCES))
MAIN_OBJECTS = $(patsubst ../../src/%.cpp,$(OBJDIR)/src_%.o,$(MAIN_SOURCES))

# Target executable
TARGET = $(BUILDDIR)/test_runner

.PHONY: all clean test install-deps

all: $(TARGET)

# Create build directories
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(TEST_OBJECTS) $(MAIN_OBJECTS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/src_%.o: ../../src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

install-deps:
	@echo "Installing Google Test..."
	@echo "On Ubuntu/Debian: sudo apt-get install libgtest-dev cmake"
	@echo "Then build gtest:"
	@echo "cd /usr/src/gtest && sudo cmake . && sudo make && sudo cp lib/*.a /usr/lib"
	@echo ""
	@echo "Or install via package manager:"
	@echo "sudo apt-get install libgtest-dev libgtest-main-dev"

clean:
	rm -rf $(BUILDDIR)

# Clean legacy files
clean-legacy:
	rm -f $(TEST_SOURCES:.cpp=.o) ../../src/*.o test_runner

help:
	@echo "Available targets:"
	@echo "  all         - Build test executable"
	@echo "  test        - Build and run tests"
	@echo "  clean       - Remove object files and executable"
	@echo "  install-deps - Show instructions for installing Google Test"
	@echo "  help        - Show this help message"
