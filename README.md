# LibCube

LibCube is a C++ library that provides simulation, rendering, and algorithms of [Rubik's
Cube](https://en.wikipedia.org/wiki/Rubik%27s_Cube). I design LibCube for
developers to build applications on-top of it.

## Prerequisite

- Install [CMake](https://formulae.brew.sh/formula/cmake).

## Caveat

We have only developmented and tested this project on Mac OS.

## Build

```bash
$ cmake . && make
```

## Test

After build:

```bash
$ make test
```

## Example Code

Make a 'F' turn:

```cc
Cube cube;
cube.Move(Turn::F);
EXPECT_EQ("      -------\n"
          "      |Y|Y|Y|\n"
          "      |Y|Y|Y|\n"
          "      |R|R|R|\n"
          "-------------------------\n"
          "|R|R|W|G|G|G|Y|O|O|B|B|B|\n"
          "|R|R|W|G|G|G|Y|O|O|B|B|B|\n"
          "|R|R|W|G|G|G|Y|O|O|B|B|B|\n"
          "-------------------------\n"
          "      |O|O|O|\n"
          "      |W|W|W|\n"
          "      |W|W|W|\n"
          "      -------\n",
          cube.GetState().GetDebugString());
```

## Future Architecture

Today, I have only implemented the simulation part, and this section describes
the architecture I'm planning to move forward.

LibCube is composed of three components:

- **Simulation** - the core component - simulates cube states after given turns.
- **Renderer** reads a simulated cube state and generates human-friendly images.
- **Algorithm** contains cubing algorithms that are compatible with Simulation.
