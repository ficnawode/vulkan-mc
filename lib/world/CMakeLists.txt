set(NAME world)

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
    include/world/World.hpp

    src/World.cpp

)