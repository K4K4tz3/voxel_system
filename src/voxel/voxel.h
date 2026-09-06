#ifndef VOXEL_H
#define VOXEL_H

#include <godot_cpp/classes/node3d.hpp>

namespace godot {

struct Voxel {

  Node3D *center;
  // WARN: Offset has to be max half the voxels size
  // MANUALLY set!!!
  Vector3 top() const { return center->get_position() + Vector3(0, 0.5, 0); }
  Vector3 bot() const { return center->get_position() + Vector3(0, -0.5, 0); }
  Vector3 front() const { return center->get_position() + Vector3(0.5, 0, 0); }
  Vector3 back() const { return center->get_position() + Vector3(-0.5, 0, 0); }
  Vector3 left() const { return center->get_position() + Vector3(0, 0, 0.5); }
  Vector3 right() const { return center->get_position() + Vector3(0, 0, -0.5); }
};

}; // namespace godot

#endif
