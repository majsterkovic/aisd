cmake_minimum_required(VERSION 3.17)
project(aisd_data)

set(CMAKE_CXX_STANDARD 20)

add_executable(aisd_data main.cpp generator.h LinkedList.h BST.h AVL.h)