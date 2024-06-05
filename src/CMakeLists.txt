cmake_minimum_required(VERSION 3.13.4)

# declare your project using project()
project(Raytracing-SoC024)

# giving execuatable a name and it's source file
#add_executable(${PROJECT_NAME} main.cpp)
add_library(vecops ../lib/vecops.cpp)
add_executable(execfile main.cpp)
target_link_libraries(execfile vecops)

