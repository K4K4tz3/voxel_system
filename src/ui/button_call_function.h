#ifndef BUTTON_CALL_FUNCTION_H
#define BUTTON_CALL_FUNCTION_H

#include <godot_cpp/classes/texture_button.hpp>

#include <godot_cpp/variant/node_path.hpp>

namespace godot {

class Button_Call_Function : public TextureButton {
  GDCLASS(Button_Call_Function, TextureButton)

private:
  NodePath m_call_path;
  StringName m_function_name;

  void on_pressed();

protected:
  static void _bind_methods();

public:
  void _ready() override;

  void set_call_path(const NodePath &a_Path) { m_call_path = a_Path; };
  NodePath get_call_path() const { return m_call_path; };

  void set_function_name(const StringName a_function_name) {
    m_function_name = a_function_name;
  };
  StringName get_function_name() const { return m_function_name; };
};

} // namespace godot

#endif
