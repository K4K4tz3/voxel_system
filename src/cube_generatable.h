#ifndef CUBE_GENERATABLE_H
#define CUBE_GENERATABLE_H

#include <vector>

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

namespace godot {

class Cube_Generatable : public Node3D {
  GDCLASS(Cube_Generatable, Node3D)

private:
  MeshInstance3D *m_mesh_instance = nullptr;

  const PackedVector3Array M_VERTICES = {
      Vector3(-1.0, 1.0, 0.0),  // top left
      Vector3(1.0, 1.0, 0.0),   // top right
      Vector3(1.0, -1.0, 0.0),  // bot right
      Vector3(-1.0, -1.0, 0.0), // bot left
  };

  const std::vector<int> M_VERT_ORDER = {0, 2, 3, 0, 1, 2};
  const int M_VERT_COUNT = M_VERT_ORDER.size();

  Vector3 get_vertice_coords(const int a_index) { return M_VERTICES[a_index]; };

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
