cmake_minimum_required(VERSION 3.3)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set (CMAKE_CXX_STANDARD 17)

project(cpp_resource)

add_executable(generator generator.cpp)

# allows to add file as binary blob to executable
function(add_resource target key path)
    add_custom_command(
      OUTPUT "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${key}.cpp"
      COMMAND generator ${key} ${path} "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}"
      DEPENDS generator)

    target_sources(${target} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${key}.cpp")
endfunction()

# use this variable to be able to read Resource.h
set(CPP_RESOURCE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "CPP_RESOURCE_INCLUDE_DIR")

