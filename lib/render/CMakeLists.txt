set(NAME render)

add_library(${NAME} STATIC)

target_link_libraries(${NAME} 
PUBLIC
    Microsoft.GSL::GSL
    glm
    gfx
    camera
)

target_include_directories(${NAME}
PUBLIC
    include/
)

target_sources(${NAME}
PRIVATE
    include/render/Renderer.hpp
    include/render/types.hpp

    src/Renderer.cpp
)