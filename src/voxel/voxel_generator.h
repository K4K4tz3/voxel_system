#ifndef VOXEL_GENERATOR_H
#define VOXEL_GENERATOR_H

#include <godot_cpp/classes/node.hpp>

#include "voxel_data.h"
#include "voxel_interactor.h"

#include <godot_cpp/classes/node3d.hpp>

namespace godot {

class Voxel_Generator : public Node {
  GDCLASS(Voxel_Generator, Node)

private:
  NodePath m_interactor_path;
  Voxel_Interactor *m_interactor = nullptr;

  // void spawn_voxel_object();

  int m_voxel_size;
  int m_object_width, m_object_height, m_object_depth;
  Vector3 m_debug_voxel_center_scale = Vector3(1, 1, 1);

protected:
  static void _bind_methods();

public:
  Voxel_Generator();
  ~Voxel_Generator();

  void _ready() override;

  bool create_voxel_object();
  bool generate_grid(Voxel_Data &a_data);

  //
  // Property Set/Get
  //
  void set_interactor_path(const NodePath &a_path) {
    m_interactor_path = a_path;
  };
  NodePath get_interactor_path() const { return m_interactor_path; };

  void set_voxel_size(const int &a_voxel_size) { m_voxel_size = a_voxel_size; };
  int get_voxel_size() const { return m_voxel_size; };

  void set_object_width(const int &a_object_width) {
    m_object_width = a_object_width;
  };
  int get_object_width() const { return m_object_width; };
  void set_object_height(const int &a_object_height) {
    m_object_height = a_object_height;
  };
  int get_object_height() const { return m_object_height; };
  void set_object_depth(const int &a_object_depth) {
    m_object_depth = a_object_depth;
  };
  int get_object_depth() const { return m_object_depth; };

  void set_debug_scale(const Vector3 &a_debug_voxel_center_scale) {
    m_debug_voxel_center_scale = a_debug_voxel_center_scale;
  };
  Vector3 get_debug_scale() const { return m_debug_voxel_center_scale; };
};
} // namespace godot

#endif
