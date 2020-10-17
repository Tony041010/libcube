#include "gtest/gtest.h"

#include "cube_state.h"
#include "instruction.h"
#include "util.h"

using Face = CubeState::Face;
using Turn = Instruction::Turn;

TEST(UtilTest, GetTargetFaceSucceed) {
  EXPECT_EQ(Face::F, GetTargetFace(Turn::F));
  EXPECT_EQ(Face::B, GetTargetFace(Turn::B_));
}
