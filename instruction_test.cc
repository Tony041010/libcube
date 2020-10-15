#include "gtest/gtest.h"

#include "instruction.h"

TEST(InstructionTest, GetNameSucceed) {
  Instruction instruction_1(Instruction::Turn::B);
  EXPECT_EQ("B", instruction_1.GetName());

  Instruction instruction_2(Instruction::Turn::D_);
  EXPECT_EQ("D'", instruction_2.GetName());
}
