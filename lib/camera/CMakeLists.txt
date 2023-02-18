set(NAME camera)

add_library(${NAME} STATIC)

target_link_libraries(${NAME} 
PUBLIC
    Microsoft.GSL::GSL
    glm
    gfx
)

target_include_directories(${NAME}
PUBLIC
    include/
)

target_sources(${NAME}
PRIVATE
    include/camera/PerspectiveCamera.hpp
    include/camera/OrthoCamera.hpp
    include/camera/camera.hpp

    src/PerspectiveCamera.cpp
    src/OrthoCamera.cpp
)