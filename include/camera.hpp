#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"

class Camera{

    public:

        Camera()const{

            vec3& position=vec3(0.0,0.0,0.0),

        };

        void moveforward(double delta);
        void movebackward(double delta);
        void moveright(double delta);
        void moveleft(double delta);
        void moveup(double delta);
        void movedown(double delta);
        
    private:
        vec3 position;  // Camera position
        vec3 target;    // Point the camera is looking at
        vec3 up;        // Up vector for orientation
        vec3 direction; // Normalized direction (target - position)
        vec3 right;     // Right vector (cross product of direction and up)

    public:
        double aspect_ratio=16.0/9.0;
        double image_width=1200;
        double image_height=double(image_width/aspect_ratio);
        double focal_length=1.0;
        double viewport_height=2.0;
        double viewport_width=viewport_height/double(aspect_ratio);
        vec3 viewport_u=vec3(viewport_width,0,0);
        vec3 viewport_v=vec3(0,-viewport_height,0);

        

};

#endif