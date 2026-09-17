#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS

#include <bitset>
#include <doctest/doctest.h>

#include "voxel/voxel_manager.h"

namespace godot {

TEST_CASE("create manager") {
  Voxel_Manager *manager = memnew(godot::Voxel_Manager);

  REQUIRE(manager != nullptr);

  Voxel_Object *object = nullptr;
  SUBCASE("Create Voxel Object") {
    CHECK(manager->load_from_file(true));
    object = &manager->get_object_ref(0);
    CHECK(object != nullptr);
  }

  SUBCASE("Get Index from Position") {
    int index = object->get_index_from_position(Vector3{
        -1,
        -1,
        -1,
    });
    CHECK(index == 0);

    // center check
    index = object->get_index_from_position(Vector3{0, 0, 0});
    CHECK(index == 13);

    // out of bounds check
    index = object->get_index_from_position(Vector3{+2, 0, 0});
    CHECK(index == -1);
  }

  SUBCASE("Check Byte Rep") {
    std::uint8_t byte = object->get_byte_rep_at(Vector3{0, 0, 0});
    CHECK(byte == 0b01111111);

    byte = object->get_byte_rep_at(Vector3{-1, -1, -1});
    CHECK(byte == 0b00000000);
    MESSAGE("actual: ", std::bitset<8>(byte).to_string());
  }

  memdelete(manager);
}

} // namespace godot
