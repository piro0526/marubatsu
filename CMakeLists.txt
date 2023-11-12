cmake_minimum_required(VERSION 3.2)
project(tic_tac_toe VERSION 0.1.0)

add_subdirectory(pybind11)

add_library(Main
  Board.cpp
  Disc.cpp
  Porint.cpp
)

pybind11_add_module(tic_tac_toe tic_tac_toe.cpp)
target_link_libraries(mymodule PRIVATE Main)