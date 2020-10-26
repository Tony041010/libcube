#ifndef RENDERER_H
#define RENDERER_H
#include <string>

#include "cube_state.h"

class Renderer {
public:
  void RenderExpandedView(const CubeState &cube_state,
                          std::string output_filename);

private:
  static const int SCALE = 50;
  static const int MARGIN = 100;
  static const int BACKGROUND_COLOR = 0;  // black
};
#endif
