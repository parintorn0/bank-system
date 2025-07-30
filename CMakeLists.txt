cmake_minimum_required(VERSION 3.31)
project(bank-system)

set(CMAKE_CXX_STANDARD 23)

add_executable(bank-system
        src/main.cpp
        src/FunctionHub.hpp
        src/FunctionHub.cpp
        src/Mainmenu.hpp
        src/Mainmenu.cpp
        src/Bank.hpp
        src/Bank.cpp
        src/Admin.hpp
        src/Admin.cpp
        src/User.hpp
        src/User.cpp
)

add_custom_command(
        TARGET bank-system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}
)