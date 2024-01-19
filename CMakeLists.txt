cmake_minimum_required(VERSION 3.26)
project(The_Bank_Console)

set(CMAKE_CXX_STANDARD 20)

add_executable(The_Bank_Console main.cpp
        user.h
        account.h)
