#ifndef CUBE_STATE_H
#define CUBE_STATE_H

/**
 * CubeState stores the colors of each piece of a cube. CubeState doesn't
 * contain code logic for validation, turning, etc, and relies on the caller to
 * set a correct color of each piece.
 */
class CubeState {
public:
  /**
   * Face refers to one face of a cube. The expanded view of a cube below shows
   * the 6 faces of a cube and their names.
   *     -----
   *     | U |
   * -----------------
   * | L | F | R | B |
   * -----------------
   *     | D |
   *     -----
   */
  enum Face {
    F, // Front
    B, // Back
    L, // Left
    R, // Right
    U, // Up
    D  // Down
  };

  /**
   * Position refers to one block on a face of a cube. The below view shows the
   * 9 positions on a face and their names.
   * ---------------------
   * | C_LU | E_U | C_RU |
   * ---------------------
   * | E_L  | C   | E_R  |
   * ---------------------
   * | C_LD | E_D | C_RD |
   * ---------------------
   */
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

  // Sets color of a piece.
  void SetColor(const Face face, const Position position, const Color color);

  // Gets color of a piece.
  Color GetColor(const Face face, const Position position) const;

private:
  const static int N_FACES = 6;
  const static int N_POSITIONS = 9;
  Color colors[N_FACES][N_POSITIONS];
};
#endif
