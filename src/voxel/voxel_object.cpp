#include "voxel_object.h"

#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Voxel_Object::_bind_methods() {
  ClassDB::bind_method(D_METHOD("build_cube"), &Voxel_Object::build_cube);
}

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

void Voxel_Object::build_cube() {
  // 1. Vertex positions (counter-clockwise winding = front-facing)
  PackedVector3Array vertices;
  for (int i = 0; i < M_VERT_COUNT; i += 3) {
    vertices.push_back(get_vertice_coords(M_VERT_ORDER[i + 0]));
    vertices.push_back(get_vertice_coords(M_VERT_ORDER[i + 1]));
    vertices.push_back(get_vertice_coords(M_VERT_ORDER[i + 2]));
  }

  // 2. Normals - all face +Z so the flat triangle is lit from the front-facing
  PackedVector3Array normals;
  for (int i = 0; i < M_VERT_COUNT; i++) {
    normals.push_back(Vector3(0.0, 0.0, 1.0));
  }

  // 3. UVs (optional, for texturing)
  PackedVector2Array uvs;
  for (int i = 0; i < M_VERT_COUNT; i += 3) {
    uvs.push_back(Vector2(0.5, 0.0));
    uvs.push_back(Vector2(0.0, 1.0));
    uvs.push_back(Vector2(1.0, 1.0));
  }

  // 4. Vertex Colors (optional)
  PackedColorArray colors;
  for (int i = 0; i < M_VERT_COUNT; i += 3) {
    colors.push_back(Color(1, 0, 0));
    colors.push_back(Color(0, 1, 0));
    colors.push_back(Color(0, 0, 1));
  }

  // 5. Pack into ARRAY_MAX-sized ARRAY_MAX-sized
  Array arrays;
  arrays.resize(Mesh::ARRAY_MAX);
  arrays[Mesh::ARRAY_VERTEX] = vertices;
  arrays[Mesh::ARRAY_NORMAL] = normals;
  arrays[Mesh::ARRAY_TEX_UV] = uvs;
  arrays[Mesh::ARRAY_COLOR] = colors;

  // 6. Build the mesh surface
  Ref<ArrayMesh> mesh;
  mesh.instantiate();
  mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

  // 7. Material so vertex colors show and its visible from both sides
  Ref<StandardMaterial3D> material;
  material.instantiate();
  material->set_flag(BaseMaterial3D::FLAG_ALBEDO_FROM_VERTEX_COLOR, true);
  material->set_cull_mode(BaseMaterial3D::CULL_BACK); // draw both faces
  mesh->surface_set_material(0, material);

  m_mesh_instance->set_mesh(mesh);
}
