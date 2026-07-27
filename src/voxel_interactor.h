#ifndef VOXEL_INTERACTOR_H
#define VOXEL_INTERACTOR_H

#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/node3d.hpp>

namespace godot {

class Voxel_Interactor : public Node3D {
  GDCLASS(Voxel_Interactor, Node3D)

private:
  double mouse_sensitivity = 0.002;

  Node3D *cube = get_node<Node3D>("../Cube_Generatable");

  Vector2 m_mouse_motion = Vector2();

protected:
  static void _bind_methods();

public:
  Voxel_Interactor();
  ~Voxel_Interactor();

  void _ready() override;
  void _process();
  void _unhandled_input(const Ref<InputEvent> &event) override;
};

} // namespace godot

#endif
