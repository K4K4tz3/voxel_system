#include "voxel_manager.h"

#include "voxel_generator.h"

using namespace godot;

void Voxel_Manager::_bind_methods() {
  ClassDB::bind_method(D_METHOD("create_object"),
                       &Voxel_Manager::create_object);
  ClassDB::bind_method(D_METHOD("create_object_and_generate_default"),
                       &Voxel_Manager::create_object_and_generate_default);
  ClassDB::bind_method(D_METHOD("create_mesh"), &Voxel_Manager::create_mesh);

  ClassDB::bind_method(D_METHOD("set_generator_path", "m_generator_path"),
                       &Voxel_Manager::set_generator_path);
  ClassDB::bind_method(D_METHOD("get_generator_path"),
                       &Voxel_Manager::get_generator_path);
  ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "m_generator_path"),
               "set_generator_path", "get_generator_path");
}

void Voxel_Manager::_ready() {
  if (m_generator_path.is_empty()) {
    UtilityFunctions::push_error("Voxel_Manager: m_generator_path is empty [",
                                 m_generator_path, "]");
    UtilityFunctions::push_warning(
        "Voxel_Manager: Unable to do primary function.");
    return;
  } else {
    m_generator =
        Object::cast_to<Voxel_Generator>(get_node_or_null(m_generator_path));
  }
}

/**
 * @brief Creates a voxel object and pushes into 'memory'
 *
 * @return State of success
 */
bool Voxel_Manager::create_object() {
  Voxel_Object *object = memnew(Voxel_Object);

  if (object == nullptr) {
    UtilityFunctions::push_warning("Voxel_Manager: Failed to create object.");
    delete object;
    return false;
  } else {
    UtilityFunctions::print("Voxel_Manager: Succeeded in creating object.");
  }
  add_child(object);

  // Object got created successfully
  m_objects.push_back(object);
  return true;
}

/**
 * @brief Creates a Voxel_Object and generates its grid.
 *
 * @return State of success
 */
bool Voxel_Manager::create_object_and_generate_default() {
  Voxel_Object *object = memnew(Voxel_Object);

  if (object == nullptr) {
    UtilityFunctions::push_warning("Voxel_Manager: Failed to create object.");
    delete object;
    return false;
  } else {
    UtilityFunctions::print("Voxel_Manager: Succeeded in creating object.");
  }
  add_child(object);

  if (!m_generator->generate_grid(*object)) {
    UtilityFunctions::push_warning("Voxel_Generator: Failed to generate_grid");
    return false;
  }
  // Object got created successfully
  m_objects.push_back(object);
  return true;
}

void Voxel_Manager::create_mesh() {
  m_generator->generate_mesh_instance(*m_objects[0]);
}
