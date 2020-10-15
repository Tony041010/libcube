#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <map>
#include <string>

/**
 * Instruction presents a single action that can be applied to a cube. E.g. turn
 * the left face.
 */
class Instruction {
public:
  enum Turn {
    F,  // (clockwise) turn the front face
    B,  // (clockwise) turn the back face
    L,  // (clockwise) turn the left face
    R,  // (clockwise) turn the right face
    U,  // (clockwise) turn the up face
    D,  // (clockwise) turn the down face
    F_, // (counterclockwise) turn the front face
    B_, // (counterclockwise) turn the back face
    L_, // (counterclockwise) turn the left face
    R_, // (counterclockwise) turn the right face
    U_, // (counterclockwise) turn the up face
    D_  // (counterclockwise) turn the down face
  };
  Instruction(Turn turn);

  // Gets string presentation of this instruction.
  std::string GetName() const;

private:
  static std::map<Turn, std::string> _turn_names;
  const Turn _turn;
};

#endif
