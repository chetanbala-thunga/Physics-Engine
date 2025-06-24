cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add GLAD
add_library(glad STATIC glad.c)
target_include_directories(glad PUBLIC Libraries/include)

# Add main executable
add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE Libraries/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# Link GLFW statically
target_link_directories(${PROJECT_NAME} PRIVATE Libraries/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3)

# Link system libraries
target_link_libraries(${PROJECT_NAME} PRIVATE dl GL X11 pthread)
