#ifndef UTIL_H
#define UTIL_H

#include "cube_state.h"
#include "instruction.h"

CubeState::Face GetTargetFace(Instruction::Turn turn);

#endif
