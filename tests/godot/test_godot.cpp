#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS

#include <doctest/doctest.h>

#include "voxel/voxel_manager.h"

namespace godot {

TEST_CASE("sanity check") { CHECK(1 + 1 == 2); }
TEST_CASE("create manager") {
  Voxel_Manager *manager = memnew(godot::Voxel_Manager);

  REQUIRE(manager != nullptr);

  memdelete(manager);
}

} // namespace godot
