cmake_minimum_required(VERSION 3.21)
project(Payment_Application C)

set(CMAKE_C_STANDARD 11)

include_directories(src/Application)
include_directories(src/Card)
include_directories(src/Server)
include_directories(src/Terminal)
include_directories(utils)

add_executable(Payment_Application
        src/Application/app.c
        src/Application/app.h
        src/Card/card.c
        src/Card/card.h
        src/Server/server.c
        src/Server/server.h
        src/Terminal/terminal.c
        src/Terminal/terminal.h
        utils/types.h
        main.c)
