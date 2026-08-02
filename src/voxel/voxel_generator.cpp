#include "voxel_generator.h"

#include "voxel_object.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Voxel_Generator::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_interactor_path", "path"),
                       &Voxel_Generator::set_interactor_path);

  ClassDB::bind_method(D_METHOD("get_interactor_path"),
                       &Voxel_Generator::get_interactor_path);

  ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "m_interactor_path"),
               "set_interactor_path", "get_interactor_path");

  ClassDB::bind_method(D_METHOD("spawn_voxel_object"),
                       &Voxel_Generator::spawn_voxel_object);
}

Voxel_Generator::Voxel_Generator() {}
Voxel_Generator::~Voxel_Generator() {}

void Voxel_Generator::_ready() {
  if (!m_interactor_path.is_empty()) {
    m_interactor =
        Object::cast_to<Voxel_Interactor>(get_node_or_null(m_interactor_path));
  } else {
    UtilityFunctions::push_warning("Voxel_Generator can't cast interactor");
    UtilityFunctions::push_error(
        "Voxel_Generator is missing: m_interactor_path");
  }
}

void Voxel_Generator::spawn_voxel_object() {
  Voxel_Object *voxel_object = memnew(Voxel_Object);

  add_child(voxel_object);
  UtilityFunctions::print("Created voxel object");

  // sent created object to interactor
  NodePath object_path = voxel_object->get_path();
  m_interactor->set_target_from_path(object_path);
};
