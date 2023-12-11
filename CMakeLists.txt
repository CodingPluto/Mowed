cmake_minimum_required (VERSION 3.8)
project ("Mower")
add_definitions(-DGLEW_STATIC)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "libraries/glew/")
set(GLEW_INCLUDE_DIRS "libraries/glew/include")
find_library(GLEW_LIBRARIES glew32s PATHS "${CMAKE_CURRENT_SOURCE_DIR}/libraries/glew/lib/Release/x64")

include_directories(${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} "libraries/SOIL2-master/src/SOIL2/")
link_libraries(${GLEW_LIBRARIES})
find_package(GLEW REQUIRED)
set(CMAKE_PREFIX_PATH "libraries/SDL2")
set(CMAKE_MODULE_PATH "libraries/SDL2/cmake/sdl2-config.cmake")
find_package(SDL2 REQUIRED)
set(CMAKE_PREFIX_PATH "libraries/SDL2_image")
set(CMAKE_MODULE_PATH "libraries/SDL2_image/cmake/sdl2_image-config.cmake")
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)
#set(CMAKE_PREFIX_PATH "libraries/glm/")
#set(CMAKE_MODULE_PATH "libraries/SDL2_image/cmake/sdl2_image-config.cmake")
set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libraries/glm/")



add_executable(MowerExecutable
"libraries/SOIL2-master/src/SOIL2/image_DXT.c" "libraries/SOIL2-master/src/SOIL2/image_helper.c" "libraries/SOIL2-master/src/SOIL2/SOIL2.c" "libraries/SOIL2-master/src/SOIL2/wfETC.c"
"src/main.cpp"
"include/Shader.h"
"src/player.cpp" "include/player.h" "include/render.h" "src/render.cpp" "src/grass.cpp" "include/grass.h" "include/animation.h"  "src/animation.cc" "include/item.h" "src/item.cc" "include/gas-can.h" "src/gas-can.cc" "include/mower.h" "src/mower.cc")

target_include_directories(MowerExecutable PUBLIC "include" ${SDL2_INCLUDE_DIRS} "libraries/glm/")
target_link_libraries(MowerExecutable PRIVATE GLEW::GLEW ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARIES} SDL2_image::SDL2_image ${GLM_INCLUDE_DIR})

############################################################Gotta remove cache and reconfigure to change shaders####################################################################################################

file(REMOVE "${CMAKE_BINARY_DIR}/core.frag" "${CMAKE_BINARY_DIR}/core.vs")
file(
	COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/core.frag
	DESTINATION ${CMAKE_BINARY_DIR}
	FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

file(
	COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/core.vs
	DESTINATION ${CMAKE_BINARY_DIR}
	FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

file(
	COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/vertices.txt
	DESTINATION ${CMAKE_BINARY_DIR}
	FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
file(
	COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/mower.png
	DESTINATION ${CMAKE_BINARY_DIR}
	FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
file(
	COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/
	DESTINATION ${CMAKE_BINARY_DIR}
	FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)


# Manually coping dlls over as it did not work for others, strange.
file(
	COPY ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2/lib/x64/SDL2.dll
	DESTINATION ${CMAKE_BINARY_DIR}
	FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
file(
	COPY ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image/lib/x64/SDL2_image.dll
	DESTINATION ${CMAKE_BINARY_DIR}
	FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
add_custom_command(TARGET MowerExecutable POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:MowerExecutable> $<TARGET_FILE_DIR:MowerExecutable>
  COMMAND_EXPAND_LISTS
)