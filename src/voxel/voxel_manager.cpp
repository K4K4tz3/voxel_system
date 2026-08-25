#include "voxel_manager.h"

using namespace godot;

void Voxel_Manager::_bind_methods() {
  ClassDB::bind_method(D_METHOD("create_object"),
                       &Voxel_Manager::create_object);
}

bool Voxel_Manager::create_object() {
  Voxel_Object *object = memnew(Voxel_Object);

  if (object == nullptr) {
    UtilityFunctions::push_warning("Voxel_Manager: Failed to create object.");
    delete object;
    return false;
  } else {
    UtilityFunctions::print("Voxel_Manager: Succeeded in creating object.");
  }

  // auto data = std::make_unique<Voxel_Data>();
  // data->width = m_object_width;
  // data->height = m_object_height;
  // data->depth = m_object_depth;

  add_child(object);

  // Object got created successfully
  m_objects.push_back(object);
  return true;
}

bool Voxel_Manager::create_object_and_generate_default() {}
