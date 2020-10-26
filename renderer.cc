#include "renderer.h"

#include <iostream>
#include <map>
#include <pngwriter.h>
#include <utility>
#include <vector>

#include "cube_state.h"

namespace {

static std::map<std::pair<CubeState::Face, CubeState::Position>, int>
    PIECE_TO_COL_OFFSET = {
        {{CubeState::Face::L, CubeState::Position::C_LU}, 0},
        {{CubeState::Face::L, CubeState::Position::E_L}, 0},
        {{CubeState::Face::L, CubeState::Position::C_LD}, 0},
        {{CubeState::Face::L, CubeState::Position::E_U}, 1},
        {{CubeState::Face::L, CubeState::Position::C}, 1},
        {{CubeState::Face::L, CubeState::Position::E_D}, 1},
        {{CubeState::Face::L, CubeState::Position::C_RU}, 2},
        {{CubeState::Face::L, CubeState::Position::E_R}, 2},
        {{CubeState::Face::L, CubeState::Position::C_RD}, 2},

        {{CubeState::Face::U, CubeState::Position::C_LU}, 3},
        {{CubeState::Face::U, CubeState::Position::E_L}, 3},
        {{CubeState::Face::U, CubeState::Position::C_LD}, 3},
        {{CubeState::Face::F, CubeState::Position::C_LU}, 3},
        {{CubeState::Face::F, CubeState::Position::E_L}, 3},
        {{CubeState::Face::F, CubeState::Position::C_LD}, 3},
        {{CubeState::Face::D, CubeState::Position::C_LU}, 3},
        {{CubeState::Face::D, CubeState::Position::E_L}, 3},
        {{CubeState::Face::D, CubeState::Position::C_LD}, 3},

        {{CubeState::Face::U, CubeState::Position::E_U}, 4},
        {{CubeState::Face::U, CubeState::Position::C}, 4},
        {{CubeState::Face::U, CubeState::Position::E_D}, 4},
        {{CubeState::Face::F, CubeState::Position::E_U}, 4},
        {{CubeState::Face::F, CubeState::Position::C}, 4},
        {{CubeState::Face::F, CubeState::Position::E_D}, 4},
        {{CubeState::Face::D, CubeState::Position::E_U}, 4},
        {{CubeState::Face::D, CubeState::Position::C}, 4},
        {{CubeState::Face::D, CubeState::Position::E_D}, 4},

        {{CubeState::Face::U, CubeState::Position::C_RU}, 5},
        {{CubeState::Face::U, CubeState::Position::E_R}, 5},
        {{CubeState::Face::U, CubeState::Position::C_RD}, 5},
        {{CubeState::Face::F, CubeState::Position::C_RU}, 5},
        {{CubeState::Face::F, CubeState::Position::E_R}, 5},
        {{CubeState::Face::F, CubeState::Position::C_RD}, 5},
        {{CubeState::Face::D, CubeState::Position::C_RU}, 5},
        {{CubeState::Face::D, CubeState::Position::E_R}, 5},
        {{CubeState::Face::D, CubeState::Position::C_RD}, 5},

        {{CubeState::Face::R, CubeState::Position::C_LU}, 6},
        {{CubeState::Face::R, CubeState::Position::E_L}, 6},
        {{CubeState::Face::R, CubeState::Position::C_LD}, 6},
        {{CubeState::Face::R, CubeState::Position::E_U}, 7},
        {{CubeState::Face::R, CubeState::Position::C}, 7},
        {{CubeState::Face::R, CubeState::Position::E_D}, 7},
        {{CubeState::Face::R, CubeState::Position::C_RU}, 8},
        {{CubeState::Face::R, CubeState::Position::E_R}, 8},
        {{CubeState::Face::R, CubeState::Position::C_RD}, 8},

        {{CubeState::Face::B, CubeState::Position::C_LU}, 9},
        {{CubeState::Face::B, CubeState::Position::E_L}, 9},
        {{CubeState::Face::B, CubeState::Position::C_LD}, 9},
        {{CubeState::Face::B, CubeState::Position::E_U}, 10},
        {{CubeState::Face::B, CubeState::Position::C}, 10},
        {{CubeState::Face::B, CubeState::Position::E_D}, 10},
        {{CubeState::Face::B, CubeState::Position::C_RU}, 11},
        {{CubeState::Face::B, CubeState::Position::E_R}, 11},
        {{CubeState::Face::B, CubeState::Position::C_RD}, 11},
};

static std::map<std::pair<CubeState::Face, CubeState::Position>, int>
    PIECE_TO_ROW_OFFSET = {
        {{CubeState::Face::U, CubeState::Position::C_LU}, 8},
        {{CubeState::Face::U, CubeState::Position::E_U}, 8},
        {{CubeState::Face::U, CubeState::Position::C_RU}, 8},
        {{CubeState::Face::U, CubeState::Position::E_L}, 7},
        {{CubeState::Face::U, CubeState::Position::C}, 7},
        {{CubeState::Face::U, CubeState::Position::E_R}, 7},
        {{CubeState::Face::U, CubeState::Position::C_LD}, 6},
        {{CubeState::Face::U, CubeState::Position::E_D}, 6},
        {{CubeState::Face::U, CubeState::Position::C_RD}, 6},

        {{CubeState::Face::L, CubeState::Position::C_LU}, 5},
        {{CubeState::Face::L, CubeState::Position::E_U}, 5},
        {{CubeState::Face::L, CubeState::Position::C_RU}, 5},
        {{CubeState::Face::F, CubeState::Position::C_LU}, 5},
        {{CubeState::Face::F, CubeState::Position::E_U}, 5},
        {{CubeState::Face::F, CubeState::Position::C_RU}, 5},
        {{CubeState::Face::R, CubeState::Position::C_LU}, 5},
        {{CubeState::Face::R, CubeState::Position::E_U}, 5},
        {{CubeState::Face::R, CubeState::Position::C_RU}, 5},
        {{CubeState::Face::B, CubeState::Position::C_LU}, 5},
        {{CubeState::Face::B, CubeState::Position::E_U}, 5},
        {{CubeState::Face::B, CubeState::Position::C_RU}, 5},

        {{CubeState::Face::L, CubeState::Position::E_L}, 4},
        {{CubeState::Face::L, CubeState::Position::C}, 4},
        {{CubeState::Face::L, CubeState::Position::E_R}, 4},
        {{CubeState::Face::F, CubeState::Position::E_L}, 4},
        {{CubeState::Face::F, CubeState::Position::C}, 4},
        {{CubeState::Face::F, CubeState::Position::E_R}, 4},
        {{CubeState::Face::R, CubeState::Position::E_L}, 4},
        {{CubeState::Face::R, CubeState::Position::C}, 4},
        {{CubeState::Face::R, CubeState::Position::E_R}, 4},
        {{CubeState::Face::B, CubeState::Position::E_L}, 4},
        {{CubeState::Face::B, CubeState::Position::C}, 4},
        {{CubeState::Face::B, CubeState::Position::E_R}, 4},

        {{CubeState::Face::L, CubeState::Position::C_LD}, 3},
        {{CubeState::Face::L, CubeState::Position::E_D}, 3},
        {{CubeState::Face::L, CubeState::Position::C_RD}, 3},
        {{CubeState::Face::F, CubeState::Position::C_LD}, 3},
        {{CubeState::Face::F, CubeState::Position::E_D}, 3},
        {{CubeState::Face::F, CubeState::Position::C_RD}, 3},
        {{CubeState::Face::R, CubeState::Position::C_LD}, 3},
        {{CubeState::Face::R, CubeState::Position::E_D}, 3},
        {{CubeState::Face::R, CubeState::Position::C_RD}, 3},
        {{CubeState::Face::B, CubeState::Position::C_LD}, 3},
        {{CubeState::Face::B, CubeState::Position::E_D}, 3},
        {{CubeState::Face::B, CubeState::Position::C_RD}, 3},

        {{CubeState::Face::D, CubeState::Position::C_LU}, 2},
        {{CubeState::Face::D, CubeState::Position::E_U}, 2},
        {{CubeState::Face::D, CubeState::Position::C_RU}, 2},
        {{CubeState::Face::D, CubeState::Position::E_L}, 1},
        {{CubeState::Face::D, CubeState::Position::C}, 1},
        {{CubeState::Face::D, CubeState::Position::E_R}, 1},
        {{CubeState::Face::D, CubeState::Position::C_LD}, 0},
        {{CubeState::Face::D, CubeState::Position::E_D}, 0},
        {{CubeState::Face::D, CubeState::Position::C_RD}, 0},
};

static std::map<CubeState::Color, std::vector<int>> COLOR_TO_RGB = {
    {CubeState::Color::RED, {65535, 0, 0}},
    {CubeState::Color::GREEN, {0, 65535, 0}},
    {CubeState::Color::BLUE, {0, 0, 65535}},
    {CubeState::Color::WHITE, {65535, 65535, 65535}},
    {CubeState::Color::YELLOW, {65535, 65535, 0}},
    {CubeState::Color::ORANGE, {65535, 42240, 0}},
};

int GetWidth(int scale, int margin) {
  // The width includes two margins (left and right) and the widths of 4 faces
  // (L, F, R, B). Each face has the width of 3 pieces.
  return margin * 2 + scale * 4 * 3;
}

int GetHeight(int scale, int margin) {
  // The height includes two margins (top and bottom) and the heights of 3 faces
  // (U, F, D). Each face has the height of 3 pieces.
  return margin * 2 + scale * 3 * 3;
}

int GetPieceXOffset(CubeState::Face face, CubeState::Position position,
                    int margin, int size) {
  std::pair<CubeState::Face, CubeState::Position> piece =
      std::make_pair<>(face, position);
  assert(PIECE_TO_COL_OFFSET.count(piece) == 1);
  return margin + PIECE_TO_COL_OFFSET.at(piece) * size;
}

int GetPieceYOffset(const CubeState::Face face,
                    const CubeState::Position position, int margin, int size) {
  std::pair<CubeState::Face, CubeState::Position> piece =
      std::make_pair<>(face, position);
  assert(PIECE_TO_ROW_OFFSET.count(piece) == 1);
  return margin + PIECE_TO_ROW_OFFSET.at(piece) * size;
}

std::vector<int> GetRGBColor(const CubeState::Color color) {
  assert(COLOR_TO_RGB.count(color) == 1);
  return COLOR_TO_RGB.at(color);
}

void RenderPiece(const CubeState::Face face, const CubeState::Position position,
                 const CubeState::Color color, int margin, int size,
                 pngwriter &png_writer) {
  int x_offset = GetPieceXOffset(face, position, margin, size);
  int y_offset = GetPieceYOffset(face, position, margin, size);
  std::vector<int> rgb = GetRGBColor(color);
  png_writer.filledsquare(x_offset, y_offset, x_offset + size, y_offset + size,
                          rgb.at(0), rgb.at(1), rgb.at(2));
}

void RenderCubeLines(int margin, int size, pngwriter &png_writer) {
  // Render horizontal lines.
  png_writer.line(margin + size * 3, margin + size * 0, margin + size * 6,
                  margin + size * 0, 0, 0, 0);
  png_writer.line(margin + size * 3, margin + size * 1, margin + size * 6,
                  margin + size * 1, 0, 0, 0);
  png_writer.line(margin + size * 3, margin + size * 2, margin + size * 6,
                  margin + size * 2, 0, 0, 0);

  png_writer.line(margin, margin + size * 3, margin + size * 12,
                  margin + size * 3, 0, 0, 0);
  png_writer.line(margin, margin + size * 4, margin + size * 12,
                  margin + size * 4, 0, 0, 0);
  png_writer.line(margin, margin + size * 5, margin + size * 12,
                  margin + size * 5, 0, 0, 0);
  png_writer.line(margin, margin + size * 6, margin + size * 12,
                  margin + size * 6, 0, 0, 0);

  png_writer.line(margin + size * 3, margin + size * 7, margin + size * 6,
                  margin + size * 7, 0, 0, 0);
  png_writer.line(margin + size * 3, margin + size * 8, margin + size * 6,
                  margin + size * 8, 0, 0, 0);
  png_writer.line(margin + size * 3, margin + size * 9, margin + size * 6,
                  margin + size * 9, 0, 0, 0);

  // Render vertical lines.
  png_writer.line(margin + size * 0, margin + size * 3, margin + size * 0,
                  margin + size * 6, 0, 0, 0);
  png_writer.line(margin + size * 1, margin + size * 3, margin + size * 1,
                  margin + size * 6, 0, 0, 0);
  png_writer.line(margin + size * 2, margin + size * 3, margin + size * 2,
                  margin + size * 6, 0, 0, 0);
  png_writer.line(margin + size * 3, margin + size * 0, margin + size * 3,
                  margin + size * 9, 0, 0, 0);
  png_writer.line(margin + size * 4, margin + size * 0, margin + size * 4,
                  margin + size * 9, 0, 0, 0);
  png_writer.line(margin + size * 5, margin + size * 0, margin + size * 5,
                  margin + size * 9, 0, 0, 0);
  png_writer.line(margin + size * 6, margin + size * 0, margin + size * 6,
                  margin + size * 9, 0, 0, 0);
  png_writer.line(margin + size * 7, margin + size * 3, margin + size * 7,
                  margin + size * 6, 0, 0, 0);
  png_writer.line(margin + size * 8, margin + size * 3, margin + size * 8,
                  margin + size * 6, 0, 0, 0);
  png_writer.line(margin + size * 9, margin + size * 3, margin + size * 9,
                  margin + size * 6, 0, 0, 0);
  png_writer.line(margin + size * 10, margin + size * 3, margin + size * 10,
                  margin + size * 6, 0, 0, 0);
  png_writer.line(margin + size * 11, margin + size * 3, margin + size * 11,
                  margin + size * 6, 0, 0, 0);
  png_writer.line(margin + size * 12, margin + size * 3, margin + size * 12,
                  margin + size * 6, 0, 0, 0);
}

} // namespace

void Renderer::RenderExpandedView(const CubeState &cube_state,
                                  std::string output_filename) {
  pngwriter png_writer(GetWidth(SCALE, MARGIN), GetHeight(SCALE, MARGIN),
                       BACKGROUND_COLOR, output_filename.c_str());
  for (const CubeState::Face &face : CubeState::GetFaces()) {
    for (const CubeState::Position &position : CubeState::GetPositions()) {
      RenderPiece(face, position, cube_state.GetColor(face, position), MARGIN,
                  SCALE, png_writer);
    }
  }
  RenderCubeLines(MARGIN, SCALE, png_writer);
  png_writer.close();
}
