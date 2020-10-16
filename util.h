#ifndef UTIL_H
#define UTIL_H

#include "cube_state.h"
#include "instruction.h"

namespace util {
CubeState::Face GetTargetFace(Instruction::Turn turn);
}

#endif
