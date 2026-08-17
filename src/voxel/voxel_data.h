#ifndef VOXEL_DATA_H
#define VOXEL_DATA_H

#include <vector>

namespace godot {

struct Voxel_Data {
  std::vector<int> densities;
  int width;
  int height;
  int depth;
};

} // namespace godot

#endif
