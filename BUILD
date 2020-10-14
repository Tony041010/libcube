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
