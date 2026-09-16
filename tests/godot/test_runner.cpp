#include "test_runner.h"

#include <doctest/doctest.h>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void Test_Runner::_bind_methods() {
  ClassDB::bind_method(D_METHOD("run_tests"), &Test_Runner::run_tests);
}

void Test_Runner::_ready() {
  if (Engine::get_singleton()->is_editor_hint()) {
    return;
  }

  call_deferred("run_tests");
}

void Test_Runner::run_tests() {
  doctest::Context context;

  int result = context.run();

  get_tree()->quit(result);
}
