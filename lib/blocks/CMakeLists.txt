set(NAME blocks)

add_library(${NAME} STATIC)

target_link_libraries(${NAME} 
PUBLIC
    Microsoft.GSL::GSL
    glm
    gfx
    util
)

target_include_directories(${NAME}
PUBLIC
    include/
)

target_sources(${NAME}
PRIVATE
    include/blocks/Block.hpp
    include/blocks/types.hpp
    include/blocks/Dirt.hpp
    include/blocks/Lookup.hpp
    include/blocks/Air.hpp

    src/Block.cpp
)