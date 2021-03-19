# cmake version
cmake_minimum_required(VERSION 2.8)

# project variable
set (PROJECT_NAME CmakeExp)

# config project 
project(${PROJECT_NAME})
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MAJOR 0)

# set cpp version
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# create a head file to receive cmake config
configure_file (
"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h"
)

file(GLOB_RECURSE SOURCE_FILES *.c)

add_executable(${PROJECT_NAME}) ${SOURCE_FILES})

