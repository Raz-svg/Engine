#include <gtest/gtest.h>
#include "../../include/math/vec3.hpp"
#include <cmath>

// Test basic vec3 construction
TEST(Vec3Test, Construction) {
    vec3 v1;
    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
    
    vec3 v2(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v2.x(), 1.0);
    EXPECT_DOUBLE_EQ(v2.y(), 2.0);
    EXPECT_DOUBLE_EQ(v2.z(), 3.0);
}

// Test vec3 operations
TEST(Vec3Test, BasicOperations) {
    vec3 v1(1.0, 2.0, 3.0);
    vec3 v2(4.0, 5.0, 6.0);
    
    // Addition
    vec3 sum = v1 + v2;
    EXPECT_DOUBLE_EQ(sum.x(), 5.0);
    EXPECT_DOUBLE_EQ(sum.y(), 7.0);
    EXPECT_DOUBLE_EQ(sum.z(), 9.0);
    
    // Subtraction
    vec3 diff = v2 - v1;
    EXPECT_DOUBLE_EQ(diff.x(), 3.0);
    EXPECT_DOUBLE_EQ(diff.y(), 3.0);
    EXPECT_DOUBLE_EQ(diff.z(), 3.0);
    
    // Scalar multiplication
    vec3 scaled = v1 * 2.0;
    EXPECT_DOUBLE_EQ(scaled.x(), 2.0);
    EXPECT_DOUBLE_EQ(scaled.y(), 4.0);
    EXPECT_DOUBLE_EQ(scaled.z(), 6.0);
}

// Test vec3 mathematical functions
TEST(Vec3Test, MathFunctions) {
    vec3 v1(3.0, 4.0, 0.0);
    
    // Length
    double length = v1.length();
    EXPECT_DOUBLE_EQ(length, 5.0);
    
    // Length squared
    double length_sq = v1.length_squared();
    EXPECT_DOUBLE_EQ(length_sq, 25.0);
    
    // Unit vector
    vec3 unit = unit_vector(v1);
    EXPECT_DOUBLE_EQ(unit.x(), 0.6);
    EXPECT_DOUBLE_EQ(unit.y(), 0.8);
    EXPECT_DOUBLE_EQ(unit.z(), 0.0);
    EXPECT_NEAR(unit.length(), 1.0, 1e-10);
}

// Test dot product
TEST(Vec3Test, DotProduct) {
    vec3 v1(1.0, 2.0, 3.0);
    vec3 v2(4.0, 5.0, 6.0);
    
    double dot_result = dot(v1, v2);
    EXPECT_DOUBLE_EQ(dot_result, 32.0); // 1*4 + 2*5 + 3*6 = 32
}

// Test cross product
TEST(Vec3Test, CrossProduct) {
    vec3 v1(1.0, 0.0, 0.0);
    vec3 v2(0.0, 1.0, 0.0);
    
    vec3 cross_result = cross(v1, v2);
    EXPECT_DOUBLE_EQ(cross_result.x(), 0.0);
    EXPECT_DOUBLE_EQ(cross_result.y(), 0.0);
    EXPECT_DOUBLE_EQ(cross_result.z(), 1.0);
}

// Test array access
TEST(Vec3Test, ArrayAccess) {
    vec3 v(1.0, 2.0, 3.0);
    
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    
    // Test mutable access
    v[0] = 10.0;
    EXPECT_DOUBLE_EQ(v[0], 10.0);
    EXPECT_DOUBLE_EQ(v.x(), 10.0);
}
