CXX = g++
# Performance-optimized flags
CXXFLAGS_RELEASE = -Wall -Wextra -std=c++17 -Iinclude -O3 -march=native -flto -funroll-loops -ffast-math -DNDEBUG
CXXFLAGS_DEBUG = -Wall -Wextra -std=c++17 -Iinclude -g -O0 -DDEBUG
LDFLAGS = -lSDL2 -lm -lpthread

SRCDIR = src
INCDIR = include
BUILDDIR = build
OBJDIR_DEBUG = $(BUILDDIR)/debug
OBJDIR_RELEASE = $(BUILDDIR)/release
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Default target is debug
all: debug

# Debug build
debug: OBJDIR = $(OBJDIR_DEBUG)
debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: TARGET = $(OBJDIR_DEBUG)/raytracer
debug: OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR_DEBUG)/%.o,$(SOURCES))
debug: $(OBJDIR_DEBUG)/raytracer
	@echo "Built debug version at $(OBJDIR_DEBUG)/raytracer"

# Release build
release: OBJDIR = $(OBJDIR_RELEASE)
release: CXXFLAGS = $(CXXFLAGS_RELEASE)
release: TARGET = $(OBJDIR_RELEASE)/raytracer
release: OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR_RELEASE)/%.o,$(SOURCES))
release: $(OBJDIR_RELEASE)/raytracer
	@echo "Built optimized release version at $(OBJDIR_RELEASE)/raytracer"

# Create directories
$(OBJDIR_DEBUG):
	mkdir -p $(OBJDIR_DEBUG)

$(OBJDIR_RELEASE):
	mkdir -p $(OBJDIR_RELEASE)

# Debug build rules
$(OBJDIR_DEBUG)/raytracer: $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR_DEBUG)/%.o,$(SOURCES)) | $(OBJDIR_DEBUG)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJDIR_DEBUG)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

# Release build rules
$(OBJDIR_RELEASE)/raytracer: $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR_RELEASE)/%.o,$(SOURCES)) | $(OBJDIR_RELEASE)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJDIR_RELEASE)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR_RELEASE)
	$(CXX) $(CXXFLAGS_RELEASE) -c $< -o $@

# Convenience targets
run-debug: debug
	$(OBJDIR_DEBUG)/raytracer

run-release: release
	$(OBJDIR_RELEASE)/raytracer

# Clean targets
clean:
	rm -rf $(BUILDDIR)

clean-debug:
	rm -rf $(OBJDIR_DEBUG)

clean-release:
	rm -rf $(OBJDIR_RELEASE)

# Clean legacy directories
clean-legacy:
	rm -rf obj output

.PHONY: all debug release run-debug run-release clean clean-debug clean-release clean-legacy
