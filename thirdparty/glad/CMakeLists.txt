project(glad LANGUAGES C)

add_library(glad STATIC
    src/gl.c
)

target_include_directories(glad
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Suppress warnings from third-party code — not our problem to fix
if(MSVC)
    target_compile_options(glad PRIVATE /W0)
else()
    target_compile_options(glad PRIVATE -w)
endif()