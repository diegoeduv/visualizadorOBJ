cmake_minimum_required(VERSION 3.24)
project(visualizadorOBJ)

# Estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags del compilador (equivalente a -Wall -Wextra)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

#Cargamos Assets
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Encontrar bibliotecas
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
# Directorio de shaders
add_definitions(-DSHADER_DIR=\"${CMAKE_SOURCE_DIR}/shaders\")

# Buscar todos los archivos fuente automáticamente
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)   

# Ejecutable
add_executable(${PROJECT_NAME} ${SRC_FILES}
                                ${PROJECT_SOURCE_DIR}/src/models/ImportedModel.cpp
                                ${PROJECT_SOURCE_DIR}/src/obj_helpers/ModelImporter.cpp
                                ${PROJECT_SOURCE_DIR}/src/models/Grid.cpp)
    
# Librerías
# Linkear las bibliotecas encontradas
target_link_libraries(${PROJECT_NAME} 
    OpenGL::GL
    GLEW::GLEW
    glfw
)
