#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "cube_state.h"
#include <vector>

using ::testing::ElementsAre;

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

TEST(CubeStateTest, GetFaces) {
  std::vector<CubeState::Face> faces = CubeState::GetFaces();
  ASSERT_EQ(faces.size(), 6);
  EXPECT_EQ(faces.at(0), CubeState::Face::F);
  EXPECT_EQ(faces.at(1), CubeState::Face::B);
  EXPECT_EQ(faces.at(2), CubeState::Face::L);
  EXPECT_EQ(faces.at(3), CubeState::Face::R);
  EXPECT_EQ(faces.at(4), CubeState::Face::U);
  EXPECT_EQ(faces.at(5), CubeState::Face::D);
}

TEST(CubeStateTest, GetPositions) {
  std::vector<CubeState::Position> positions = CubeState::GetPositions();
  ASSERT_EQ(positions.size(), 9);
  EXPECT_EQ(positions.at(0), CubeState::Position::C);
  EXPECT_EQ(positions.at(1), CubeState::Position::E_L);
  EXPECT_EQ(positions.at(2), CubeState::Position::E_R);
  EXPECT_EQ(positions.at(3), CubeState::Position::E_U);
  EXPECT_EQ(positions.at(4), CubeState::Position::E_D);
  EXPECT_EQ(positions.at(5), CubeState::Position::C_LU);
  EXPECT_EQ(positions.at(6), CubeState::Position::C_LD);
  EXPECT_EQ(positions.at(7), CubeState::Position::C_RU);
  EXPECT_EQ(positions.at(8), CubeState::Position::C_RD);
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
