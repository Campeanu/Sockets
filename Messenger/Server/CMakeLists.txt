cmake_minimum_required(VERSION 3.8)

set(This Server)

set(HEADERS
    include/Server/Server.h
)

set(SOURCES 
    src/Server.cpp
    src/main.cpp
)

add_executable(${This} ${SOURCES} ${HEADERS})

target_include_directories(${This} PUBLIC include)