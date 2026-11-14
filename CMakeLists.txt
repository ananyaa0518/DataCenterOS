cmake_minimum_required(VERSION 3.16)

project(DataCenterOS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(DataCenterOS

    src/main.cpp

    src/disk/DiskRequest.cpp
    src/disk/DiskScheduler.cpp

    src/process/ContextSwitch.cpp

)

target_include_directories(DataCenterOS PRIVATE include)

if(MSVC)
    target_compile_options(DataCenterOS PRIVATE /W4)
else()
    target_compile_options(DataCenterOS PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()