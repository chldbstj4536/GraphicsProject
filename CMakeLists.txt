cmake_minimum_required(VERSION 3.25)

if(NOT WIN32)
    message(FATAL_ERROR "No support this Platform currently")
endif()

project(GraphicsProject)

set(target_name GraphicsProject)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)
add_executable(${target_name} ${sources})

add_subdirectory(submodules/YSMath)
add_subdirectory(submodules/YSEvent)
add_subdirectory(submodules/YSUtility)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${target_name})
endif()

target_link_libraries(${target_name} PRIVATE YSMath)