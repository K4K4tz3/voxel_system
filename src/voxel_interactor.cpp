#include "voxel_interactor.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

using namespace godot;

void Voxel_Interactor::_bind_methods() {}

Voxel_Interactor::Voxel_Interactor() {}
Voxel_Interactor::~Voxel_Interactor() {}

void Voxel_Interactor::_ready() {
  Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
}

void Voxel_Interactor::_process() {
  UtilityFunctions::print(m_mouse_motion.x, m_mouse_motion.y);
}

void Voxel_Interactor::_unhandled_input(const Ref<InputEvent> &event) {
  Ref<InputEventMouseMotion> mouse_motion = event;

  if (mouse_motion.is_valid()) {
    m_mouse_motion = mouse_motion->get_relative();
  }
}
