#include "rendering/camera.hpp"

Camera::Camera() {
    position = point3(0.0, 0.0, 0.0);
    target = vec3(0.0, 0.0, -1.0);
    up = vec3(0.0, 1.0, 0.0);

    // Calculate camera basis vectors
    vec3 dir = unit_vector(target - position);
    right = unit_vector(cross(dir, up));
    up = unit_vector(cross(right, dir)); 

    horizontal = right * viewport_width;
    vertical = up * viewport_height;

    // Calculate the location of the upper left pixel
    auto viewport_upper_left = position - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Ray Camera::get_ray(int i, int j) const {
    // Calculate the location of the sample point in pixel i,j
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto ray_direction = pixel_center - position;
    
    return Ray(position, ray_direction);
}

void Camera::set_aspect_ratio(double new_aspect_ratio) {
    aspect_ratio = new_aspect_ratio;
    image_height = image_width / aspect_ratio;
    viewport_width = viewport_height / aspect_ratio;
    
    // Update viewport vectors
    viewport_u = vec3(viewport_width, 0, 0);
    viewport_v = vec3(0, -viewport_height, 0);
    
    // Update pixel deltas
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;
    
    // Recalculate pixel00_loc
    auto viewport_upper_left = position - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

void Camera::update_dimensions(double new_width, double new_height) {
    image_width = new_width;
    image_height = new_height;
    aspect_ratio = new_width / new_height;
    
    viewport_width = viewport_height / aspect_ratio;
    
    // Update viewport vectors
    viewport_u = vec3(viewport_width, 0, 0);
    viewport_v = vec3(0, -viewport_height, 0);
    
    // Update pixel deltas
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;
    
    // Recalculate pixel00_loc
    auto viewport_upper_left = position - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}