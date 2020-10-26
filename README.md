# LibCube

LibCube is a C++ library that provides simulation, rendering, and algorithms of [Rubik's
Cube](https://en.wikipedia.org/wiki/Rubik%27s_Cube). I design LibCube for
developers to build applications on-top of it.

## Prerequisite

- Install [CMake](https://formulae.brew.sh/formula/cmake).
- Install [pngwriter](https://github.com/pngwriter/pngwriter#installation).

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

## Example

Make a 'F' turn then render:

```cc
Cube cube;
cube.Move(Instruction::F);

Renderer renderer;
renderer.RenderExpandedView(cube.GetState(), "/tmp/out.png");
```

Output:

![](https://raw.githubusercontent.com/heronyang/libcube/main/test_files/renderer_sample1.png)

## Future Architecture

Today, I have only implemented the simulation part, and this section describes
the architecture I'm planning to move forward.

LibCube is composed of three components:

- **Simulation** - the core component - simulates cube states after given turns.
- **Renderer** reads a simulated cube state and generates human-friendly images.
- **Algorithm** contains cubing algorithms that are compatible with Simulation.
