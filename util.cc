#include <map>

#include "cube_state.h"
#include "instruction.h"
#include "util.h"

namespace {
using Face = CubeState::Face;
using Turn = Instruction::Turn;
} // namespace
Face GetTargetFace(Turn turn) {
  std::map<Turn, Face> turn_to_target_face = {
      {Turn::F, Face::F},  {Turn::R, Face::R},  {Turn::B, Face::B},
      {Turn::L, Face::L},  {Turn::D, Face::D},  {Turn::U, Face::U},
      {Turn::F_, Face::F}, {Turn::R_, Face::R}, {Turn::B_, Face::B},
      {Turn::L_, Face::L}, {Turn::D_, Face::D}, {Turn::U_, Face::U},
  };
  return turn_to_target_face[turn];
}
