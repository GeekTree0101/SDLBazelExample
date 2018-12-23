
cc_library(
    name = "Lib",
    srcs = ["Cube.cpp"],
    hdrs = ["Cube.h"],
    deps = ["@SDL2//:SDL2"],
)

cc_binary(
    name = "CubeExample",
    srcs = ["main.cpp"],
    deps = [":Lib"]
)
