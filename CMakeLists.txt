cmake_minimum_required(VERSION 3.17)
project(implementations)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp deque.h list.h stack.h vector.h treap.h)
