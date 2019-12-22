cmake_minimum_required(VERSION 3.8)

set(This Client)

set(HEADERS
    include/Client/Client.h
)

set(SOURCES 
    src/Client.cpp
    src/main.cpp
)

add_executable(${This} ${SOURCES} ${HEADERS})

target_include_directories(${This} PUBLIC include)