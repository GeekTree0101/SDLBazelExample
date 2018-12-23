cc_library(
    name = "SDL2",
    hdrs = glob(["include/SDL2/*.h"]),
    linkopts = [
        "-L /usr/local/Cellar/sdl2/2.0.9/lib -l SDL2-2.0.0",
        "-framework OpenGL"
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

# DO NOT Use SDL2.framework from Library path
# dyld: Library not loaded: @rpath/SDL2.framework/Versions/A/SDL2
#   Referenced from: /Users/vingle/Desktop/BuckCrossPlatformExample/bazel-bin/GeekKit/App
#   Reason: image not found
# make: *** [run] Abort trap: 6
