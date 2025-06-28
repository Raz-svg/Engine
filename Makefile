CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = -lSDL2 -lm

SRCDIR = .
INCDIR = include
OBJDIR = obj
OUTDIR = output
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
TARGET = $(OUTDIR)/raytracer

all: $(TARGET)

# Create directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(TARGET): $(OBJECTS) | $(OUTDIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OUTDIR)

.PHONY: all clean
