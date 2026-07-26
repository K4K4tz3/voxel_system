#ifndef CUBE_GENERATABLE_H
#define CUBE_GENERATABLE_H

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

namespace godot {

class Cube_Generatable : public Node3D {
  GDCLASS(Cube_Generatable, Node3D)

private:
  MeshInstance3D *mesh_instance = nullptr;

protected:
  static void _bind_methods();

public:
  Cube_Generatable();
  ~Cube_Generatable();

  void _ready() override;
  void build_cube();
};
} // namespace godot

#endif
