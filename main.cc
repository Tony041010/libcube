#include <vector>

#include "cube.h"
#include "cube_state.h"
#include "renderer.h"

int main() {
  Cube cube;
  cube.Move(Instruction::F);

  Renderer renderer;
  renderer.RenderExpandedView(cube.GetState(), "/tmp/out.png");
}
