#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/variant/packed_color_array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>

namespace godot {

struct Mesh_Data {
  PackedVector3Array vertices;
  PackedVector3Array normals;
  PackedVector2Array uvs;
  PackedColorArray colors;
  Array collection;
};
} // namespace godot

#endif
