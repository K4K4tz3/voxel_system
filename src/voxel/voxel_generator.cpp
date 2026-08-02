#include "voxel_generator.h"

#include "voxel_object.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Voxel_Generator::_bind_methods() {
  ClassDB::bind_method(D_METHOD("print_hello"), &Voxel_Generator::print_hello);
  ClassDB::bind_method(D_METHOD("spawn_voxel_object"),
                       &Voxel_Generator::spawn_voxel_object);
}

Voxel_Generator::Voxel_Generator() {}
Voxel_Generator::~Voxel_Generator() {}

void Voxel_Generator::spawn_voxel_object() {
  Voxel_Object *voxel_object = memnew(Voxel_Object);

  add_child(voxel_object);
  UtilityFunctions::print("Created voxel object");
};
