#include "voxel_generator.h"
#include "mesh_data.h"
#include "voxel.h"
#include "voxel_frame.h"
#include "voxel_object.h"

#include <filesystem>
#include <fstream>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
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

  if (!_load_marching_cube_cases()) {
    UtilityFunctions::push_error("Voxel_Generator::loading_failure: Failed at "
                                 "loading marching cube cases...");
    UtilityFunctions::push_error("System can't progress without successfull "
                                 "loaded cases and is thereby stopping...");

    get_tree()->quit();
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
bool Voxel_Generator::generate_debug_grid(Voxel_Object &a_object) {
  const size_t grid_size = m_object_width * m_object_height * m_object_depth;

  for (int index = 0; index < grid_size; index++) {
    Voxel *current = new Voxel();
    // instantiate debug ball at index
    current->center = _create_debug_ball(index);
    a_object.add_child(current->center);
    _set_debug_ball_material(current->center, m_test_voxel_structure[index]);

    // TODO: add debug vector
    // a_object.push_back_voxel(current);
    UtilityFunctions::print("Generated ", index, " voxel");
  }

  return true;
}

bool Voxel_Generator::generate_mesh_instance(Voxel_Object &a_object) {
  UtilityFunctions::print("Generating mesh");
  Mesh_Data *mesh_data = new Mesh_Data();

  // for (size_t i = 0; i < a_object.get_voxels_size(); i++)
  //   _find_marching_case(a_object.get_byte_representation_at(i));

  UtilityFunctions::print("Pack Mesh Data into Collection");
  // 5. Pack into ARRAY_MAX-sized ARRAY_MAX-sized
  mesh_data->collection.resize(Mesh::ARRAY_MAX);
  mesh_data->collection[Mesh::ARRAY_VERTEX] = mesh_data->vertices;
  mesh_data->collection[Mesh::ARRAY_NORMAL] = mesh_data->normals;
  mesh_data->collection[Mesh::ARRAY_TEX_UV] = mesh_data->uvs;
  mesh_data->collection[Mesh::ARRAY_COLOR] = mesh_data->colors;

  UtilityFunctions::print("Build mesh surface");
  // 6. Build the mesh surface
  Ref<ArrayMesh> mesh;
  mesh.instantiate();
  mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES,
                                mesh_data->collection);

  UtilityFunctions::print("Instantiate mesh instance");
  // 7. Material so vertex colors show and its visible from both sides
  Ref<StandardMaterial3D> material;
  material.instantiate();
  material->set_flag(BaseMaterial3D::FLAG_ALBEDO_FROM_VERTEX_COLOR, true);
  material->set_cull_mode(BaseMaterial3D::CULL_BACK); // draw both faces
  mesh->surface_set_material(0, material);

  a_object.set_mesh_instance(mesh);

  UtilityFunctions::print("Finished generating mesh instance");
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

void Voxel_Generator::_create_voxel_body(Voxel *a_voxel,
                                         Mesh_Data &a_mesh_data) {
  if (a_voxel == nullptr) {
    UtilityFunctions::push_error("Temp_Voxel is empty");
    return;
  }
  // create vertices
  a_mesh_data.vertices.push_back(a_voxel->top());
  a_mesh_data.vertices.push_back(a_voxel->front());
  a_mesh_data.vertices.push_back(a_voxel->left());

  a_mesh_data.vertices.push_back(a_voxel->top());
  a_mesh_data.vertices.push_back(a_voxel->left());
  a_mesh_data.vertices.push_back(a_voxel->back());

  a_mesh_data.vertices.push_back(a_voxel->top());
  a_mesh_data.vertices.push_back(a_voxel->back());
  a_mesh_data.vertices.push_back(a_voxel->right());

  a_mesh_data.vertices.push_back(a_voxel->top());
  a_mesh_data.vertices.push_back(a_voxel->right());
  a_mesh_data.vertices.push_back(a_voxel->front());

  a_mesh_data.vertices.push_back(a_voxel->front());
  a_mesh_data.vertices.push_back(a_voxel->bot());
  a_mesh_data.vertices.push_back(a_voxel->left());

  a_mesh_data.vertices.push_back(a_voxel->left());
  a_mesh_data.vertices.push_back(a_voxel->bot());
  a_mesh_data.vertices.push_back(a_voxel->back());

  a_mesh_data.vertices.push_back(a_voxel->back());
  a_mesh_data.vertices.push_back(a_voxel->bot());
  a_mesh_data.vertices.push_back(a_voxel->right());

  a_mesh_data.vertices.push_back(a_voxel->right());
  a_mesh_data.vertices.push_back(a_voxel->bot());
  a_mesh_data.vertices.push_back(a_voxel->front());

  // 2. Nora_mals - all face +Z so the flat triangle is lit from the
  // front-facing
  for (int i = 0; i < 24; i++) {
    a_mesh_data.normals.push_back(Vector3(0.0, 0.0, 1.0));
  }

  // 3. UVs (optional, for texturing)
  for (int i = 0; i < 24; i += 3) {
    a_mesh_data.uvs.push_back(Vector2(0.5, 0.0));
    a_mesh_data.uvs.push_back(Vector2(0.0, 1.0));
    a_mesh_data.uvs.push_back(Vector2(1.0, 1.0));
  }

  // 4. Vertex Colors (optional)
  for (int i = 0; i < 24; i += 3) {
    a_mesh_data.colors.push_back(Color(1, 0, 0));
    a_mesh_data.colors.push_back(Color(0, 1, 0));
    a_mesh_data.colors.push_back(Color(0, 0, 1));
  }
}

/**
 * Takes in a index of
 *
 * NOTE: Order of general direction
 * 1. wide - x positve
 * 2. high - y positive
 * 3. deep - z positive
 */
void Voxel_Generator::_find_marching_case(Voxel_Object &a_object,
                                          const int a_index) {
  // 1. get voxel densities in OGD
  // std::uint8_t density_byte =
  //   ((a_object.get << 0) |
  //   (() << 1) |
  //   (() << 2) |
  //   (() << 3) |
  //   (() << 4) |
  //   (() << 5) |
  //   (() << 6) |
  //   (() << 7);

  // 2. get possible case's by full_voxel count
  // 3. find correct case with correctio orientation
  // 4. return case's vertices with orientation
}

bool Voxel_Generator::_load_marching_cube_cases() {
  bool success_state = true;
  size_t successful_loads = 0;

  String cases_dir_path = ProjectSettings::get_singleton()->globalize_path(
      "res://marching-cubes_cases/");

  // NOTE: Do not break for loop for one file...
  // Save and continue, thereby we get the states for all present files
  for (const auto &entry :
       std::filesystem::directory_iterator(cases_dir_path.utf8().get_data())) {
    if (entry.path().filename() == "template.json") {
      continue;
    }

    UtilityFunctions::print("Voxel_Generator::load_mc_cases: ",
                            entry.path().filename().c_str());

    // 1. load json
    std::ifstream file(entry.path());
    if (!file.is_open()) {
      UtilityFunctions::push_error("Voxel_Generator::load_mc_cases: FAILED..");
      UtilityFunctions::push_warning("Failed to load [",
                                     entry.path().filename().c_str(), "]");

      success_state = false;
      continue;
    }

    // 2. parse and check file
    nlohmann::json data = nlohmann::json::parse(file, nullptr, false);
    if (data.is_discarded()) {
      UtilityFunctions::push_warning(
          "Voxel_Generator::load_mc_cases: Failed to parse json file");

      success_state = false;
      continue;
    }

    // 3. create case from json
    std::vector<std::string> vertices;
    for (auto &vert : data["vertices"]) {
      std::string chars = vert.get<std::string>();
      vertices.push_back(chars);
    }
    MC_Case *current_case =
        new MC_Case(data["filled_voxels"].get<int>(),
                    data["ignore_count"].get<bool>(), vertices);

    m_marching_cube_cases.push_back(current_case);
    // TODO: add remaining cases

    successful_loads++;
  }

  UtilityFunctions::print("Voxel_Generator::load_mc_cases: Finished Succesful");
  UtilityFunctions::print(
      "[", successful_loads, "] case", (successful_loads > 1 ? "s" : ""),
      (successful_loads > 1 ? " are " : " is "), "now ready to be used.");

  return success_state;
}
