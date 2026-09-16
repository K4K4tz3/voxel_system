#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <godot_cpp/classes/node.hpp>

namespace godot {

class Test_Runner : public Node {
  GDCLASS(Test_Runner, Node)

private:
protected:
  static void _bind_methods();

public:
  void _ready() override;
  void run_tests();
};

} // namespace godot

#endif
