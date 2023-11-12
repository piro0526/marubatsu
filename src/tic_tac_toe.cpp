#include <pybind11/pybind11.h>
#include "Board.h"
namespace py = pybind11;

PYBIND11_MODULE(tic_tac_toe, m)
{
    py::class_<Point>(m, "Point")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def("getX", &Point::getX)
        .def("getY", &Point::getX)
        .def("setX", &Point::setX)
        .def("setY", &Point::setX)
        ;
    
    py::class_<Disc, Point>(m, "Disc")
        .def(py::init<>())
        .def(py::init<int, int, Mark>())
        .def("getMark", &Disc::getMark)
        .def("setMark", &Disc::getMark)
        ;
    
    m.attr("BOARD_ROW_SIZE") = BOARD_ROW_SIZE;
    m.attr("BOARD_COL_SIZE") = BOARD_COL_SIZE;
    m.attr("K_IN_A_ROW") = K_IN_A_ROW;
    m.attr("MAX_TURNS") = MAX_TURNS;
    m.attr("EMPTY") = 0;
    m.attr("X") = -1;
    m.attr("O") = 1;
    m.attr("WALL") = 2;



    py::class_<Board>(m, "Board")
        .def(py::init<>())
        .def("init", &Board::init)
        .def("place", &Board::place)
        .def("undo", &Board::undo)
        .def("checkLine", &Board::checkLine)
        .def("isGameOver", &Board::isGameOver)
        .def("switchMark", &Board::switchMark)
        .def("getMark", &Board::getMark)
        .def("getPlaceablePosition", &Board::getPlaceablePosition)
        .def("getUpdate", &Board::getUpdate)
        .def("getCurrentMark", &Board::getCurrentMark)
        .def("getTurns", &Board::getTurns)
        ;
}