cmake_minimum_required (VERSION 3.8)
project ("SnakeProject")
add_definitions(-DGLEW_STATIC)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "libraries/glew/")
set(GLEW_INCLUDE_DIRS "libraries/glew/include")
find_library(GLEW_LIBRARIES glew32s PATHS "${CMAKE_CURRENT_SOURCE_DIR}/libraries/glew/lib/Release/x64")

include_directories(${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
find_package(GLEW REQUIRED)
set(CMAKE_PREFIX_PATH "libraries/SDL2")
set(CMAKE_MODULE_PATH "libraries/SDL2/cmake/sdl2-config.cmake")
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(SnakeEXE "src/main.cpp"   "include/Shader.h")

target_include_directories(SnakeEXE PUBLIC "include" ${SDL2_INCLUDE_DIRS})
target_link_libraries(SnakeEXE PRIVATE GLEW::GLEW ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARIES})

add_custom_command(TARGET SnakeEXE POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SnakeEXE> $<TARGET_FILE_DIR:SnakeEXE>
  COMMAND_EXPAND_LISTS
)