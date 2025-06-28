#include "camera.hpp"

Camera::Camera() {
    position = vec3(0.0, 0.0, 0.0);
    target = vec3(0.0, 0.0, -1.0);
    up = vec3(0.0, 1.0, 0.0);

    direction = unit_vector(target - position);
    right = unit_vector(cross(direction, up));
    up = unit_vector(cross(right, direction)); 

    horizontal = right * viewport_width;
    vertical = up * viewport_height;

    vec3 center = position + direction * focal_length;
    upper_left_corner = center - horizontal / 2 + vertical / 2;
}
