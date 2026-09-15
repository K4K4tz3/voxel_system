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
  String m_file_name;

  int m_grid_width;
  int m_grid_height;
  int m_grid_depth;

  std::vector<int> *m_voxel_densities;

  MeshInstance3D *m_mesh_instance = nullptr;

  // TODO: redo density storage with smaller type
  std::unique_ptr<Voxel_Data> m_voxel_data = nullptr;

  Ref<PackedScene> m_center_model;

protected:
  static void _bind_methods();

public:
  Voxel_Object();
  ~Voxel_Object();

  void _ready() override;

  void reserve_voxels(const size_t a_size);
  void set_densities(std::vector<int> &a_densities);
  std::vector<int> &get_density_ref();

  void set_mesh_instance(Ref<ArrayMesh> a_mesh);
  int get_voxels_size() const;
  int get_grid_size() const;
  int get_index_from_vec_manipulation(const int a_inital_index,
                                      const Vector3 a_manipulation) const;

  void set_grid_width(const int &a_grid_width) { m_grid_width = a_grid_width; };
  int get_grid_width() const { return m_grid_width; };
  void set_grid_height(const int &a_grid_height) {
    m_grid_height = a_grid_height;
  };
  int get_grid_height() const { return m_grid_height; };
  void set_grid_depth(const int &a_grid_depth) { m_grid_depth = a_grid_depth; };
  int get_grid_depth() const { return m_grid_depth; };
};
} // namespace godot

#endif
