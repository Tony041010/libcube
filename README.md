# Cube

## Prerequisite

- Install [Bazel](https://docs.bazel.build/versions/master/install.html).

## Build

```bash
$ bazel build :all
```

## Test

```bash
$ bazel test :all
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
