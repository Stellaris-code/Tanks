cmake_minimum_required(VERSION 2.8.3)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for executables

set(project_name 123Tanks)
project(${project_name})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -g")

include_directories("include")

file(GLOB_RECURSE source_files "src/*.cpp")
file(GLOB_RECURSE header_files "include/*.hpp")

find_package(SFML REQUIRED COMPONENTS system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

find_package(Thor REQUIRED)
include_directories(${THOR_INCLUDE_DIR})

find_package(EntityX REQUIRED)
include_directories(${ENTITYX_INCLUDE_DIRS})

find_package(Boost REQUIRED program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${project_name} ${header_files} ${source_files})
target_link_libraries(${project_name} ${ENTITYX_LIBRARIES} ${SFML_LIBRARIES} ${THOR_LIBRARY} ${Boost_LIBRARIES})
