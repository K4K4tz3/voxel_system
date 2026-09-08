#ifndef VOXEL_MANAGER_H
#define VOXEL_MANAGER_H

#include "voxel_generator.h"
#include "voxel_object.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/node_path.hpp>

namespace godot {

class Voxel_Manager : public Node {
  GDCLASS(Voxel_Manager, Node)

private:
  NodePath m_generator_path;
  Voxel_Generator *m_generator = nullptr;

  std::vector<Voxel_Object *> m_objects;

protected:
  static void _bind_methods();

public:
  void _ready() override;

  bool create_object();
  bool create_object_and_generate_default();
  void create_mesh();
  bool load_from_file();

  void set_generator_path(const NodePath &a_generator_path) {
    m_generator_path = a_generator_path;
  };
  NodePath get_generator_path() const { return m_generator_path; };
};

} // namespace godot

#endif
