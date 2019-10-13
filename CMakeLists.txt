cmake_minimum_required(VERSION 3.4)

project(TSIS-LAB01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
  ${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/GoldrenSection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/OptimalPassiveSearch.cpp
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(main ./sources/lab02.cpp)

target_include_directories(
main
PUBLIC
 ${PROJECT_NAME}
)
