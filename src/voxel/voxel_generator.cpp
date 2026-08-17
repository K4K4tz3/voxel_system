#include "voxel_generator.h"

#include "voxel_object.h"

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Voxel_Generator::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_interactor_path", "path"),
                       &Voxel_Generator::set_interactor_path);

  ClassDB::bind_method(D_METHOD("get_interactor_path"),
                       &Voxel_Generator::get_interactor_path);

  ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "interactor_path"),
               "set_interactor_path", "get_interactor_path");

  ClassDB::bind_method(D_METHOD("create_voxel_object"),
                       &Voxel_Generator::create_voxel_object);

  ClassDB::bind_method(D_METHOD("set_voxel_size", "voxel size"),
                       &Voxel_Generator::set_voxel_size);
  ClassDB::bind_method(D_METHOD("get_voxel_size"),
                       &Voxel_Generator::get_voxel_size);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "m_voxel_size"), "set_voxel_size",
               "get_voxel_size");

  ClassDB::bind_method(D_METHOD("set_object_width", "width"),
                       &Voxel_Generator::set_object_width);
  ClassDB::bind_method(D_METHOD("get_object_width"),
                       &Voxel_Generator::get_object_width);

  ClassDB::bind_method(D_METHOD("set_object_height", "height"),
                       &Voxel_Generator::set_object_height);
  ClassDB::bind_method(D_METHOD("get_object_height"),
                       &Voxel_Generator::get_object_height);

  ClassDB::bind_method(D_METHOD("set_object_depth", "depth"),
                       &Voxel_Generator::set_object_depth);
  ClassDB::bind_method(D_METHOD("get_object_depth"),
                       &Voxel_Generator::get_object_depth);

  ADD_GROUP("Object", "");

  ADD_PROPERTY(PropertyInfo(Variant::INT, "width"), "set_object_width",
               "get_object_width");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "height"), "set_object_height",
               "get_object_height");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "depth"), "set_object_depth",
               "get_object_depth");
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
}

bool Voxel_Generator::create_voxel_object() {
  UtilityFunctions::print("test");
  Voxel_Object *voxel_object = memnew(Voxel_Object);

  voxel_object->set_generator(this);

  auto data = std::make_unique<Voxel_Data>();
  data->width = m_object_width;
  data->height = m_object_height;
  data->depth = m_object_depth;

  if (!generate_grid(*data)) {
    UtilityFunctions::push_warning("Voxel_Generator: Failed to generate_grid");
    return false;
  }

  add_child(voxel_object);
  UtilityFunctions::print("Created voxel object");

  // sent created object to interactor
  NodePath object_path = voxel_object->get_path();
  m_interactor->set_target_from_path(object_path);

  return true;
}

bool Voxel_Generator::generate_grid(Voxel_Data &a_data) {
  // const int size = m_object_width * m_object_height * m_object_depth;

  // for (int i = 0; i < size; i++)
  //   a_data.densities.push_back(0);

  Ref<PackedScene> model =
      ResourceLoader::get_singleton()->load("res://ball.glb");

  Node3D *instance = Object::cast_to<Node3D>(model->instantiate());
  UtilityFunctions::print("generated grid");
  instance->set_position(Vector3(0, 0, 0));
  add_child(instance);

  return true;
}
