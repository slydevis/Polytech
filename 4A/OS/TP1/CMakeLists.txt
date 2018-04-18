cmake_minimum_required(VERSION 3.8)
project(TP1)

find_package("Threads")

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(TP1.out ${SOURCE_FILES})

target_link_libraries(TP1.out ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(TP1.out rt)
