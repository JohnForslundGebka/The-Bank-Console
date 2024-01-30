cmake_minimum_required(VERSION 3.26)
project(The_Bank_Console)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_LIST_DIR}/headerFiles)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/external/SQLiteCpp/.git")
	message(FATAL_ERROR "SQLiteCpp submodule does not exist. You must run 'git submodule update --init --recursive' to initialize it.")
else()
	message("-- SQLiteCpp submodule found.")
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/SQLiteCpp)


add_executable(The_Bank_Console main.cpp
        headerFiles/user.h
        headerFiles/account.h
        headerFiles/checkUserInput.h
        headerFiles/conversionRate.h
        headerFiles/login.h
        headerFiles/fillData.h
)

target_link_libraries(The_Bank_Console
        SQLiteCpp
        sqlite3
)


# Post-build command to copy database and CSV files to the same directory as the executable
add_custom_command(TARGET The_Bank_Console POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${CMAKE_SOURCE_DIR}/bankDatabase.db
                           $<TARGET_FILE_DIR:The_Bank_Console>/bankDatabase.db)
