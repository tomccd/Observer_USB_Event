cmake_minimum_required(VERSION 3.5)
project(USB_Handle)
set(CMAKE_CXX_STANDARD 11)

add_library(
    USB_Manager
    ${CMAKE_CURRENT_SOURCE_DIR}/src/USB_Manager.cpp
)

target_link_libraries(
    USB_Manager
    stdc++fs
)

add_executable(
    main
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/header/USB_Manager.hpp 
)

target_link_libraries(
    main
    USB_Manager
)
