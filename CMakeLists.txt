cmake_minimum_required(VERSION 3.27)
project(majsa_main C)

set(CMAKE_C_STANDARD 11)

add_executable(majsa_main
        src/main.c
        src/main.h
        src/majsa.c
        src/majsa.h
        src/YakuChecker.c
        src/YakuChecker.h
        src/Calculator.c
        src/Calculator.h
        src/AgariChecker.c
        src/AgariChecker.h
        src/NewDef.h)
