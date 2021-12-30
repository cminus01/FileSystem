cmake_minimum_required(VERSION 3.9)
project(FileSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(FileSystem 
    main.cpp 
    User.hpp 
    FileDir_lz.cpp 
    FileAccess.cpp 
    Manager.cpp
)
