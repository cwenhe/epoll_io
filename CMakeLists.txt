cmake_minimum_required(VERSION 3.10)
include(CheckCXXCompilerFlag)

project(io_context)

set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    message("support CXX11")
    add_definitions(-std=c++11)
endif()

include_directories(${ROOT_PATH}/include)
file(GLOB_RECURSE SOURCE_FILES ${ROOT_PATH}/src/*.cpp)
#aux_source_directory(${ROOT_PATH}/src SOURCE_FILES)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
