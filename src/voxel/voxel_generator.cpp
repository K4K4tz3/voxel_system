#include "voxel_generator.h"

#include "voxel.h"
#include "voxel_object.h"

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/node_path.hpp>

using namespace godot;

void Voxel_Generator::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_interactor_path", "path"),
                       &Voxel_Generator::set_interactor_path);

  ClassDB::bind_method(D_METHOD("get_interactor_path"),
                       &Voxel_Generator::get_interactor_path);

  ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "interactor_path"),
               "set_interactor_path", "get_interactor_path");

  ClassDB::bind_method(D_METHOD("set_voxel_size", "voxel size"),
                       &Voxel_Generator::set_voxel_size);
  ClassDB::bind_method(D_METHOD("get_voxel_size"),
                       &Voxel_Generator::get_voxel_size);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "m_voxel_size"), "set_voxel_size",
               "get_voxel_size");

  ClassDB::bind_method(D_METHOD("set_object_width", "m_object_width"),
                       &Voxel_Generator::set_object_width);
  ClassDB::bind_method(D_METHOD("get_object_width"),
                       &Voxel_Generator::get_object_width);

  ClassDB::bind_method(D_METHOD("set_object_height", "m_object_height"),
                       &Voxel_Generator::set_object_height);
  ClassDB::bind_method(D_METHOD("get_object_height"),
                       &Voxel_Generator::get_object_height);

  ClassDB::bind_method(D_METHOD("set_object_depth", "m_object_depth"),
                       &Voxel_Generator::set_object_depth);
  ClassDB::bind_method(D_METHOD("get_object_depth"),
                       &Voxel_Generator::get_object_depth);

  ADD_GROUP("Object", "object_");

  ADD_PROPERTY(PropertyInfo(Variant::INT, "object_width"), "set_object_width",
               "get_object_width");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "object_height"), "set_object_height",
               "get_object_height");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "object_depth"), "set_object_depth",
               "get_object_depth");

  //
  // Debug
  //
  ClassDB::bind_method(D_METHOD("set_debug_scale", "debug_voxel_center_scale"),
                       &Voxel_Generator::set_debug_scale);
  ClassDB::bind_method(D_METHOD("get_debug_scale"),
                       &Voxel_Generator::get_debug_scale);

  ADD_GROUP("Debug", "debug");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "debug_voxel_center_scale"),
               "set_debug_scale", "get_debug_scale");
}

Voxel_Generator::Voxel_Generator() {}
Voxel_Generator::~Voxel_Generator() {}

void Voxel_Generator::_ready() {
  if (m_interactor_path.is_empty()) {
    UtilityFunctions::push_warning("Voxel_Generator can't cast interactor");
    UtilityFunctions::push_error(
        "Voxel_Generator is missing: m_interactor_path[", m_interactor_path,
        "]");
  } else {
    m_interactor =
        Object::cast_to<Voxel_Interactor>(get_node_or_null(m_interactor_path));
  }

  // const int size = m_object_width * m_object_height * m_object_depth;
  m_debug_model = ResourceLoader::get_singleton()->load("res://ball.glb");
  if (m_debug_model.is_null()) {
    UtilityFunctions::push_error("Voxel_Generator: Debug Model cant be loaded");
  }

  m_material_default = ResourceLoader::get_singleton()->load("res://blue.tres");
  if (m_material_default.is_null()) {
    UtilityFunctions::push_error(
        "Voxel_Generator: Default Debug Material cant be loaded");
  }

  m_material_filled_voxel =
      ResourceLoader::get_singleton()->load("res://filled_voxel.tres");
  if (m_material_filled_voxel.is_null()) {
    UtilityFunctions::push_error(
        "Voxel_Generator: Filled Voxel Debug Material cant be loaded");
  }
}

/**
 * @brief Generates the individual voxels of a object.
 *
 * Creates a array full of voxels, each generated with a debug ball and their
 * own location.
 *
 * @param a_data Voxel_Data that acts as foundation for a Voxel_Object. When
 * left empty, an empty grid gets generated.
 * @return State of success
 */
bool Voxel_Generator::generate_grid(Voxel_Object &a_object) {
  const size_t grid_size = m_object_width * m_object_height * m_object_depth;

  std::vector<Voxel *> voxels;
  voxels.reserve(grid_size);

  for (int index = 0; index < grid_size; index++) {
    Voxel *current = new Voxel();
    // instantiate debug ball at index
    current->center = _create_debug_ball(index);
    add_child(current->center);
    _set_debug_ball_material(current->center, m_test_voxel_structure[index]);

    // top
    // left -> neg x
    // back -> neg z
    // right -> x
    // front -> z
    // bot
    UtilityFunctions::print("Generated ", index, " voxel");
  }

  // Node3D *instance = Object::cast_to<Node3D>(model->instantiate());
  // UtilityFunctions::print("generated grid");
  // instance->set_position(Vector3(0, 0, 0));
  // add_child(instance);

  return true;
}

Node3D *Voxel_Generator::_create_debug_ball(int a_index) {
  Node3D *node = Object::cast_to<Node3D>(m_debug_model->instantiate());

  float x = (a_index % m_object_width) - ((float)(m_object_width - 1) / 2);
  float y = ((a_index / m_object_width) % m_object_height) -
            ((float)(m_object_height - 1) / 2);
  float z = (a_index / (m_object_width * m_object_height)) -
            ((float)(m_object_depth - 1) / 2);

  UtilityFunctions::print("X: ", x, " Y: ", y, " Z: ", z);
  node->set_position(Vector3(x, y, z));
  node->set_scale(m_debug_voxel_center_scale);

  return node;
}

void Voxel_Generator::_set_debug_ball_material(Node3D *&a_node,
                                               const int a_value) {
  MeshInstance3D *mesh = a_node->get_node<MeshInstance3D>(NodePath("Sphere"));

  switch (a_value) {
  case 1:
    mesh->set_material_override(m_material_filled_voxel);
    break;
  default:
    mesh->set_material_override(m_material_default);
  }
}
