cmake_minimum_required (VERSION 2.8.11)
project (LinearAlgebra)

add_executable (sim main.cpp game.cpp camera.cpp object.cpp utilities/matrix.cpp utilities/transform.cpp utilities/vector.cpp ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/src/gl3w.c)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

target_include_directories(sim PUBLIC ${GLFW_INCLUDE_DIRS})
target_include_directories (sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include)

target_link_libraries(sim ${CMAKE_DL_LIBS})
target_link_libraries(sim ${GLFW_STATIC_LIBRARIES})
