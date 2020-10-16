#include "gtest/gtest.h"

#include "util.h"
#include "cube_state.h"
#include "instruction.h"

using Face = CubeState::Face;
using Turn = Instruction::Turn;

TEST(UtilTest, GetTargetFaceSucceed) {
  EXPECT_EQ(Face::F, util::GetTargetFace(Turn::F));
  EXPECT_EQ(Face::B, util::GetTargetFace(Turn::B_));
}
