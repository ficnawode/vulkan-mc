set(NAME entity)

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
    include/entity/Component.hpp
    include/entity/Player.hpp
    include/entity/BlockLookComp.hpp
    include/entity/CameraComp.hpp
    include/entity/ControlComp.hpp
    include/entity/PhysicsComp.hpp
    include/entity/PositionComp.hpp

    src/Player.cpp

)