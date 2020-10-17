#include "cube.h"

#include <assert.h>
#include <iostream>
#include <utility>
#include <vector>

#include "cube_state.h"
#include "instruction.h"
#include "util.h"

namespace {

using Turn = Instruction::Turn;
using Face = CubeState::Face;
using Position = CubeState::Position;
using Color = CubeState::Color;

bool IsClockWise(const Turn &turn) {
  return (turn == Turn::F || turn == Turn::R || turn == Turn::B ||
          turn == Turn::L || turn == Turn::U || turn == Turn::D);
}

void TurnFacePositionsClockWise(Face face, CubeState *state) {
  // Turns corners.
  Color buffer_corner_color = state->GetColor(face, Position::C_LU);
  state->SetColor(face, Position::C_LU, state->GetColor(face, Position::C_LD));
  state->SetColor(face, Position::C_LD, state->GetColor(face, Position::C_RD));
  state->SetColor(face, Position::C_RD, state->GetColor(face, Position::C_RU));
  state->SetColor(face, Position::C_RU, buffer_corner_color);
  // Turns edges.
  Color buffer_edge_color = state->GetColor(face, Position::E_L);
  state->SetColor(face, Position::E_L, state->GetColor(face, Position::E_D));
  state->SetColor(face, Position::E_D, state->GetColor(face, Position::E_R));
  state->SetColor(face, Position::E_R, state->GetColor(face, Position::E_U));
  state->SetColor(face, Position::E_U, buffer_edge_color);
}

void TurnFacePositionsCounterClockWise(Face face, CubeState *state) {
  // Turns corners.
  Color buffer_corner_color = state->GetColor(face, Position::C_LU);
  state->SetColor(face, Position::C_LU, state->GetColor(face, Position::C_RU));
  state->SetColor(face, Position::C_RU, state->GetColor(face, Position::C_RD));
  state->SetColor(face, Position::C_RD, state->GetColor(face, Position::C_LD));
  state->SetColor(face, Position::C_LD, buffer_corner_color);
  // Turns edges.
  Color buffer_edge_color = state->GetColor(face, Position::E_L);
  state->SetColor(face, Position::E_L, state->GetColor(face, Position::E_U));
  state->SetColor(face, Position::E_U, state->GetColor(face, Position::E_R));
  state->SetColor(face, Position::E_R, state->GetColor(face, Position::E_D));
  state->SetColor(face, Position::E_D, buffer_edge_color);
}

void TurnFacePositions(bool is_clockwise, Face face, CubeState *state) {
  if (is_clockwise) {
    TurnFacePositionsClockWise(face, state);
  } else {
    TurnFacePositionsCounterClockWise(face, state);
  }
}

/**
 * ShiftPositionsInGroup takes 12 positions and shift their corresponding colors
 * in group of size 3. E.g., say the corresponding colors of the input positions
 * are [C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12] the colors will
 * become [C4, C5, C6, C7, C8, C9, C10, C11, C12, C1, C2, C3].
 */
void ShiftPositionsInGroup(std::vector<std::pair<Face, Position>> positions,
                           bool should_reverse, CubeState *state) {
  if (should_reverse) {
    std::reverse(positions.begin(), positions.end());
  }

  int group_size = 3;
  int n_groups = 4;
  assert(group_size * n_groups == positions.size());

  std::vector<Color> buffer_colors;
  for (int i = 0; i < group_size; i++) {
    buffer_colors.emplace_back(
        state->GetColor(positions.at(i).first, positions.at(i).second));
  }

  int break_point = group_size * (n_groups - 1);
  for (int i = 0; i < break_point; i++) {
    state->SetColor(positions.at(i).first, positions.at(i).second,
                    state->GetColor(positions.at(i + group_size).first,
                                    positions.at(i + group_size).second));
  }

  for (int i = 0; i < group_size; i++) {
    state->SetColor(positions.at(break_point + i).first,
                    positions.at(break_point + i).second, buffer_colors.at(i));
  }
}

void TurnNeighborPositions(Instruction instruction, CubeState *state) {
  bool should_reverse = !IsClockWise(instruction.GetTurn());
  switch (instruction.GetTurn()) {
  case Turn::L:
  case Turn::L_:
    ShiftPositionsInGroup(
        {
            {Face::U, Position::C_LD},
            {Face::U, Position::E_L},
            {Face::U, Position::C_LU},
            {Face::B, Position::C_RU},
            {Face::B, Position::E_R},
            {Face::B, Position::C_RD},
            {Face::D, Position::C_LD},
            {Face::D, Position::E_L},
            {Face::D, Position::C_LU},
            {Face::F, Position::C_LD},
            {Face::F, Position::E_L},
            {Face::F, Position::C_LU},
        },
        should_reverse, state);
    break;
  case Turn::F:
  case Turn::F_:
    ShiftPositionsInGroup(
        {
            {Face::U, Position::C_RD},
            {Face::U, Position::E_D},
            {Face::U, Position::C_LD},
            {Face::L, Position::C_RU},
            {Face::L, Position::E_R},
            {Face::L, Position::C_RD},
            {Face::D, Position::C_LU},
            {Face::D, Position::E_U},
            {Face::D, Position::C_RU},
            {Face::R, Position::C_LD},
            {Face::R, Position::E_L},
            {Face::R, Position::C_LU},
        },
        should_reverse, state);
    break;
  case Turn::R:
  case Turn::R_:
    ShiftPositionsInGroup(
        {
            {Face::U, Position::C_RU},
            {Face::U, Position::E_R},
            {Face::U, Position::C_RD},
            {Face::F, Position::C_RU},
            {Face::F, Position::E_R},
            {Face::F, Position::C_RD},
            {Face::D, Position::C_RU},
            {Face::D, Position::E_R},
            {Face::D, Position::C_RD},
            {Face::B, Position::C_LD},
            {Face::B, Position::E_L},
            {Face::B, Position::C_LU},
        },
        should_reverse, state);
    break;
  case Turn::B:
  case Turn::B_:
    ShiftPositionsInGroup(
        {
            {Face::U, Position::C_LU},
            {Face::U, Position::E_U},
            {Face::U, Position::C_RU},
            {Face::R, Position::C_RU},
            {Face::R, Position::E_R},
            {Face::R, Position::C_RD},
            {Face::D, Position::C_RD},
            {Face::D, Position::E_D},
            {Face::D, Position::C_LD},
            {Face::L, Position::C_LD},
            {Face::L, Position::E_L},
            {Face::L, Position::C_LU},
        },
        should_reverse, state);
    break;
  case Turn::U:
  case Turn::U_:
    ShiftPositionsInGroup(
        {
            {Face::R, Position::C_LU},
            {Face::R, Position::E_U},
            {Face::R, Position::C_RU},
            {Face::B, Position::C_LU},
            {Face::B, Position::E_U},
            {Face::B, Position::C_RU},
            {Face::L, Position::C_LU},
            {Face::L, Position::E_U},
            {Face::L, Position::C_RU},
            {Face::F, Position::C_LU},
            {Face::F, Position::E_U},
            {Face::F, Position::C_RU},
        },
        should_reverse, state);
    break;
  case Turn::D:
  case Turn::D_:
    ShiftPositionsInGroup(
        {
            {Face::F, Position::C_RD},
            {Face::F, Position::E_D},
            {Face::F, Position::C_LD},
            {Face::L, Position::C_RD},
            {Face::L, Position::E_D},
            {Face::L, Position::C_LD},
            {Face::B, Position::C_RD},
            {Face::B, Position::E_D},
            {Face::B, Position::C_LD},
            {Face::R, Position::C_RD},
            {Face::R, Position::E_D},
            {Face::R, Position::C_LD},
        },
        should_reverse, state);
    break;
  default:
    std::cerr << "Unexpected instruction." << std::endl;
    std::abort();
  }
}

} // namespace

void Cube::Move(Instruction instruction) {
  TurnFacePositions(IsClockWise(instruction.GetTurn()),
                    GetTargetFace(instruction.GetTurn()), &_cube_state);
  TurnNeighborPositions(instruction, &_cube_state);
}

CubeState Cube::GetState() const { return _cube_state; }
