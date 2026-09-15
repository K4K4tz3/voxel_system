#include "voxel_object.h"

#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Voxel_Object::_bind_methods() {
  ADD_GROUP("Grid", "m_grid_");

  ClassDB::bind_method(D_METHOD("set_grid_width", "m_grid_width"),
                       &Voxel_Object::set_grid_width);
  ClassDB::bind_method(D_METHOD("get_grid_width"),
                       &Voxel_Object::get_grid_width);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "m_grid_width"), "set_grid_width",
               "get_grid_width");
  ClassDB::bind_method(D_METHOD("set_grid_height", "m_grid_height"),
                       &Voxel_Object::set_grid_height);
  ClassDB::bind_method(D_METHOD("get_grid_height"),
                       &Voxel_Object::get_grid_height);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "m_grid_height"), "set_grid_height",
               "get_grid_height");
  ClassDB::bind_method(D_METHOD("set_grid_depth", "m_grid_depth"),
                       &Voxel_Object::set_grid_depth);
  ClassDB::bind_method(D_METHOD("get_grid_depth"),
                       &Voxel_Object::get_grid_depth);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "m_grid_depth"), "set_grid_depth",
               "get_grid_depth");
}

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
  m_voxel_densities->reserve(a_size);
}

void Voxel_Object::set_densities(std::vector<int> &a_densities) {
  m_voxel_densities = &a_densities;
}

int Voxel_Object::get_voxels_size() const {
  if (m_voxel_densities == nullptr) {
    UtilityFunctions::push_warning(
        "Voxel_Object::get_voxels_size: m_voxel_densities is null");
    return -1;
  }
  return m_voxel_densities->size();
}

std::vector<int> &Voxel_Object::get_density_ref() { return *m_voxel_densities; }

int Voxel_Object::get_grid_size() const {
  return (m_grid_width * m_grid_height * m_grid_depth);
}

void Voxel_Object::set_mesh_instance(Ref<ArrayMesh> a_mesh) {

  m_mesh_instance->set_mesh(a_mesh);
}

/**
 * @brief This function takes in a index and takes it as its origin, then with
 * a_manipulation the new index gets calulated.
 *
 * @param a_index The index of the relevant voxel.
 * @param2 Vector3 Manipulation value used on relevant voxel's origin
 *
 * WARN: Return value is not limited.
 * -> Out of Bounds to be expected
 * -> No limitation was set, as there was no real reason for it
 *
 */
int Voxel_Object::get_index_from_vec_manipulation(
    const int a_initial_index, const Vector3 a_manipulation) const {

  int index_change = 0;
  index_change += a_manipulation.x;
  index_change += m_grid_width * a_manipulation.y;
  index_change += m_grid_width * m_grid_height * a_manipulation.z;

  return a_initial_index + index_change;
}
