# DataCenterOS – Smart Storage OS Simulator

A C++17-based operating system simulator that demonstrates core OS concepts including process management, CPU scheduling, memory management, disk scheduling, file systems, synchronization, and resource allocation.

## Features

- **Process Management:** Create, manage, and terminate processes using PCB and process states.
- **CPU Scheduling:** FCFS and Round Robin scheduling.
- **Context Switching:** Simulate saving and restoring process contexts.
- **Memory Management:** Paging, page tables, page faults, and FIFO page replacement.
- **Disk Scheduling:** FCFS and SSTF algorithms.
- **File System:** Create, read, write, delete, and list files.
- **Synchronization:** Mutex and shared-resource management.
- **Resource Management:** Basic resource allocation and release.
- **Metrics:** Track waiting time, turnaround time, page faults, and disk-head movement.

## Tech Stack

- C++17
- STL
- CMake
- GCC / Clang

## Build & Run

```bash
cmake -S . -B build
cmake --build build
./build/DataCenterOS
```

## Project Structure

```text
DataCenterOS/
├── include/
├── src/
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Project Goal

To simulate how an operating system manages processes, memory, storage, and resources while demonstrating fundamental OS algorithms through an interactive application.
