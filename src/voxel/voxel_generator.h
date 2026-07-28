#ifndef VOXEL_GENERATOR_H
#define VOXEL_GENERATOR_H

#include <godot_cpp/classes/node.hpp>

namespace godot {

class Voxel_Generator : public Node {
  GDCLASS(Voxel_Generator, Node)

private:
protected:
  static void _bind_methods();

public:
  Voxel_Generator();
  ~Voxel_Generator();
};

} // namespace godot

#endif
