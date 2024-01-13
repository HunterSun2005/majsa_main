cmake_minimum_required(VERSION 3.27)
project(majsa_main C)

set(CMAKE_C_STANDARD 11)

add_executable(majsa_main
        src/main.c
        src/majsa.c
        src/YakuChecker.c
        src/Calculator.c
        src/AgariChecker.c
        src/NewDef.h)
