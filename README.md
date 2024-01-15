# toy rasterizer

A simple 3d software rasterizer

# setup

assuming mac os, vscode and following project structure:

```
.
├── .gitignore
├── README.md
└── src
    └── main.cpp
```

## SDL2

simple multimedia library. to install run `brew install sdl2`

## cmake

for managing the build process

1. install `cmake`:

   ```
   brew install cmake
   ```

2. create `cmake` folder in the project root folder and put `FindSDL2.cmake` in there. after that you can use this module to find SDL2:

```
   set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
   find_package(SDL2 REQUIRED)
   include_directories(${SDL2_INCLUDE_DIR})
   target_link_libraries(toy-rasterizer ${SDL2_LIBRARY})
```

3. create `CMakeLists.txt` in the project root folder:

   ```
   cmake_minimum_required(VERSION 3.0)

   project(toy-rasterizer)

   set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
   set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

   file(GLOB SOURCES "src/*.cpp")
   add_executable(toy-rasterizer ${SOURCES})

   find_package(SDL2 REQUIRED)
   include_directories(${SDL2_INCLUDE_DIR})
   target_link_libraries(toy-rasterizer ${SDL2_LIBRARY})
   ```

to reduce clutter, create a `build` folder in the project root folder. to build the project, run the following commands from within `build` folder:

1. `cmake ../`

2. `make`

## clangd

for c++ language support 

1. install [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) extension

2. make sure you have the following line in your `CmakeLists.txt`: `set(CMAKE_EXPORT_COMPILE_COMMANDS ON)`

3. after building your project (see above), create a `compile_commands.json` symlink. to do so, run the following command from within the project root folder (assuming you created the `build` folder to reduce clutter):

   `ln -s build/compile_commands.json compile_commands.json`

to enable `clang-tidy` checks create a `.clang-tidy` file in the project root folder:

```
Checks: '
  bugprone-*,
  cert-*,
  clang-analyzer-*,
  clang-diagnostic-*,
  cppcoreguidelines-*,
  google-*,
  hicpp-*,
  llvm-*,
  misc-*,
  modernize-*,
  performance-*,
  portability-*,
  readability-*
'
FormatStyle: '
  google
'
```

## .gitignore

don't forget to add the following lines to  `.gitignore`:

```
.DS_Store

build/

.clangd
.clang-tidy
.clang-format
compile_commands.json
```


