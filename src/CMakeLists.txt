cmake_minimum_required(VERSION 3.13.4)

# declare your project using project()
project(Raytracing-SoC024)

# giving execuatable a name and it's source file
#add_executable(${PROJECT_NAME} main.cpp)
add_library(mylib ../lib/vecops.cpp ../lib/color.cpp)
add_executable(bin main.cpp)
target_link_libraries(bin mylib)

