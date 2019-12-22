cmake_minimum_required(VERSION 3.8)

set(This Thor)

# Set project name.
project(${This} C CXX)

add_subdirectory(Server)
add_subdirectory(Client)