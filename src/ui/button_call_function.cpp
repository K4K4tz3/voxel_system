#include "button_call_function.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Button_Call_Function::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_call_path", "path"),
                       &Button_Call_Function::set_call_path);
  ClassDB::bind_method(D_METHOD("get_call_path"),
                       &Button_Call_Function::get_call_path);
  ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "m_target_path"),
               "set_call_path", "get_call_path");

  ClassDB::bind_method(D_METHOD("set_function_name", "path"),
                       &Button_Call_Function::set_function_name);
  ClassDB::bind_method(D_METHOD("get_function_name"),
                       &Button_Call_Function::get_function_name);
  ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "m_function_name"),
               "set_function_name", "get_function_name");

  ClassDB::bind_method(D_METHOD("on_pressed"),
                       &Button_Call_Function::on_pressed);
}

void Button_Call_Function::_ready() {
  Callable callback(this, "on_pressed");

  if (!is_connected("pressed", callback)) {
    connect("pressed", callback);
  }
}

void Button_Call_Function::on_pressed() {
  Node *target = get_node_or_null(m_call_path);
  UtilityFunctions::print("attempt call");

  if (target == nullptr) {
    UtilityFunctions::push_error(
        "Button_Call_Function: m_call_path does not point to a valid node.");
    return;
  }

  if (m_function_name.is_empty()) {
    UtilityFunctions::push_error(
        "Button_Call_Function: no m_function_name has been configured.");
    return;
  }

  target->call(m_function_name);
}
