#ifndef CUBE_H
#define CUBE_H

#include "cube_state.h"
#include "instruction.h"

class Cube {
public:
  /**
   * Moves the cube with a given instruction.
   */
  void Move(Instruction instruction);

  /**
   * Gets a copy of the current cube state.
   */
  CubeState GetState() const;

private:
  CubeState _cube_state;
};

#endif
