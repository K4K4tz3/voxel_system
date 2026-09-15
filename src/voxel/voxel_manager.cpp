#include "voxel_manager.h"
#include "voxel_generator.h"

#include <fstream>
#include <godot_cpp/classes/project_settings.hpp>
#include <nlohmann/json.hpp>

using namespace godot;

void Voxel_Manager::_bind_methods() {
  ClassDB::bind_method(D_METHOD("create_object"),
                       &Voxel_Manager::create_object);
  ClassDB::bind_method(D_METHOD("create_object_and_generate_default"),
                       &Voxel_Manager::create_object_and_generate_default);
  ClassDB::bind_method(D_METHOD("create_mesh"), &Voxel_Manager::create_mesh);
  ClassDB::bind_method(D_METHOD("load_from_file"),
                       &Voxel_Manager::load_from_file);

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

  if (!m_generator->generate_debug_grid(*object)) {
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

bool Voxel_Manager::load_from_file() {
  String file_path = ProjectSettings::get_singleton()->globalize_path(
      "res://voxel_data/test.json");
  // 1. load json
  std::ifstream file(file_path.utf8().get_data());
  if (!file.is_open()) {
    UtilityFunctions::push_warning("Voxel_Manager::load_from_file: Failed to "
                                   "load: ",
                                   file_path);
    return false;
  }

  // 2. parse and check file
  nlohmann::json data = nlohmann::json::parse(file, nullptr, false);

  if (data.is_discarded()) {
    UtilityFunctions::push_warning(
        "Voxel_Manager::load_from_file: Failed to parse json file");
    return false;
  }

  if (!data.contains("dimensions")) {
    UtilityFunctions::push_error(
        "Voxel_Manager::load_from_file: Failed to load: ", file_path);
    return false;
  }

  // 3. create voxel_object and set it based on json
  Voxel_Object *voxel_object = memnew(Voxel_Object);

  voxel_object->set_grid_width(data["dimensions"]["width"].get<int>());
  voxel_object->set_grid_height(data["dimensions"]["height"].get<int>());
  voxel_object->set_grid_depth(data["dimensions"]["depth"].get<int>());

  std::vector<int> *densities =
      new std::vector(data["densities"].get<std::vector<int>>());
  voxel_object->set_densities(*densities);
  add_child(voxel_object);

  //  3. generate debug grid
  m_generator->generate_debug_grid(*voxel_object);

  //  4. generate mesh
  m_generator->generate_mesh_instance(*voxel_object);

  UtilityFunctions::print(
      "Voxel_Manager::load_from_file: Successfully loaded voxel_object");
  return true;
}
