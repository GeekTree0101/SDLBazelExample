# How to make SDL application with Bazel Builder?
<img src="https://github.com/GeekTree0101/SDLBazelExample/blob/master/resource/cube.jpg" height=300px/>

## 1. Install Bazel 
```sh
brew tap bazelbuild/tap
brew tap-pin bazelbuild/tap
brew install bazelbuild/tap/bazel
```
https://docs.bazel.build/versions/master/install-os-x.html


## 2. Install SDL
```sh
brew install sdl2
```

## 3. Make WORKSPACE for SDL2
```py
new_local_repository(
    name = "SDL2",
    path = "/usr/local/Cellar/sdl2/2.0.9", # <----- SDL path
    build_file = "sdl2.BUILD" # <------ SDL2 Build script!
)
```

## 4. Make SDL2 Build script

sdl2 dir 
```sh
/usr/local/Cellar/sdl2/2.0.9
- include <----- @Important
- lib <----- @Important (header files located, SDL/*.h)
- TODO.txt
- INSTALL_RECEIPT.json
- bin	
- share
- README.text
- COPYING.txt
```

sdl.BUILD script
```py
cc_library(
    name = "SDL2",
    hdrs = glob(["include/SDL2/*.h"]), 
    linkopts = [
        "-L /usr/local/Cellar/sdl2/2.0.9/lib -l SDL2-2.0.0", # (-L lib-dir -l lib-name)
        "-framework OpenGL" # (use OpenGL, <SDL2/SDL_opengl.h>)
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"], # Visibility is important!
)
```

## 5. Make Build script for application

Cube dir
```sh
Cube
- BUILD
- Cube.cpp
- Cube.h
- main.cpp
```

BUILD script
```py

cc_library(
    name = "Lib",
    srcs = ["Cube.cpp"],
    hdrs = ["Cube.h"],
    deps = ["@SDL2//:SDL2"],  # <----- SDL2 library from sdl2.BUILD script
)

cc_binary(
    name = "CubeExample",
    srcs = ["main.cpp"],
    deps = [":Lib"] .  # <----- dep cc_library.Lib
)
```
