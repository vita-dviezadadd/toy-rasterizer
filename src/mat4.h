#pragma once

#include <cassert>
#include "cmath"
#include "vec.h"

class mat4 {
  public:
  float e[16] = { 1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1 };

  mat4() {};
  mat4( float a, float b, float c, float d,
        float q, float f, float g, float h,
        float i, float j, float k, float l,
        float m, float n, float o, float p) {
    e[0] = a; e[1] = b; e[2] = c; e[3] = d;
    e[0 + 4] = q; e[1 + 4] = f; e[2 + 4] = g; e[3 + 4] = h;
    e[0 + 8] = i; e[1 + 8] = j; e[2 + 8] = k; e[3 + 8] = l;
    e[0 + 12] = m; e[1 + 12] = n; e[2 + 12] = o; e[3 + 12] = p;
  };

  float operator()(int i, int j) const { assert(i * 4 + j < 16); return e[i * 4 + j]; };
  float& operator()(int i, int j) { assert(i * 4 + j < 16); return e[i * 4 + j]; };
};

// mat4 add(mat4 a, float t);
// mat4 subtract(mat4 a, float t);
// mat4 multiply(float t, mat4 a);
// mat4 divide(mat4 a, float t);
vec4 multiply(vec4 a, mat4 b);
mat4 multiply(mat4 a, mat4 b);
mat4 transpose (mat4 a);
mat4 inverse(mat4 a);
// local sace to world space
mat4 rotation_x(float rad);
// local sace to world space
mat4 rotation_y(float rad);
// local sace to world space
mat4 rotation_z(float rad);
// local sace to world space
mat4 translate(float t_b, float t_y, float t_z);
// world space to camera space
mat4 look_at(vec3 from, vec3 to, vec3 tmp = { 0, 1, 0 });
mat4 project(float fov_y, float n, float f);
// mat4 add(mat4 a, float t){
//   mat4 c;
//   for(int i = 0, i < 16; ++i) { c.e[i] = a.e[i] + t;
//   return c;
// }

// mat4 subtract(mat4 a, float t){
//   return add( a, -t );
// }

// mat4 multiply(float t, mat4 a){
//   mat4 c;
//   for(int i = 0, i < 16; ++i) { c.e[i] = a.e[i] * t;
//   return c;
// }

// mat4 divide(mat4 a, float t){
//   return multiply( 1 / t, a );
// }

vec4 multiply(vec4 a, mat4 b) {
  return { a[0] * b(0, 0) + a[1] * b(1, 0) + a[2] * b(2, 0) + a[3] * b(3, 0), 
           a[0] * b(0, 1) + a[1] * b(1, 1) + a[2] * b(2, 1) + a[3] * b(3, 1), 
           a[0] * b(0, 2) + a[1] * b(1, 2) + a[2] * b(2, 2) + a[3] * b(3, 2), 
           a[0] * b(0, 3) + a[1] * b(1, 3) + a[2] * b(2, 3) + a[3] * b(3, 3) };
}

mat4 multiply(mat4 a, mat4 b) {
  mat4 c = {};
  for (int i = 0; i < 4; ++i) { 
    for (int j = 0; j < 4; ++j) { 
      c(i, j) = a(i, 0) * b(0, j) + a(i, 1) * b(1, j) + a(i, 2) * b(2, j) + a(i, 3) * b(3, j); 
    } 
  }
  return c;
}

mat4 transpose(mat4 a) { 
  return mat4 { a(0, 0), a(1, 0), a(2, 0), a(3, 0), 
                a(0, 1), a(1, 1), a(2, 1), a(3, 1), 
                a(0, 2), a(1, 2), a(2, 2), a(3, 2), 
                a(0, 3), a(1, 3), a(2, 3), a(3, 3) }; 
} 

mat4 inverse(mat4 a) {
  int i, j, k; 
  mat4 s = {}; 

  // forward elimination
  for (i = 0; i < 3; ++i) { 
    int pivot = i; 
    float pivotsize = a(i, i); 

    if (pivotsize < 0) {
      pivotsize = -pivotsize; 

      for (j = i + 1; j < 4; ++j) { 
        float tmp = a(j, i); 

        if (tmp < 0) {
          tmp = -tmp; 

          if (tmp > pivotsize) { 
              pivot = j; 
              pivotsize = tmp; 
          }
        }
      } 
    } 
  
    if (pivotsize == 0) { 
      return mat4 {}; 
    } 

    if (pivot != i) { 
        for (j = 0; j < 4; ++j) { 
            float tmp; 

            tmp = a(i, j); 
            a(i, j) = a(pivot, j); 
            a(pivot, j) = tmp; 

            tmp = s(i, j); 
            s(i, j) = s(pivot, j); 
            s(pivot, j) = tmp; 
        } 
    } 
  
    for (j = i + 1; j < 4; ++j) { 
        float f = a(j, i) / a(i, i); 

        for (k = 0; k < 4; k++) { 
            a(j, k) -= f * a(i, k); 
            s(j, k) -= f * s(i, k); 
        } 
    } 
  } 

  // backward substitution
  for (i = 3; i >= 0; --i) { 
    float f; 

    if ((f = a(i, i)) == 0) { 
      return mat4 {}; 
    } 

    for (j = 0; j < 4; j++) { 
      a(i, j) /= f; 
      s(i, j) /= f; 
    } 

    for (j = 0; j < i; j++) { 
      f = a(j, i); 

      for (k = 0; k < 4; k++) { 
        a(j, k) -= f * a(i, k); 
        s(j, k) -= f * s(i, k); 
      } 
    } 
  } 

  return s; 
}

// local sace to world space
mat4 rotation_x(float rad) {
  float c = cos(rad);
  float s = sin(rad);
  return { 1, 0,  0, 0,
           0, c,  s, 0,
           0, -s, c, 0,
           0, 0,  0, 1 };
}

// local sace to world space
mat4 rotation_y(float rad) {
  float c = cos(rad);
  float s = sin(rad);
  return { c, 0, -s, 0,
           0, 1, 0,  0,
           s, 0, c,  0,
           0, 0,  0, 1 };
}

// local sace to world space
mat4 rotation_z(float rad) {
  float c = cos(rad);
  float s = sin(rad);
  return { c,  s, 0, 0,
           -s, c, 0, 0,
           0,  0, 1, 0,
           0,  0, 0, 1 };
}

// local sace to world space
mat4 translate(float t_x, float t_y, float t_z) {
  return { 1,   0,   0,   0,
           0,   1,   0,   0,
           0,   0,   1,   0,
           t_x, t_y, t_z, 1 };
}

// camera space to world space
mat4 look_at(vec3 from, vec3 to, vec3 tmp) {
  vec3 forward = normalize( subtract(from, to) ); 
  vec3 right = cross(normalize(tmp), forward); 
  vec3 up = cross(forward, right); 

  return { right[0],   right[1],   right[2],   0,
           up[0],      up[1],      up[2],      0,
           forward[0], forward[1], forward[2], 0,
           from[0],    from[1],    from[2],    1 };
}

mat4 project(float fov_y, float n, float f) { 
  float s = 1 / tan(fov_y * 0.5 * M_PI / 180); 

  return { s, 0, 0,                0,
           0, s, 0,                0,
           0, 0, -f / (f - n),     -1,
           0, 0, -f * n / (f - n), 0   };
}