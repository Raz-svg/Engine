#include <gtest/gtest.h>
#include "../../include/rendering/image.hpp"

// Test basic image construction and initialization
TEST(ImageTest, Construction) {
    Image img;
    
    // Image should start with zero dimensions
    EXPECT_DOUBLE_EQ(img.get_width(), 0.0);
    EXPECT_DOUBLE_EQ(img.get_height(), 0.0);
}

// Test image initialization 
TEST(ImageTest, Initialization) {
    Image img;
    
    // Initialize with specific dimensions (we'll skip SDL_Renderer for unit tests)
    img.initialize(800, 600, nullptr);
    
    EXPECT_DOUBLE_EQ(img.get_width(), 800.0);
    EXPECT_DOUBLE_EQ(img.get_height(), 600.0);
}

// Test pixel setting operations
TEST(ImageTest, PixelOperations) {
    Image img;
    img.initialize(100, 100, nullptr);
    
    // Test that pixel setting doesn't crash
    // Note: We can't easily test pixel retrieval without modifying the Image class
    // to expose pixel data for testing
    EXPECT_NO_THROW(img.setpixel(50, 50, 1.0, 0.5, 0.25));
    EXPECT_NO_THROW(img.setpixel_safe(75, 75, 0.8, 0.6, 0.4));
}

// Test bulk pixel operations
TEST(ImageTest, BulkPixelOperations) {
    Image img;
    img.initialize(100, 100, nullptr);
    
    // Test bulk pixel setting
    EXPECT_NO_THROW(img.setpixel_block(10, 10, 20, 20, 1.0, 0.0, 0.0));
}

// Test resize functionality
TEST(ImageTest, Resize) {
    Image img;
    img.initialize(100, 100, nullptr);
    
    // Test resize
    img.resize(200, 150);
    
    EXPECT_DOUBLE_EQ(img.get_width(), 200.0);
    EXPECT_DOUBLE_EQ(img.get_height(), 150.0);
}

// Test boundary safety
TEST(ImageTest, BoundarySafety) {
    Image img;
    img.initialize(10, 10, nullptr);
    
    // Test that out-of-bounds operations don't crash (using safe version)
    EXPECT_NO_THROW(img.setpixel_safe(-1, -1, 1.0, 1.0, 1.0));
    EXPECT_NO_THROW(img.setpixel_safe(100, 100, 1.0, 1.0, 1.0));
    EXPECT_NO_THROW(img.setpixel_safe(5, 15, 1.0, 1.0, 1.0));
}

// Test Pixel structure
TEST(ImageTest, PixelStructure) {
    // Test Pixel construction
    Pixel p1;
    EXPECT_DOUBLE_EQ(p1.r, 0.0);
    EXPECT_DOUBLE_EQ(p1.g, 0.0);
    EXPECT_DOUBLE_EQ(p1.b, 0.0);
    
    Pixel p2(0.5, 0.7, 0.9);
    EXPECT_DOUBLE_EQ(p2.r, 0.5);
    EXPECT_DOUBLE_EQ(p2.g, 0.7);
    EXPECT_DOUBLE_EQ(p2.b, 0.9);
}
