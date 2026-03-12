# CMakeList.txt : CMake project for MegaEngine2, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)
include(CMakePrintHelpers)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141) 
  cmake_policy(SET CMP0141 NEW)  
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MegaEngine2" LANGUAGES CXX)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ExampleGame/res/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
#cpp  
file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/Core/*.cpp" "${SOURCE_DIR}/Renderer/*.cpp"
"${SOURCE_DIR}/Game/*.cpp" "${SOURCE_DIR}/Tools/*.cpp" "${SOURCE_DIR}/ScriptEngine/*.cpp" "${SOURCE_DIR}/ComponentSystem/*.cpp"
#headers
"${SOURCE_DIR}/*.h" "${SOURCE_DIR}/Core/*.h" "${SOURCE_DIR}/Renderer/*.h" 
"${SOURCE_DIR}/Game/*.h" "${SOURCE_DIR}/Tools/*.h" "${SOURCE_DIR}/ScriptEngine/*.h" "${SOURCE_DIR}/ComponentSystem/*.h")

cmake_print_variables(${SOURCE_FILES})

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/yaml-cpp)
add_subdirectory(vendor/glm)

add_compile_definitions(GLFW_INCLUDE_NONE)

# Add source to this project's executable.
add_executable (MegaEngine2 ${SOURCE_FILES} "src/Game/Camera.cpp")

target_compile_features(MegaEngine2 PRIVATE cxx_std_20)

target_include_directories(MegaEngine2 PRIVATE ${PROJECT_SOURCE_DIR}/src)

find_package(OpenGL REQUIRED)
target_link_libraries(MegaEngine2 PRIVATE OpenGL::GL)

target_include_directories(MegaEngine2 PRIVATE vendor/glad/include)
target_link_libraries(MegaEngine2 PRIVATE glad)

target_include_directories(MegaEngine2 PRIVATE vendor/yaml-cpp/include)
target_link_libraries(MegaEngine2 PRIVATE yaml-cpp::yaml-cpp)

target_include_directories(MegaEngine2 PRIVATE vendor/glfw/include)
target_link_libraries(MegaEngine2 PRIVATE glfw)

target_include_directories(MegaEngine2 PRIVATE vendor/glm/glm)
target_link_libraries(MegaEngine2 PRIVATE glm)

target_include_directories(MegaEngine2 PRIVATE vendor)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MegaEngine2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
