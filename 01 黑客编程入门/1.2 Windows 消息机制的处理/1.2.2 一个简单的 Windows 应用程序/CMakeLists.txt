cmake_minimum_required(VERSION 3.21)
project(app)

add_compile_definitions(app UNICODE _UNICODE)
add_executable(app WIN32 app.cpp)
