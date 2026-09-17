#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS

#include <doctest/doctest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "../src/voxel/mc_case.h"
#include "../src/voxel/voxel_generator.h"
#include "../src/voxel/voxel_manager.h"

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

TEST_CASE("Parse Checking") {
  INFO("Data: mc_case_test.json");

  std::filesystem::path path = "tests/data/mc_case_test.json";
  auto absolute = std::filesystem::absolute(path);

  // 1. load json
  std::cout << "Absolute: " << absolute << '\n';
  std::cout << "Exists:   " << std::filesystem::exists(absolute) << '\n';
  std::cout << "Regular:  " << std::filesystem::is_regular_file(absolute)
            << '\n';

  errno = 0;
  std::ifstream file(absolute);
  bool open = file.is_open();
  REQUIRE(open);

  // 2. format to json
  nlohmann::json data = nlohmann::json::parse(file, nullptr, false);
  REQUIRE(!data.is_discarded());

  godot::MC_Case *mc_case = godot::Voxel_Generator::parse_mc_case(data);

  REQUIRE(mc_case != nullptr);
  CHECK(mc_case->get_filled_voxels() == 2);
  CHECK(mc_case->get_byte_rep(0) == 0b11000000);
}

// TEST_CASE("Byte representation creation at certain index") {
//   std::cout << "Create Object\n";
//   Voxel_Manager manager;
//   std::cout << "Load file\n";
//   manager.load_from_file(true);
//
//   std::cout << "Get Object from Manager\n";
//   Voxel_Object &object = manager.get_object_ref(0);
//
//   std::cout << "Get byte rep at pos from Object\n";
//   std::uint8_t default_pos = object.get_byte_rep_at(0);
//   CHECK(default_pos == 0b00000000);
// }
} // namespace godot
  //
