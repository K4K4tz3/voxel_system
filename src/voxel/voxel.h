#ifndef VOXEL_H
#define VOXEL_H

#include <godot_cpp/classes/node3d.hpp>

namespace godot {

struct Voxel {

  Node3D *center;
  Vector3 top() const { return center->get_position() + Vector3(0, 1, 0); }
  Vector3 bottom() const { return center->get_position() + Vector3(0, -1, 0); }
  Vector3 front() const { return center->get_position() + Vector3(1, 0, 0); }
  Vector3 back() const { return center->get_position() + Vector3(-1, 0, 0); }
  Vector3 left() const { return center->get_position() + Vector3(0, 0, 1); }
  Vector3 right() const { return center->get_position() + Vector3(0, 0, -1); }
};

}; // namespace godot

#endif
