cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

# set the project name
project(cartesianVector)

# add the lib
add_library(vector SHARED vector.cpp)

# add another
#add_library(mysource_2 SHARED sources_2.cpp)

# add the executable
add_executable(main main.cc)

# do not forget to link
target_link_libraries(main vector)

#target_link_libraries(main mysource_2)
