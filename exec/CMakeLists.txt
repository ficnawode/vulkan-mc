set(NAME exec)

add_executable(${NAME})

target_link_libraries(${NAME}
PRIVATE
    glfw
    dummy
    Vulkan::Vulkan
)

target_sources(${NAME}
PRIVATE
    include/backend/Window.hpp
    include/backend/Pipeline.hpp

    include/game/State.hpp

    src/backend/Window.cpp
    src/backend/Pipeline.cpp

    src/game/State.cpp

    src/main.cpp
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

#COMPILE SHADERS:

if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
else()
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin32/glslangValidator.exe")
endif()

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "shaders/*.frag"
    "shaders/*.vert"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )

add_dependencies(${NAME} Shaders)

add_custom_command(TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${NAME}>/shaders/"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/shaders"
        "$<TARGET_FILE_DIR:${NAME}>/shaders"
        )