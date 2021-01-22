cmake_minimum_required(VERSION 3.10)

project(rgb2bin)

add_executable(
    rgb2bin
    src/main.c
)

install(TARGETS rgb2bin DESTINATION bin)
