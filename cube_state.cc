#include "cube_state.h"

#include <map>
#include <sstream>
#include <string>

CubeState::CubeState() {
  std::map<Face, Color> face_to_color = {
      {Face::F, Color::GREEN},  {Face::R, Color::ORANGE},
      {Face::B, Color::BLUE},   {Face::L, Color::RED},
      {Face::U, Color::YELLOW}, {Face::D, Color::WHITE}};
  for (const auto &[face, color] : face_to_color) {
    for (int position = 0; position < N_POSITIONS; position++) {
      _colors[face][position] = color;
    }
  }
}

void CubeState::SetColor(const Face face, const Position position,
                         const CubeState::Color color) {
  _colors[face][position] = color;
}

CubeState::Color CubeState::GetColor(const Face face,
                                     const Position position) const {
  return _colors[face][position];
}

std::string CubeState::GetColorAlias(const Face face,
                                     const Position position) const {
  Color color = _colors[face][position];
  switch (color) {
  case Color::RED:
    return "R";
  case Color::BLUE:
    return "B";
  case Color::ORANGE:
    return "O";
  case Color::GREEN:
    return "G";
  case Color::WHITE:
    return "W";
  case Color::YELLOW:
    return "Y";
  default:
    return "?";
  }
};

std::string CubeState::GetDebugString() const {
  std::stringstream ss;
  // Builds U face.
  ss << "      ";
  ss << "-------" << std::endl;
  ss << "      ";
  ss << "|" << GetColorAlias(Face::U, Position::C_LU) << "|"
     << GetColorAlias(Face::U, Position::E_U) << "|"
     << GetColorAlias(Face::U, Position::C_RU) << "|" << std::endl;
  ss << "      ";
  ss << "|" << GetColorAlias(Face::U, Position::E_L) << "|"
     << GetColorAlias(Face::U, Position::C) << "|"
     << GetColorAlias(Face::U, Position::E_R) << "|" << std::endl;
  ss << "      ";
  ss << "|" << GetColorAlias(Face::U, Position::C_LD) << "|"
     << GetColorAlias(Face::U, Position::E_D) << "|"
     << GetColorAlias(Face::U, Position::C_RD) << "|" << std::endl;

  // Builds L, F, R, B faces.
  ss << "-------------------------" << std::endl;
  ss << "|" << GetColorAlias(Face::L, Position::C_LU) << "|"
     << GetColorAlias(Face::L, Position::E_U) << "|"
     << GetColorAlias(Face::L, Position::C_RU) << "|";
  ss << GetColorAlias(Face::F, Position::C_LU) << "|"
     << GetColorAlias(Face::F, Position::E_U) << "|"
     << GetColorAlias(Face::F, Position::C_RU) << "|";
  ss << GetColorAlias(Face::R, Position::C_LU) << "|"
     << GetColorAlias(Face::R, Position::E_U) << "|"
     << GetColorAlias(Face::R, Position::C_RU) << "|";
  ss << GetColorAlias(Face::B, Position::C_LU) << "|"
     << GetColorAlias(Face::B, Position::E_U) << "|"
     << GetColorAlias(Face::B, Position::C_RU) << "|" << std::endl;

  ss << "|" << GetColorAlias(Face::L, Position::E_L) << "|"
     << GetColorAlias(Face::L, Position::C) << "|"
     << GetColorAlias(Face::L, Position::E_R) << "|";
  ss << GetColorAlias(Face::F, Position::E_L) << "|"
     << GetColorAlias(Face::F, Position::C) << "|"
     << GetColorAlias(Face::F, Position::E_R) << "|";
  ss << GetColorAlias(Face::R, Position::E_L) << "|"
     << GetColorAlias(Face::R, Position::C) << "|"
     << GetColorAlias(Face::R, Position::E_R) << "|";
  ss << GetColorAlias(Face::B, Position::E_L) << "|"
     << GetColorAlias(Face::B, Position::C) << "|"
     << GetColorAlias(Face::B, Position::E_R) << "|" << std::endl;

  ss << "|" << GetColorAlias(Face::L, Position::C_LD) << "|"
     << GetColorAlias(Face::L, Position::E_D) << "|"
     << GetColorAlias(Face::L, Position::C_RD) << "|";
  ss << GetColorAlias(Face::F, Position::C_LD) << "|"
     << GetColorAlias(Face::F, Position::E_D) << "|"
     << GetColorAlias(Face::F, Position::C_RD) << "|";
  ss << GetColorAlias(Face::R, Position::C_LD) << "|"
     << GetColorAlias(Face::R, Position::E_D) << "|"
     << GetColorAlias(Face::R, Position::C_RD) << "|";
  ss << GetColorAlias(Face::B, Position::C_LD) << "|"
     << GetColorAlias(Face::B, Position::E_D) << "|"
     << GetColorAlias(Face::B, Position::C_RD) << "|" << std::endl;
  ss << "-------------------------" << std::endl;

  // Builds D face.
  ss << "      ";
  ss << "|" << GetColorAlias(Face::D, Position::C_LU) << "|"
     << GetColorAlias(Face::D, Position::E_U) << "|"
     << GetColorAlias(Face::D, Position::C_RU) << "|" << std::endl;
  ss << "      ";
  ss << "|" << GetColorAlias(Face::D, Position::E_L) << "|"
     << GetColorAlias(Face::D, Position::C) << "|"
     << GetColorAlias(Face::D, Position::E_R) << "|" << std::endl;
  ss << "      ";
  ss << "|" << GetColorAlias(Face::D, Position::C_LD) << "|"
     << GetColorAlias(Face::D, Position::E_D) << "|"
     << GetColorAlias(Face::D, Position::C_RD) << "|" << std::endl;
  ss << "      ";
  ss << "-------" << std::endl;
  return ss.str();
}
