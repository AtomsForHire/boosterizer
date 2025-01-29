cmake_minimum_required(VERSION 3.10)

project(boosteriser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(boosterise src/main.cpp src/card_list.cpp)

target_include_directories(boosterise PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

