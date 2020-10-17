#include "gtest/gtest.h"

#include "cube.h"
#include "cube_state.h"
#include "instruction.h"

using Face = CubeState::Face;
using Position = CubeState::Position;
using Turn = Instruction::Turn;

TEST(CubeTest, MoveUpFace) {
  Cube cube;
  cube.Move(Turn::F);
  EXPECT_EQ("      -------\n"
            "      |Y|Y|Y|\n"
            "      |Y|Y|Y|\n"
            "      |R|R|R|\n"
            "-------------------------\n"
            "|R|R|W|G|G|G|Y|O|O|B|B|B|\n"
            "|R|R|W|G|G|G|Y|O|O|B|B|B|\n"
            "|R|R|W|G|G|G|Y|O|O|B|B|B|\n"
            "-------------------------\n"
            "      |O|O|O|\n"
            "      |W|W|W|\n"
            "      |W|W|W|\n"
            "      -------\n",
            cube.GetState().GetDebugString());
}

TEST(CubeTest, MoveBackFace) {
  Cube cube;
  cube.Move(Turn::B);
  EXPECT_EQ("      -------\n"
            "      |O|O|O|\n"
            "      |Y|Y|Y|\n"
            "      |Y|Y|Y|\n"
            "-------------------------\n"
            "|Y|R|R|G|G|G|O|O|W|B|B|B|\n"
            "|Y|R|R|G|G|G|O|O|W|B|B|B|\n"
            "|Y|R|R|G|G|G|O|O|W|B|B|B|\n"
            "-------------------------\n"
            "      |W|W|W|\n"
            "      |W|W|W|\n"
            "      |R|R|R|\n"
            "      -------\n",
            cube.GetState().GetDebugString());
}

TEST(CubeTest, MoveDownFaceCounterclockwise) {
  Cube cube;
  cube.Move(Turn::D_);
  EXPECT_EQ("      -------\n"
            "      |Y|Y|Y|\n"
            "      |Y|Y|Y|\n"
            "      |Y|Y|Y|\n"
            "-------------------------\n"
            "|R|R|R|G|G|G|O|O|O|B|B|B|\n"
            "|R|R|R|G|G|G|O|O|O|B|B|B|\n"
            "|G|G|G|O|O|O|B|B|B|R|R|R|\n"
            "-------------------------\n"
            "      |W|W|W|\n"
            "      |W|W|W|\n"
            "      |W|W|W|\n"
            "      -------\n",
            cube.GetState().GetDebugString());
}

TEST(CubeTest, MoveRightFaceCounterclockwise) {
  Cube cube;
  cube.Move(Turn::R_);
  EXPECT_EQ("      -------\n"
            "      |Y|Y|B|\n"
            "      |Y|Y|B|\n"
            "      |Y|Y|B|\n"
            "-------------------------\n"
            "|R|R|R|G|G|Y|O|O|O|W|B|B|\n"
            "|R|R|R|G|G|Y|O|O|O|W|B|B|\n"
            "|R|R|R|G|G|Y|O|O|O|W|B|B|\n"
            "-------------------------\n"
            "      |W|W|G|\n"
            "      |W|W|G|\n"
            "      |W|W|G|\n"
            "      -------\n",
            cube.GetState().GetDebugString());
}

TEST(CubeTest, MulitpleMoves) {
  Cube cube;
  cube.Move(Turn::R_);
  cube.Move(Turn::F);
  EXPECT_EQ("      -------\n"
            "      |Y|Y|B|\n"
            "      |Y|Y|B|\n"
            "      |R|R|R|\n"
            "-------------------------\n"
            "|R|R|W|G|G|G|Y|O|O|W|B|B|\n"
            "|R|R|W|G|G|G|Y|O|O|W|B|B|\n"
            "|R|R|G|Y|Y|Y|B|O|O|W|B|B|\n"
            "-------------------------\n"
            "      |O|O|O|\n"
            "      |W|W|G|\n"
            "      |W|W|G|\n"
            "      -------\n",
            cube.GetState().GetDebugString());
  cube.Move(Turn::L_);
  EXPECT_EQ("      -------\n"
            "      |G|Y|B|\n"
            "      |G|Y|B|\n"
            "      |Y|R|R|\n"
            "-------------------------\n"
            "|W|W|G|O|G|G|Y|O|O|W|B|R|\n"
            "|R|R|R|W|G|G|Y|O|O|W|B|Y|\n"
            "|R|R|R|W|Y|Y|B|O|O|W|B|Y|\n"
            "-------------------------\n"
            "      |B|O|O|\n"
            "      |B|W|G|\n"
            "      |B|W|G|\n"
            "      -------\n",
            cube.GetState().GetDebugString());
  cube.Move(Turn::D);
  EXPECT_EQ("      -------\n"
            "      |G|Y|B|\n"
            "      |G|Y|B|\n"
            "      |Y|R|R|\n"
            "-------------------------\n"
            "|W|W|G|O|G|G|Y|O|O|W|B|R|\n"
            "|R|R|R|W|G|G|Y|O|O|W|B|Y|\n"
            "|W|B|Y|R|R|R|W|Y|Y|B|O|O|\n"
            "-------------------------\n"
            "      |B|B|B|\n"
            "      |W|W|O|\n"
            "      |G|G|O|\n"
            "      -------\n",
            cube.GetState().GetDebugString());
}
