cmake_minimum_required(VERSION 3.20)

Project(CTP)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(
    main 
   
    src/lexer.c
    src/parser.c
    src/file.c
    src/vector.c
    src/hashmap.c
    src/main.c
)
