#include <gtest/gtest.h>
#include "../../include/math/ray.hpp"

// Test ray construction
TEST(RayTest, Construction) {
    vec3 origin(1.0, 2.0, 3.0);
    vec3 direction(0.0, 0.0, -1.0);
    
    Ray ray(origin, direction);
    
    EXPECT_DOUBLE_EQ(ray.origin().x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.origin().y(), 2.0);
    EXPECT_DOUBLE_EQ(ray.origin().z(), 3.0);
    
    EXPECT_DOUBLE_EQ(ray.direction().x(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().z(), -1.0);
}

// Test ray at parameter t
TEST(RayTest, At) {
    vec3 origin(0.0, 0.0, 0.0);
    vec3 direction(1.0, 2.0, 3.0);
    
    Ray ray(origin, direction);
    
    // At t=0, should return origin
    vec3 at_zero = ray.at(0.0);
    EXPECT_DOUBLE_EQ(at_zero.x(), 0.0);
    EXPECT_DOUBLE_EQ(at_zero.y(), 0.0);
    EXPECT_DOUBLE_EQ(at_zero.z(), 0.0);
    
    // At t=1, should return origin + direction
    vec3 at_one = ray.at(1.0);
    EXPECT_DOUBLE_EQ(at_one.x(), 1.0);
    EXPECT_DOUBLE_EQ(at_one.y(), 2.0);
    EXPECT_DOUBLE_EQ(at_one.z(), 3.0);
    
    // At t=2, should return origin + 2*direction
    vec3 at_two = ray.at(2.0);
    EXPECT_DOUBLE_EQ(at_two.x(), 2.0);
    EXPECT_DOUBLE_EQ(at_two.y(), 4.0);
    EXPECT_DOUBLE_EQ(at_two.z(), 6.0);
}

// Test ray with negative t values
TEST(RayTest, NegativeT) {
    vec3 origin(5.0, 5.0, 5.0);
    vec3 direction(1.0, 1.0, 1.0);
    
    Ray ray(origin, direction);
    
    // At t=-1, should go backwards
    vec3 at_neg_one = ray.at(-1.0);
    EXPECT_DOUBLE_EQ(at_neg_one.x(), 4.0);
    EXPECT_DOUBLE_EQ(at_neg_one.y(), 4.0);
    EXPECT_DOUBLE_EQ(at_neg_one.z(), 4.0);
}
