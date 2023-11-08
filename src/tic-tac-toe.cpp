#include <pybind11/pybind11.h>
#include "Board.h"
namespace py = pybind11;

PYBIND11_MODULE(tic-tac-toe, m)
{
    py::class_<Point>(m, "Point")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def("getX", &Point::getX)
        .def("getY", &Point::getX)
        .def("setX", &Point::setX)
        .def("setY", &Point::setX)
        ;
    
    py::class_<Disc, Point>(m, "Point")
        .def(py::init<>())
        .def(py::init<int, int, Mark>())
        .def("getMark", &Point::getX)
        .def("setMark", &Point::getX)
        ;
    
    m.attr('BOARD_ROW_SIZE') = BOARD_ROW_SIZE;
    m.attr('BOARD_COL_SIZE ') = BOARD_COL_SIZE;
    m.attr('K_IN_A_ROW') = K_IN_A_ROW;
    m.attr('MAX_TURNS') = MAX_TURNS;


    py::class_<Board>(m, "Point")
        .def(py::init<>())
        .def("init", &Point::init)
        .def("place", &Point::palce)
        .def("undo", &Point::undo)
        .def("checkLine", &Point::checkLine)
        .def("isGameOver", &Point::isGameOver)
        .def("switchMark", &Point::switchMark)
        .def("countDisc", &Point::countDisc)
        .def("getMark", &Point::getMark)
        .def("getMovablePosition", &Point::getMovablePosition)
        .def("getUpdate", &Point::getUpdate)
        .def("getCurrentMark", &Point::getCurrentMark)
        .def("getTurns", &Point::getTurns)
        ;
}