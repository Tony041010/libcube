#include "cube_state.h"

#include <map>

CubeState::CubeState() {
  std::map<Face, Color> face_to_color = {
      {Face::F, Color::GREEN},  {Face::R, Color::ORANGE},
      {Face::B, Color::BLUE},   {Face::L, Color::RED},
      {Face::U, Color::YELLOW}, {Face::D, Color::WHITE}};
  for (const auto &[face, color] : face_to_color) {
    for (int position = 0; position < N_POSITIONS; position++) {
      _colors[face][position] = color;
    }
  }
}

void CubeState::SetColor(const Face face, const Position position,
                         const CubeState::Color color) {
  _colors[face][position] = color;
}

CubeState::Color CubeState::GetColor(const Face face,
                                     const Position position) const {
  return _colors[face][position];
}
