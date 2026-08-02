#ifndef VOXEL_GENERATOR_H
#define VOXEL_GENERATOR_H

#include <godot_cpp/classes/node.hpp>

#include "voxel_interactor.h"

#include <godot_cpp/classes/node3d.hpp>

namespace godot {

class Voxel_Generator : public Node {
  GDCLASS(Voxel_Generator, Node)

private:
  NodePath m_interactor_path;
  Voxel_Interactor *m_interactor = nullptr;

  void spawn_voxel_object();

protected:
  static void _bind_methods();

public:
  Voxel_Generator();
  ~Voxel_Generator();

  void _ready() override;

  void set_interactor_path(const NodePath &a_path) {
    m_interactor_path = a_path;
  };
  NodePath get_interactor_path() const { return m_interactor_path; };
};

} // namespace godot

#endif
