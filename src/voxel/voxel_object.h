#ifndef VOXEL_OBJECT_H
#define VOXEL_OBJECT_H

#include <godot_cpp/classes/node3d.hpp>

namespace godot {

class Voxel_Object : public Node3D {
  GDCLASS(Voxel_Object, Node3D)

private:
protected:
  static void _bind_methods();

public:
  Voxel_Object();
  ~Voxel_Object();
};

} // namespace godot

#endif
