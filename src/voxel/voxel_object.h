#ifndef VOXEL_OBJECT_H
#define VOXEL_OBJECT_H

#include <vector>

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

namespace godot {

class Voxel_Object : public Node3D {
  GDCLASS(Voxel_Object, Node3D)

private:
  MeshInstance3D *m_mesh_instance = nullptr;

  const PackedVector3Array M_VERTICES = {
      // front
      Vector3(-1.0, 1.0, 1.0),   // top left
      Vector3(1.0, 1.0, 1.0),    // top right
      Vector3(1.0, -1.0, 1.0),   // bot right
      Vector3(-1.0, -1.0, 1.0),  // bot left
                                 // back
      Vector3(1.0, 1.0, -1.0),   // top right
      Vector3(-1.0, 1.0, -1.0),  // top left
      Vector3(-1.0, -1.0, -1.0), // bot left
      Vector3(1.0, -1.0, -1.0),  // bot right
  };

  const std::vector<int> M_VERT_ORDER = {
      0, 1, 3, 2, 3, 1, // front
      1, 4, 2, 7, 2, 4, // right
      4, 5, 7, 6, 7, 5, // back
      5, 0, 6, 3, 6, 0, // left
      5, 4, 0, 1, 0, 4, // top
      3, 2, 6, 7, 6, 2, // bottom
  };
  const int M_VERT_COUNT = M_VERT_ORDER.size();

  Vector3 get_vertice_coords(const int a_index) const {
    return M_VERTICES[a_index];
  };

protected:
  static void _bind_methods();

public:
  Voxel_Object();
  ~Voxel_Object();

  void _ready() override;
  void build_cube();
};
} // namespace godot

#endif
