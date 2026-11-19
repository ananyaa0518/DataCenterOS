#include <iostream>
#include <limits>
#include <string>

#include "simulation/Simulator.h"

using namespace datacenteros;

static int readInt(const std::string& prompt, int minValue = std::numeric_limits<int>::min()) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            if (val >= minValue) {
                return val;
            }
            std::cout << "Value must be at least " << minValue << ". Please try again.\n";
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer.\n";
        }
    }
}

static std::string readString(const std::string& prompt) {
    std::string val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && !val.empty()) {
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid string.\n";
    }
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string val;
    std::getline(std::cin, val);
    return val;
}

void showMenu() {
    std::cout << "\n";
    std::cout << "====================================\n";
    std::cout << "       DATACENTEROS SIMULATOR\n";
    std::cout << "====================================\n";
    std::cout << " 1. Create Process\n";
    std::cout << " 2. Display Processes\n";
    std::cout << " 3. Run FCFS Scheduling\n";
    std::cout << " 4. Run Round Robin Scheduling\n";
    std::cout << " 5. Memory Access\n";
    std::cout << " 6. Display Memory\n";
    std::cout << " 7. Create File\n";
    std::cout << " 8. Write File\n";
    std::cout << " 9. Read File\n";
    std::cout << "10. Delete File\n";
    std::cout << "11. List Files\n";
    std::cout << "12. Synchronization Demo\n";
    std::cout << "13. Allocate Resource\n";
    std::cout << "14. Release Resource\n";
    std::cout << "15. Display Resources\n";
    std::cout << "16. Disk Scheduling\n";
    std::cout << "17. Display System Metrics\n";
    std::cout << "18. Reset Simulation / Processes\n";
    std::cout << " 0. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Enter choice: ";
}

int main() {
    Simulator simulator;

    int choice;

    do {
        showMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Invalid input. Please enter a valid menu number.\n";
            continue;
        }

        switch (choice) {

            case 1: {
                std::string name = readString("Enter process name: ");
                int arrivalTime = readInt("Enter arrival time (>= 0): ", 0);
                int burstTime = readInt("Enter burst time (> 0): ", 1);
                int priority = readInt("Enter priority: ");

                simulator.getProcessManager().createProcess(
                    name,
                    arrivalTime,
                    burstTime,
                    priority
                );

                break;
            }

            case 2:
                simulator.displayProcesses();
                break;

            case 3:
                simulator.runFCFS();
                break;

            case 4: {
                int quantum = readInt("Enter time quantum (> 0): ", 1);
                simulator.runRoundRobin(quantum);
                break;
            }

            case 5: {
                int pageId = readInt("Enter page ID (>= 0): ", 0);
                int pid = readInt("Enter process ID (>= 0): ", 0);

                bool hit = simulator.getMemoryManager()
                               .accessPage(pageId, pid);

                if (hit) {
                    std::cout << "Page HIT - Page " << pageId << " already in memory.\n";
                } else {
                    std::cout << "Page FAULT - Page " << pageId << " loaded into memory.\n";
                }

                break;
            }

            case 6:
                simulator.getMemoryManager().displayMemory();
                break;

            case 7: {
                std::string fileName = readString("Enter file name: ");

                if (simulator.getFileSystem().createFile(fileName)) {
                    std::cout << "File created successfully.\n";
                } else {
                    std::cout << "File creation failed (file already exists or invalid name).\n";
                }

                break;
            }

            case 8: {
                std::string fileName = readString("Enter file name: ");
                std::string content = readLine("Enter content: ");

                if (simulator.getFileSystem().writeFile(fileName, content)) {
                    std::cout << "File written successfully.\n";
                } else {
                    std::cout << "Error: File '" << fileName << "' not found.\n";
                }

                break;
            }

            case 9: {
                std::string fileName = readString("Enter file name: ");

                if (simulator.getFileSystem().exists(fileName)) {
                    std::cout << "File Content: "
                              << simulator.getFileSystem().readFile(fileName)
                              << "\n";
                } else {
                    std::cout << "Error: File '" << fileName << "' not found.\n";
                }

                break;
            }

            case 10: {
                std::string fileName = readString("Enter file name: ");

                if (simulator.getFileSystem().deleteFile(fileName)) {
                    std::cout << "File deleted successfully.\n";
                } else {
                    std::cout << "Error: File '" << fileName << "' not found.\n";
                }

                break;
            }

            case 11:
                simulator.getFileSystem().listFiles();
                break;

            case 12:
                simulator.getSynchronizationManager().demonstrate();
                break;

            case 13: {
                int pid = readInt("Enter PID (> 0): ", 1);
                int amount = readInt("Enter resource amount (> 0): ", 1);

                if (simulator.getResourceManager().allocate(pid, amount)) {
                    std::cout << "Resources allocated successfully.\n";
                } else {
                    std::cout << "Allocation failed (not enough available resources or invalid parameters).\n";
                }

                break;
            }

            case 14: {
                int pid = readInt("Enter PID (> 0): ", 1);
                int amount = readInt("Enter resource amount to release (> 0): ", 1);

                if (simulator.getResourceManager().release(pid, amount)) {
                    std::cout << "Resources released successfully.\n";
                } else {
                    std::cout << "Release failed (PID not found, invalid amount, or exceeds allocated).\n";
                }

                break;
            }

            case 15:
                simulator.getResourceManager().displayResources();
                break;

            case 16: {
                std::cout << "\n--- Disk Scheduling Menu ---\n";
                std::cout << "1. Add Disk Request\n";
                std::cout << "2. View Disk Requests\n";
                std::cout << "3. Run FCFS Disk Scheduling\n";
                std::cout << "4. Run SSTF Disk Scheduling\n";
                std::cout << "5. Clear Disk Requests\n";
                int diskChoice = readInt("Enter choice (1-5): ", 1);

                if (diskChoice == 1) {
                    int track = readInt("Enter track number (>= 0): ", 0);
                    int pid = readInt("Enter requesting PID (>= 0): ", 0);
                    simulator.addDiskRequest(track, pid);
                } else if (diskChoice == 2) {
                    simulator.displayDiskRequests();
                } else if (diskChoice == 3) {
                    int head = readInt("Enter initial head position (>= 0): ", 0);
                    simulator.runDiskFCFS(head);
                } else if (diskChoice == 4) {
                    int head = readInt("Enter initial head position (>= 0): ", 0);
                    simulator.runDiskSSTF(head);
                } else if (diskChoice == 5) {
                    simulator.clearDiskRequests();
                } else {
                    std::cout << "Invalid disk option.\n";
                }
                break;
            }

            case 17:
                simulator.displayMetrics();
                break;

            case 18: {
                std::cout << "\n--- Reset Options ---\n";
                std::cout << "1. Reset Processes to READY (for re-running scheduling)\n";
                std::cout << "2. Reset Memory (clear frames, page table & stats)\n";
                std::cout << "3. Reset Entire Simulation\n";
                int resetChoice = readInt("Enter choice (1-3): ", 1);

                if (resetChoice == 1) {
                    simulator.resetProcesses();
                } else if (resetChoice == 2) {
                    simulator.getMemoryManager().reset();
                    std::cout << "Memory has been reset.\n";
                } else if (resetChoice == 3) {
                    simulator.resetSimulation();
                } else {
                    std::cout << "Invalid reset option.\n";
                }
                break;
            }

            case 0:
                std::cout << "Exiting DataCenterOS...\n";
                break;

            default:
                std::cout << "Invalid choice. Please select an option from the menu.\n";
        }

    } while (choice != 0);

    return 0;
}
