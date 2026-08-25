#ifndef VOXEL_MANAGER_H
#define VOXEL_MANAGER_H

#include "voxel_object.h"

#include <godot_cpp/classes/node.hpp>

namespace godot {

class Voxel_Manager : public Node {
  GDCLASS(Voxel_Manager, Node)

private:
  std::vector<Voxel_Object *> m_objects;

protected:
  static void _bind_methods();

public:
  bool create_object();
  bool create_object_and_generate_default();
};

} // namespace godot

#endif
