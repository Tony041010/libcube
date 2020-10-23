# Cube

Cube (I haven't found a better name yet) is a C++ library that provides
simulation, rendering, and algorithms of [Rubik's
Cube](https://en.wikipedia.org/wiki/Rubik%27s_Cube). I design Cube for
developers to build applications on-top of it, and we also provide example
applications.

## Prerequisite

- Install [CMake](https://formulae.brew.sh/formula/cmake).

## Build

```bash
$ cmake . && make
```

## Test

```bash
$ cmake . && make test
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

Cube library is composed of three components:

- **Simulation** - the core component - simulates cube states after given turns.
- **Renderer** reads a simulated cube state and generates human-friendly images.
- **Algorithm** contains cubing algorithms that are compatible with Simulation.

Lastly, **Application** component contains applications that uses Cube library,
e.g. a trainer app.
