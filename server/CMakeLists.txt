cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(http_server VERSION 1.0.0 DESCRIPTION "HTTP-сервер")
add_executable(server src/http_server/http_server.cpp)
add_library(pgconnection src/http_server/pgconnection.cpp src/http_server/pgconnection.h)

find_package(Crow)
find_package(PostgreSQL)

target_link_libraries(server PUBLIC
        Crow::Crow
        -lpq
        -lpqxx
        pgconnection
        )

#include_directories(${CMAKE_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(test)
