#ifndef VOXEL_FRAME_H
#define VOXEL_FRAME_H

#include "voxel.h"

namespace godot {

struct Voxel_Frame {
  Voxel *front_top_left;
  Voxel *front_top_right;
  Voxel *front_bot_right;
  Voxel *front_bot_left;
  Voxel *back_top_right;
  Voxel *back_top_left;
  Voxel *back_bot_left;
  Voxel *back_bot_right;
};

}; // namespace godot

#endif
