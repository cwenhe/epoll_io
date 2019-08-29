cmake_minimum_required(VERSION 3.10)


project(server)
set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${ROOT_PATH} SOURCE_FILES)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
