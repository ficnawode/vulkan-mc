set(NAME exec)

add_executable(${NAME})

target_link_libraries(${NAME}
    PRIVATE
    gfx
    GLEW
    OpenGL
    glfw
    render
    world
)

target_sources(${NAME}
    PRIVATE
    include/State.hpp
    src/main.cpp
    src/State.cpp 
)

target_include_directories(${NAME}
    PRIVATE
    include/
)

add_custom_target(${NAME}.run
    COMMAND ${CMAKE_EXECUTE_PROCESS_COMMAND_ECHO}
    ${NAME}
    DEPENDS ${NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
)

add_custom_command(TARGET ${NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${NAME}>/res/)