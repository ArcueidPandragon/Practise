cmake_minimum_required(VERSION 3.28.1)

project (webserver)

set(CMAKE_CXX_STANDARD 11)

add_executable(web main.cpp eventLoop.cpp Epoll.cpp channel.cpp acceptor.cpp threadPool.cpp thread_.cpp error.cpp)

# Add -pthread compiler option
target_compile_options(web PRIVATE -pthread)

# Link pthread library
target_link_libraries(web PRIVATE pthread)
