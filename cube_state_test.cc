#include "gtest/gtest.h"

#include "cube_state.h"

TEST(CubeStateTest, InitCubeStateSucceed) {
  CubeState cube_state;
  EXPECT_EQ(CubeState::Color::COLOR_UNSPECIFIED,
            cube_state.GetColor(CubeState::Face::F, CubeState::Position::E_L));
  EXPECT_EQ(CubeState::Color::COLOR_UNSPECIFIED,
            cube_state.GetColor(CubeState::Face::D, CubeState::Position::C_RD));
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
