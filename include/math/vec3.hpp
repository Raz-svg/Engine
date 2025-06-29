#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>

class vec3{
    public:
    // Align for better SIMD performance
    alignas(32) double e[3];

    vec3():e{0,0,0}{}
    vec3(double e0,double e1,double e2):e{e0,e1,e2}{}

    inline double x()const{return e[0];}
    inline double y()const{return e[1];}
    inline double z()const{return e[2];}

    inline vec3 operator -()const {return vec3(-e[0],-e[1],-e[2]);}
    inline double operator[](int i) const { return e[i]; }
    inline double& operator[](int i) { return e[i]; }

    inline vec3& operator +=(const vec3&v){
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    // scalar multiplication
    inline vec3& operator *=(double t){
        e[0]=t*e[0];
        e[1]=t*e[1];
        e[2]=t*e[2];
        return *this;

    }

    inline vec3& operator/=(double t){
        return *this *=1/t;
    }
    inline double length() const {
        return std::sqrt(length_squared());
    }
    inline double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];

    }
};

//alias for a point
using point3 =vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

// Type aliases for clarity
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

#endif