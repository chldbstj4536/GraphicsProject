cmake_minimum_required(VERSION 3.25)

if(NOT WIN32)
    message(FATAL_ERROR "No support this Platform currently")
endif()

project(GraphicsProject
        LANGUAGES CXX)

set(target_name GraphicsProject)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)
add_executable(${target_name} ${sources})

add_subdirectory(submodules/YSMath)
add_subdirectory(submodules/YSEvent)
add_subdirectory(submodules/YSUtility)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${target_name})
    target_link_libraries(${target_name}
    PRIVATE
        # $<$<CONFIG:Debug>:
            d3d11.lib
            d3dcompiler.lib
            dxgi.lib
            dxguid.lib
        # >
        # $<$<CONFIG:Release>:
        #     d3d11.lib
        #     D3DCompiler.lib
        #     Effects11.lib
        #     dxerr.lib
        #     dxgi.lib
        #     dxguid.lib
        # >
    )
endif()

# target_link_libraries(${target_name} PRIVATE YSMath)