#ifndef CAMERA_H
#define CAMERA_H

#include "math/ray.hpp"

class Camera{

    public:

        Camera();

        void moveforward(double delta);
        void movebackward(double delta);
        void moveright(double delta);
        void moveleft(double delta);
        void moveup(double delta);
        void movedown(double delta);
        
        Ray get_ray(int i, int j) const;

        void set_aspect_ratio(double new_aspect_ratio);
        void update_dimensions(double new_width, double new_height);
        
    public:
        double aspect_ratio=16.0/9.0;
        double image_width=1200.0;
        double image_height=image_width/aspect_ratio;
        double focal_length=1.0;
        double viewport_height=2.0;
        double viewport_width=viewport_height/double(aspect_ratio);
        vec3 viewport_u=vec3(viewport_width,0,0);
        vec3 viewport_v=vec3(0,-viewport_height,0);
        vec3 viewport_center=vec3(0,0,-focal_length);
        vec3 pixel_delta_u=viewport_u/double(image_width);
        vec3 pixel_delta_v=viewport_v/double(image_height);
        
    private:
        vec3 position;  // Camera position
        vec3 target;    // Point the camera is looking at
        vec3 up;        // Up vector for orientation
        vec3 right;     // Right vector (cross product of direction and up)
        vec3 horizontal; // Horizontal viewport vector
        vec3 vertical;   // Vertical viewport vector
        vec3 upper_left_corner; // Upper left corner of viewport
        vec3 pixel00_loc; // Location of pixel (0,0)

    

};

#endif