#include "voxel_object.h"

#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Voxel_Object::_bind_methods() {}

Voxel_Object::Voxel_Object() {
  m_mesh_instance = memnew(MeshInstance3D);
  add_child(m_mesh_instance);
}
Voxel_Object::~Voxel_Object() {}

void Voxel_Object::_ready() {
  m_center_model =
      ResourceLoader::get_singleton()->load("res://object_center_marker.glb");
  if (m_center_model.is_null()) {
    UtilityFunctions::push_error("Voxel_Generator: Debug Model cant be loaded");
  } else {
    Node3D *node = Object::cast_to<Node3D>(m_center_model->instantiate());

    add_child(node);
  }
}

void Voxel_Object::reserve_voxels(const size_t a_size) {
  m_voxels.reserve(a_size);
}

void Voxel_Object::push_back_voxel(Voxel *a_voxel) {
  m_voxels.push_back(a_voxel);
}

void Voxel_Object::set_voxel(const size_t a_index, Voxel *a_voxel) {
  m_voxels[a_index] = a_voxel;
}

Voxel *Voxel_Object::get_voxel_ref(const size_t a_index) {
  if (m_voxels.size() == 0) {
    UtilityFunctions::push_warning(
        "Voxel_object::get_voxel_ref: voxel vector is empty");
    return nullptr;
  }

  if (a_index > m_voxels.size()) {
    UtilityFunctions::push_warning(
        "Voxel_Object::get_voxel_ref: a_index is too big!");
    return nullptr;
  }

  return m_voxels[a_index];
}

int Voxel_Object::get_voxels_size() const { return m_voxels.size(); }

void Voxel_Object::set_mesh_instance(Ref<ArrayMesh> a_mesh) {
  m_mesh_instance->set_mesh(a_mesh);
}
