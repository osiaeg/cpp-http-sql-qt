cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(http_client VERSION 1.0.0 DESCRIPTION "GUI-клиент редактирования БД")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(client
        src/http_client/http_client.cpp
        src/http_client/mainwindow.cpp
        src/http_client/mainwindow.h
        )
target_link_libraries(client PRIVATE Qt6::Core Qt6::Widgets)

enable_testing()
add_subdirectory(test)