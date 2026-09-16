#ifndef MC_CASE_H
#define MC_CASE_H

#include <filesystem>
#include <string>
#include <vector>

namespace godot {

class MC_Case {
private:
  int m_filled_voxels;
  bool m_ignore_count;

  std::vector<std::uint8_t> m_byte_representation;
  std::vector<std::string> m_vertices;

protected:
public:
  MC_Case();
  MC_Case(const int a_filled_voxels, const bool a_ignore_count,
          const std::vector<std::uint8_t> a_bytes,
          const std::vector<std::string> a_vertices) {
    m_filled_voxels = a_filled_voxels;
    m_ignore_count = a_ignore_count;
    m_byte_representation = a_bytes;
    m_vertices = a_vertices;
  };

  int get_filled_voxels() const { return m_filled_voxels; };
  bool ignore_count() const { return m_ignore_count; };
  std::uint8_t get_byte_rep(size_t a_index) {
    return m_byte_representation[a_index];
  }
  std::vector<std::string> get_vertices() const { return m_vertices; };
};

}; // namespace godot

#endif
