cmake_minimum_required(VERSION 3.28)

set(projectName hello_triangle)
set(appName hello)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(${projectName})


add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)
add_subdirectory(external/stb_image)


set(SOURCES
	src/shader.cpp
	src/camera.cpp
	src/main.cpp
)

add_executable(${appName} ${SOURCES})

if(
	(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
  	(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
)

target_compile_options(${appName} PRIVATE -Wall -g)

endif()

target_link_libraries(${appName}
	PRIVATE
		glfw
		glad
		glm
		stb_image
)

target_include_directories(${appName}
   	PRIVATE
   		include
		shaders
		textures
)

add_custom_command(TARGET ${appName} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/shaders
		$<TARGET_FILE_DIR:${appName}>/shaders
	COMMENT "Copying shaders to build directory"
)

add_custom_command(TARGET ${appName} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/textures
		$<TARGET_FILE_DIR:${appName}>/textures
	COMMENT "Copying textures to build directory"
)
