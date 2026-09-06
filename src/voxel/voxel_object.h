#ifndef VOXEL_OBJECT_H
#define VOXEL_OBJECT_H

#include "voxel.h"
#include "voxel_data.h"

#include <memory>
#include <vector>

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

namespace godot {

class Voxel_Object : public Node3D {
  GDCLASS(Voxel_Object, Node3D)

private:
  MeshInstance3D *m_mesh_instance = nullptr;
  std::vector<Voxel *> m_voxels;

  std::unique_ptr<Voxel_Data> m_voxel_data = nullptr;

  Ref<PackedScene> m_center_model;

protected:
  static void _bind_methods();

public:
  Voxel_Object();
  ~Voxel_Object();

  void _ready() override;

  void reserve_voxels(const size_t a_size);
  void push_back_voxel(Voxel *a_voxel);
  void set_voxel(const size_t a_index, Voxel *a_voxel);
  Voxel *get_voxel_ref(const size_t a_index);
  void set_mesh_instance(Ref<ArrayMesh> a_mesh);
  int get_voxels_size() const;
};
} // namespace godot

#endif
