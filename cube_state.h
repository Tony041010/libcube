#ifndef CUBE_STATE_H
#define CUBE_STATE_H

/**
 * CubeState stores the colors of each piece of a cube. CubeState doesn't
 * contain code logic for validation, turning, etc, and relies on the caller to
 * set a correct color of each piece.
 */
class CubeState {
public:
  enum Face {
    F, // Front
    B, // Back
    L, // Left
    R, // Right
    U, // Up
    D  // Down
  };
  enum Position {
    C,    // Center
    E_L,  // Edge - Left
    E_R,  // Edge - Right
    E_U,  // Edge - Up
    E_D,  // Edge - Down
    C_LU, // Corner - Left-Up
    C_LD, // Corner - Left-Down
    C_RU, // Corner - Right-Up
    C_RD, // Corner - Right-Down
  };
  enum Color { COLOR_UNSPECIFIED, RED, BLUE, ORANGE, GREEN, WHITE, YELLOW };

  CubeState();
  void SetColor(const Face face, const Position position, const Color color);
  Color GetColor(const Face face, const Position position) const;

private:
  const static int N_FACES = 6;
  const static int N_POSITIONS = 9;
  Color colors[N_FACES][N_POSITIONS];
};
#endif
