cmake_minimum_required (VERSION 3.8)

project ("glad")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/**.c" "${CMAKE_CURRENT_SOURCE_DIR}/**.h")

add_library(glad STATIC ${SOURCE_FILES})

target_include_directories(glad PRIVATE include)

find_package(OpenGL REQUIRED)
target_link_libraries(glad PRIVATE OpenGL::GL)