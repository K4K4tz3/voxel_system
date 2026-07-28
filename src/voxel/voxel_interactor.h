#ifndef VOXEL_INTERACTOR_H
#define VOXEL_INTERACTOR_H

#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/variant/node_path.hpp>

namespace godot {

class Voxel_Interactor : public Node3D {
  GDCLASS(Voxel_Interactor, Node3D)

private:
  double mouse_sensitivity = 0.002;

  NodePath m_target_path;
  Node3D *m_target = nullptr;

  Vector2 m_mouse_motion = Vector2();
  bool m_interact = false;

protected:
  static void _bind_methods();

public:
  Voxel_Interactor();
  ~Voxel_Interactor();

  void _ready() override;
  void _process();
  void _unhandled_input(const Ref<InputEvent> &event) override;

  void set_target_path(const NodePath &a_path);
  NodePath get_target_path() const;
};

} // namespace godot

#endif
