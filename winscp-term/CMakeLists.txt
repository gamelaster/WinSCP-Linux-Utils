cmake_minimum_required(VERSION 3.26)
project(winscp_term)

set(CMAKE_CXX_STANDARD 17)

add_executable(winscp_term main.cpp)
target_link_options(winscp_term PRIVATE -static)
