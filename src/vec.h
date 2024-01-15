#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

using std::cout;

class vec3 {
  public:
  float e[3] = {};
  vec3() = default;
  vec3(float x, float y, float z) { e[0] = x; e[1] = y; e[2] = z; }
  float operator[](int i) const  { return e[i]; };
  float& operator[](int i) { return e[i]; };
};

std::ostream& operator<<(std::ostream &os, vec3 v) {
  os << "{ x: " << v[0] << ", y: " << v[1] << ", z: " << v[2] << " };";
  return os; 
}

class vec4 {
  public:
  float e[4];
  vec4() = default;
  vec4(float x, float y, float z, float w) { e[0] = x; e[1] = y; e[2] = z; e[3] = w; }
  float operator[](int i) { return e[i]; };
};

std::ostream& operator<<(std::ostream &os, vec4 v) {
  os << "{ x: " << v[0] << ", y: " << v[1] << ", z: " << v[2] << ", w: " << v[3] << " };";
  return os; 
}

vec4 make_vec4(vec3 a, float w);
vec3 add(vec3 a, vec3 b);
vec3 negate(vec3 a);
vec3 subtract(vec3 a, vec3 b);
vec3 multiply(float t, vec3 a);
vec3 divide(vec3 a, float t);
float len_squared(vec3 a);
float len(vec3 a);
vec3 normalize(vec3 a);
float dot(vec3 a, vec3 b);
vec3 cross(vec3 a, vec3 b);
vec3 camera_to_screen(vec3 point_camera);
vec3 screen_to_ndc(vec3 point_screen, float canvas_w, float canvas_h);
vec3 ndc_to_raster(vec3 point_ndc, float image_w, float image_h);

vec3 make_vec3(vec4 a);
vec4 add(vec4 a, vec4 b);
vec4 negate(vec4 a);
vec4 subtract(vec4 a, vec4 b);
vec4 multily(float t, vec4 a);
vec4 divide(vec4 a, float t);

vec4 make_vec4(vec3 a, float w) {
  return { a[0], a[1], a[2], w };
}

vec3 add(vec3 a, vec3 b) {
  return { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
}

vec3 negate(vec3 a) {
  return { -a[0], -a[1], -a[2] };
}

vec3 subtract(vec3 a, vec3 b) {
  return add(a, negate(b));
}

vec3 multiply(float t, vec3 a) {
  return { t * a[0], t * a[1], t * a[2] };
}

vec3 divide(vec3 a, float t) {
  return multiply(1 / t, a);
}

float len_squared(vec3 a) {
  return a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
}

float len(vec3 a) {
  return sqrt( len_squared(a) );
}

vec3 normalize(vec3 a) {
  return divide( a, len(a) );
}


float dot(vec3 a, vec3 b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

vec3 cross(vec3 a, vec3 b) {
  return { a[1] * b[2] - a[2] * b[1],
           a[2] * b[0] - a[0] * b[2],
           a[0] * b[1] - a[1] * b[0] };
}

// vec2f
vec3 camera_to_screen(vec3 point_camera) {
  // cout << "point_camera = " << point_camera << "\n";
  float z = point_camera[2];
  return { point_camera[0] / z, point_camera[1] / z, z };
}

// vec2f
vec3 screen_to_ndc(vec3 point_screen, float canvas_w, float canvas_h) {
  // cout << "point_screen = " << point_screen << "\n";
  return { (point_screen[0] + canvas_w * float(0.5)) / canvas_w,
           (point_screen[1] + canvas_h * float(0.5)) / canvas_h, 
           point_screen[2] };
}

// vec2i
vec3 ndc_to_raster(vec3 point_ndc, float image_w, float image_h) {
  // cout << "point_ndc = " << point_ndc << "\n";
  return { point_ndc[0] * image_w,
           (1 - point_ndc[1]) * image_h,
           point_ndc[2] };
}

vec3 make_vec3(vec4 a) {
  float w = a[3];
  return { a[0] / w, a[1] / w, a[2] / w};
}

vec4 add(vec4 a, vec4 b) {
  return { a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3] };
}

vec4 negate(vec4 a) {
  return { -a[0], -a[1], -a[2], -a[3] };
}

vec4 subtract(vec4 a, vec4 b) {
  return add(a, negate(b));
}

vec4 multily(float t, vec4 a) {
  return { t * a[0], t * a[1], t * a[2], t * a[3] };
}

vec4 divide(vec4 a, float t) {
  return multily(1 / t, a);
}