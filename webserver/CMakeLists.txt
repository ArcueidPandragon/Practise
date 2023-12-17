cmake_minimum_required (VERSION 2.8)

project (webserver)

set(CMAKE_CXX_STANDARD 11)

add_executable(web main.cpp eventLoop.cpp Epoll.cpp channel.cpp acceptor.cpp threadPool.cpp thread_.cpp)
