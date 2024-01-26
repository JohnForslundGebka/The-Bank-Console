cmake_minimum_required(VERSION 3.26)
project(The_Bank_Console)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/SQLiteCpp)


add_executable(The_Bank_Console main.cpp
        user.h
        account.h
)

target_link_libraries(The_Bank_Console
        SQLiteCpp
        sqlite3
        pthread
        dl
)
