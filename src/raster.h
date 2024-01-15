#pragma once

#include <cmath>

#include "vec.h"

struct face { 
  int vertex_indices[3]; 
  int texture_indices[3];
  int normal_indices[3];
};

struct triangle { 
  vec3 vertices[3]; 
  vec3 operator[](int i) { return vertices[i]; };
};

struct aabb { float min_x, min_y, max_x, max_y; };

aabb make_aabb(triangle t);
float edge_function(vec3 a, vec3 b, vec3 c);

aabb make_aabb(triangle t) {
  aabb bb = { INFINITY, INFINITY, -INFINITY, -INFINITY };
  for(int i = 0; i < 3; ++i) {
    vec3 v = t.vertices[i];
    if(v.e[0] < bb.min_x) { bb.min_x = v.e[0]; }
    if(v.e[0] > bb.max_x) { bb.max_x = v.e[0]; }
    if(v.e[1] < bb.min_y) { bb.min_y = v.e[1]; }
    if(v.e[1] > bb.max_y) { bb.max_y = v.e[1]; }
  }
  return bb;
}

float edge_function(vec3 a, vec3 b, vec3 c) { 
  return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]); 
}

