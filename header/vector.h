#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

//vector3
class vec3 {
  public:
    double e[3];//buku soh buat pakai array daripada buat 3 double dok au bakpe

    vec3() : e{0,0,0} {}//ni kalu buat klass tapi tak assign
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }//call
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

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

vec3 kuasa(const vec3& u, double v){
    return vec3{pow(u.x(), v), pow(u.y(), v), pow(u.z(), v)};
}

bool kompare(const vec3& u, const vec3& v){
    if(u.x() ==v.x()&&u.y() ==v.y()&&u.z() ==v.z())return true;
    return false;
}

//vector4
class vec4 {
  public:
    double e[4];//buku soh buat pakai array daripada buat 3 double dok au bakpe

    vec4() : e{0,0,0,0} {}//ni kalu buat klass tapi tak assign
    vec4(double e0, double e1, double e2, double e3) : e{e0, e1, e2, e3} {}

    double x() const { return e[0]; }//call
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    double w() const { return e[3]; }

    vec4 operator-() const { return vec4(-e[0], -e[1], -e[2], -e[3]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec4& operator+=(const vec4& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        e[3] += v.e[3];
        return *this;
    }

    vec4& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        e[3] *= t;
        return *this;
    }

    vec4& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2] + e[3]*e[3];
    }
};

// point4 is just an alias for vec4, but useful for geometric clarity in the code.
using point4 = vec4;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec4& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << v.e[3] << ' ';
}

inline vec4 operator+(const vec4& u, const vec4& v) {
    return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
}

inline vec4 operator-(const vec4& u, const vec4& v) {
    return vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
}

inline vec4 operator*(const vec4& u, const vec4& v) {
    return vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
}

inline vec4 operator*(double t, const vec4& v) {
    return vec4(t*v.e[0], t*v.e[1], t*v.e[2], t*v.e[3]);
}

inline vec4 operator*(const vec4& v, double t) {
    return t * v;
}

inline vec4 operator/(const vec4& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec4& u, const vec4& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2]
         + u.e[3] * v.e[3];
}

inline vec4 cross(const vec4& u, const vec4& v) {
    return vec4(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0],
                0);
}

inline vec4 unit_vector(const vec4& v) {
    return v / v.length();
}

inline vec4 kuasa(const vec4& u, double v){
    return vec4{pow(u.x(), v), pow(u.y(), v), pow(u.z(), v), pow(u.w(), v)};
}

bool kompare(const vec4& u, const vec4& v){
    return (u.x() ==v.x()&&u.y() ==v.y()&&u.z() ==v.z()&&u.w()==v.w());
}

//transform
class Trans4{
    public:
        double e[4][4];
        Trans4(double ee[4][4]){
            for(int i = 0;i<4;i++){
                for(int j = 0;j<4;j++){
                    e[j][i] = ee[j][i];
                }
            }
        }
};
//transform util
inline Trans4 operator*(const Trans4& u, const Trans4& v){
    //Trans4 jwp({0.f,0.f,0.f,0.f},{0.f,0.f,0.f,0.f},{0.f,0.f,0.f,0.f},{0.f,0.f,0.f,0.f})
}

#endif