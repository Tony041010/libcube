#include "gtest/gtest.h"

#include "cube_state.h"

TEST(CubeStateTest, InitCubeStateSucceed) {
  CubeState cube_state;
  EXPECT_EQ(CubeState::Color::GREEN,
            cube_state.GetColor(CubeState::Face::F, CubeState::Position::E_L));
  EXPECT_EQ(CubeState::Color::WHITE,
            cube_state.GetColor(CubeState::Face::D, CubeState::Position::C_RD));
  EXPECT_EQ(CubeState::Color::RED,
            cube_state.GetColor(CubeState::Face::L, CubeState::Position::C_RU));
}

TEST(CubeStateTest, SetAndGetColorSucceed) {
  CubeState cube_state;
  cube_state.SetColor(CubeState::Face::F, CubeState::Position::E_L,
                      CubeState::Color::RED);
  EXPECT_EQ(CubeState::Color::RED,
            cube_state.GetColor(CubeState::Face::F, CubeState::Position::E_L));
}

TEST(CubeStateTest, SetAndGetColorTwiceSucceed) {
  CubeState cube_state;
  cube_state.SetColor(CubeState::Face::F, CubeState::Position::E_L,
                      CubeState::Color::RED);
  EXPECT_EQ(CubeState::Color::RED,
            cube_state.GetColor(CubeState::Face::F, CubeState::Position::E_L));
  cube_state.SetColor(CubeState::Face::F, CubeState::Position::E_L,
                      CubeState::Color::BLUE);
  EXPECT_EQ(CubeState::Color::BLUE,
            cube_state.GetColor(CubeState::Face::F, CubeState::Position::E_L));
}

TEST(CubeStateTest, GetDebugStringSucceed) {
  CubeState cube_state;
  EXPECT_EQ("      -------\n"
            "      |Y|Y|Y|\n"
            "      |Y|Y|Y|\n"
            "      |Y|Y|Y|\n"
            "-------------------------\n"
            "|R|R|R|G|G|G|O|O|O|B|B|B|\n"
            "|R|R|R|G|G|G|O|O|O|B|B|B|\n"
            "|R|R|R|G|G|G|O|O|O|B|B|B|\n"
            "-------------------------\n"
            "      |W|W|W|\n"
            "      |W|W|W|\n"
            "      |W|W|W|\n"
            "      -------\n",
            cube_state.GetDebugString());
}
