#ifndef VOXEL_H
#define VOXEL_H

#include <godot_cpp/classes/node3d.hpp>

namespace godot {

struct Voxel {

  Node3D *center;
  Node3D *top;
  Node3D *left;
  Node3D *back;
  Node3D *right;
  Node3D *front;
  Node3D *bottom;
};

}; // namespace godot

#endif
