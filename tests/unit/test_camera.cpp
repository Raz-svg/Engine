#include <gtest/gtest.h>
#include "../../include/rendering/camera.hpp"
#include <cmath>

// Test camera construction
TEST(CameraTest, Construction) {
    Camera camera;
    
    // Test that camera is properly initialized with default values
    Ray ray = camera.get_ray(0, 0);
    
    // Ray should start from default camera position (0,0,0)
    EXPECT_DOUBLE_EQ(ray.origin().x(), 0.0);
    EXPECT_DOUBLE_EQ(ray.origin().y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.origin().z(), 0.0);
    
    // Ray direction should be pointing outward
    EXPECT_NE(ray.direction().length(), 0.0);
}

// Test ray generation at different pixel positions
TEST(CameraTest, RayGeneration) {
    Camera camera;
    
    // Test center ray
    Ray center_ray = camera.get_ray(600, 338); // Middle of default 1200x675 image
    
    // Test corner rays have different directions
    Ray top_left = camera.get_ray(0, 0);
    Ray bottom_right = camera.get_ray(1199, 674);
    
    // These rays should have different directions
    vec3 tl_dir = unit_vector(top_left.direction());
    vec3 br_dir = unit_vector(bottom_right.direction());
    
    EXPECT_NE(tl_dir.x(), br_dir.x());
    EXPECT_NE(tl_dir.y(), br_dir.y());
    
    // All rays should originate from the same position
    EXPECT_DOUBLE_EQ(top_left.origin().x(), bottom_right.origin().x());
    EXPECT_DOUBLE_EQ(top_left.origin().y(), bottom_right.origin().y());
    EXPECT_DOUBLE_EQ(top_left.origin().z(), bottom_right.origin().z());
}

// Test aspect ratio update
TEST(CameraTest, AspectRatioUpdate) {
    Camera camera;
    
    // Get initial aspect ratio
    double initial_aspect = camera.aspect_ratio;
    
    // Set new aspect ratio
    camera.set_aspect_ratio(1.0); // Square aspect ratio
    
    EXPECT_DOUBLE_EQ(camera.aspect_ratio, 1.0);
    EXPECT_NE(camera.aspect_ratio, initial_aspect);
}

// Test dimension update
TEST(CameraTest, DimensionUpdate) {
    Camera camera;
    
    // Update dimensions
    camera.update_dimensions(800, 600);
    
    EXPECT_DOUBLE_EQ(camera.image_width, 800.0);
    EXPECT_DOUBLE_EQ(camera.image_height, 600.0);
    EXPECT_DOUBLE_EQ(camera.aspect_ratio, 800.0/600.0);
}
