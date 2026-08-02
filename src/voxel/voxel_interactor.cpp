#include "voxel_interactor.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

using namespace godot;

void Voxel_Interactor::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_target_path", "path"),
                       &Voxel_Interactor::set_target_path);

  ClassDB::bind_method(D_METHOD("get_target_path"),
                       &Voxel_Interactor::get_target_path);

  ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "target_path",
                            PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Node3D"),
               "set_target_path", "get_target_path");

  ClassDB::bind_method(D_METHOD("set_target_from_path"),
                       &Voxel_Interactor::set_target_from_path);
}

Voxel_Interactor::Voxel_Interactor() {}
Voxel_Interactor::~Voxel_Interactor() {}

void Voxel_Interactor::_ready() {
  Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
}

void Voxel_Interactor::_process() {
  // UtilityFunctions::print(m_mouse_motion.x, m_mouse_motion.y);
  // UtilityFunctions::print((float)m_target->get_global_rotation_degrees().y);

  if (m_interact) {
    Vector3 rotation = m_target->get_rotation();

    float rotation_y = m_target->get_global_rotation_degrees().y;
    if (-90 < rotation_y && rotation_y < 90)
      rotation.x += m_mouse_motion.y * mouse_sensitivity;
    else
      rotation.x -= m_mouse_motion.y * mouse_sensitivity;

    rotation.y += m_mouse_motion.x * mouse_sensitivity;

    m_target->set_rotation(rotation);
  }

  if (m_mouse_motion != Vector2(0, 0))
    m_mouse_motion = Vector2{0, 0};
}

void Voxel_Interactor::_input(const Ref<InputEvent> &event) {}
void Voxel_Interactor::_unhandled_input(const Ref<InputEvent> &event) {
  Ref<InputEventMouseMotion> mouse_motion = event;
  Ref<InputEventMouseButton> mouse_button = event;

  if (mouse_motion.is_valid()) {
    m_mouse_motion = mouse_motion->get_relative();
  }

  if (mouse_button.is_valid() &&
      mouse_button->get_button_index() == MouseButton::MOUSE_BUTTON_LEFT) {
    if (mouse_button->is_pressed())
      m_interact = true;
    else if (mouse_button->is_released())
      m_interact = false;
  }
}

void Voxel_Interactor::set_target_path(const NodePath &a_path) {
  m_target_path = a_path;
}

NodePath Voxel_Interactor::get_target_path() const { return m_target_path; }

void Voxel_Interactor::set_target_from_path(const NodePath &a_path) {
  m_target_path = a_path;
  m_target = Object::cast_to<Node3D>(get_node_or_null(m_target_path));

  if (m_target == nullptr) {
    UtilityFunctions::printerr("Could not find target Node3D at path: ",
                               m_target_path);
  }
  UtilityFunctions::print("Recieved voxel_object as target");
}
