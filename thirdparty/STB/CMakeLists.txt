
set(NAME stb)

add_library(${NAME} INTERFACE)

target_link_libraries(${NAME} 
PUBLIC
)

target_include_directories(${NAME}
INTERFACE
   .
)

target_sources(${NAME}
PRIVATE
    
)