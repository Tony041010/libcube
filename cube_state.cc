#include "cube_state.h"

CubeState::CubeState() {
  for (int face = 0; face < N_FACES; face++) {
    for (int position = 0; position < N_POSITIONS; position++) {
      colors[face][position] = CubeState::Color::COLOR_UNSPECIFIED;
    }
  }
}

void CubeState::SetColor(const Face face, const Position position,
                         const CubeState::Color color) {
  colors[face][position] = color;
}

CubeState::Color CubeState::GetColor(const Face face,
                                     const Position position) const {
  return colors[face][position];
}
