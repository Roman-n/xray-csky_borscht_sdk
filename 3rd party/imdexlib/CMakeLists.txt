cmake_minimum_required(VERSION 3.15)
project(imdexlib LANGUAGES C CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE .)

