set(NAME gfx)

add_library(${NAME} STATIC)

target_link_libraries(${NAME} 
PUBLIC
    Microsoft.GSL::GSL
    GLEW 
    glm
    stb
    camera
)

target_include_directories(${NAME}
PUBLIC
    include/
)

target_sources(${NAME}
PRIVATE
    include/gfx/gfx.hpp
    include/gfx/Shader.hpp
    include/gfx/Texture.hpp
    include/gfx/RGBAImage.hpp
    include/gfx/Atlas.hpp
    include/gfx/Vao.hpp
    include/gfx/Vbo.hpp
    include/gfx/Window.hpp
    include/gfx/controls.hpp
    include/gfx/Renderer.hpp
    include/gfx/AABB.hpp
    include/gfx/BlockAtlas.hpp

    src/gfx.cpp
    src/Texture.cpp
    src/RGBAImage.cpp
    src/Atlas.cpp
    src/Vao.cpp
    src/Vbo.cpp
    src/Window.cpp
    src/controls.cpp
    src/Shader.cpp
    src/Renderer.cpp
    src/BlockAtlas.cpp

)