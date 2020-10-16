load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "cube",
    srcs = ["cube.cc"],
    hdrs = ["cube.h"],
)

cc_test(
    name = "cube_test",
    srcs = ["cube_test.cc"],
    deps = [
        "//:cube",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "cube_state",
    srcs = ["cube_state.cc"],
    hdrs = ["cube_state.h"],
)

cc_test(
    name = "cube_state_test",
    srcs = ["cube_state_test.cc"],
    deps = [
        "//:cube_state",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "instruction",
    srcs = ["instruction.cc"],
    hdrs = ["instruction.h"],
)

cc_test(
    name = "instruction_test",
    srcs = ["instruction_test.cc"],
    deps = [
        "//:instruction",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "util",
    srcs = ["util.cc"],
    hdrs = ["util.h"],
    deps = [
        "//:cube_state",
        "//:instruction",
    ],
)

cc_test(
    name = "util_test",
    srcs = ["util_test.cc"],
    deps = [
        "//:cube_state",
        "//:instruction",
        "//:util",
        "@gtest//:gtest_main",
    ],
)
