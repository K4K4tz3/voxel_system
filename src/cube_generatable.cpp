#include "cube_generatable.h"

#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Cube_Generatable::_bind_methods() {
  ClassDB::bind_method(D_METHOD("build_cube"), &Cube_Generatable::build_cube);
}

Cube_Generatable::Cube_Generatable() {
  mesh_instance = memnew(MeshInstance3D);
  add_child(mesh_instance);
}

Cube_Generatable::~Cube_Generatable() {}

void Cube_Generatable::_ready() { build_cube(); }

void Cube_Generatable::build_cube() {
  // 1. Vertex positions (counter-clockwise winding = front-facing)
  PackedVector3Array vertices;
  vertices.push_back(Vector3(0.0, 1.0, 0.0));   // top
  vertices.push_back(Vector3(-1.0, -1.0, 0.0)); // bottom-left
  vertices.push_back(Vector3(1.0, 1.0, 0.0));   // bottom-right

  // 2. Normals - all face +Z so the flat triangle is lit from the front-facing
  PackedVector3Array normals;
  for (int i = 0; i < 3; i++) {
    normals.push_back(Vector3(0.0, 0.0, 1.0));
  }

  // 3. UVs (optional, for texturing)
  PackedVector2Array uvs;
  uvs.push_back(Vector2(0.5, 0.0));
  uvs.push_back(Vector2(0.0, 1.0));
  uvs.push_back(Vector2(1.0, 1.0));

  // 4. Vertex Colors (optional)
  PackedColorArray colors;
  colors.push_back(Color(1, 0, 0));
  colors.push_back(Color(0, 1, 0));
  colors.push_back(Color(0, 0, 1));

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
  material->set_cull_mode(BaseMaterial3D::CULL_DISABLED); // draw both faces
  mesh->surface_set_material(0, material);

  mesh_instance->set_mesh(mesh);
}
