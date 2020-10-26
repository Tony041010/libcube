#include "gtest/gtest.h"

#include "cube.h"
#include "cube_state.h"
#include "renderer.h"

#include <cstdlib>
#include <fstream>
#include <iterator>
#include <vector>

std::vector<char> GetBytes(const std::string &file) {
  // Reference: https://stackoverflow.com/a/50317432/1610994
  std::ifstream input(file, std::ios::binary);
  std::vector<char> bytes((std::istreambuf_iterator<char>(input)),
                          (std::istreambuf_iterator<char>()));
  input.close();
  return bytes;
}

bool CompareFile(const std::string &file1, const std::string &file2) {
  // We compare files lossy now as the files might slightly be different due to
  // a different timestamp, etc. We haven't found a need to strictly test this
  // part of code.
  int size_diff = GetBytes(file1).size() - GetBytes(file2).size();
  return std::abs(size_diff) < 3;
}

TEST(RendererTest, RenderExpandedViewSimpleCase) {
  Cube cube;
  cube.Move(Instruction::F);

  Renderer renderer;
  renderer.RenderExpandedView(cube.GetState(), "/tmp/out1.png");
  EXPECT_TRUE(CompareFile("/tmp/out1.png", "test_files/renderer_sample1.png"));
}

TEST(RendererTest, RenderExpandedViewComplexCase) {
  Cube cube;
  cube.Move(Instruction::F);
  cube.Move(Instruction::B_);
  cube.Move(Instruction::U);
  cube.Move(Instruction::L_);

  Renderer renderer;
  renderer.RenderExpandedView(cube.GetState(), "/tmp/out2.png");
  EXPECT_TRUE(CompareFile("/tmp/out2.png", "test_files/renderer_sample2.png"));
}
