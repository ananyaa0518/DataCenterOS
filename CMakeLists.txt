cmake_minimum_required(VERSION 3.16)

project(DataCenterOS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(DataCenterOS
    src/main.cpp

    # Process
    src/process/ProcessManager.cpp
    src/process/Scheduler.cpp
    src/process/ContextSwitch.cpp

    # Disk
    src/disk/DiskRequest.cpp
    src/disk/DiskScheduler.cpp

    # Memory
    src/memory/MemoryManager.cpp
    src/memory/PageTable.cpp

    # File System
    src/filesystem/FileSystem.cpp

    # Synchronization
    src/synchronization/Mutex.cpp
    src/synchronization/SynchronizationManager.cpp

    # Resource Management
    src/resource/DeadlockManager.cpp

    # Simulation
    src/simulation/Simulator.cpp

    # Analytics
    src/analytics/MetricsEngine.cpp
)

target_include_directories(DataCenterOS PRIVATE include)

if(MSVC)
    target_compile_options(DataCenterOS PRIVATE /W4)
else()
    target_compile_options(DataCenterOS PRIVATE -Wall -Wextra -Wpedantic)
endif()