#include <iostream>
#include <limits>

#include "simulation/Simulator.h"

using namespace datacenteros;

void showMenu() {
    std::cout << "\n";
    std::cout << "====================================\n";
    std::cout << "       DATACENTEROS SIMULATOR\n";
    std::cout << "====================================\n";
    std::cout << "1. Create Process\n";
    std::cout << "2. Display Processes\n";
    std::cout << "3. Run FCFS Scheduling\n";
    std::cout << "4. Run Round Robin Scheduling\n";
    std::cout << "5. Memory Access\n";
    std::cout << "6. Display Memory\n";
    std::cout << "7. Create File\n";
    std::cout << "8. Write File\n";
    std::cout << "9. Read File\n";
    std::cout << "10. Delete File\n";
    std::cout << "11. List Files\n";
    std::cout << "12. Synchronization Demo\n";
    std::cout << "13. Allocate Resource\n";
    std::cout << "14. Release Resource\n";
    std::cout << "15. Display Resources\n";
    std::cout << "0. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Enter choice: ";
}

int main() {
    Simulator simulator;

    int choice;

    do {
        showMenu();

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {

            case 1: {
                std::string name;
                int arrivalTime;
                int burstTime;
                int priority;

                std::cout << "Enter process name: ";
                std::cin >> name;

                std::cout << "Enter arrival time: ";
                std::cin >> arrivalTime;

                std::cout << "Enter burst time: ";
                std::cin >> burstTime;

                std::cout << "Enter priority: ";
                std::cin >> priority;

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
                int quantum;

                std::cout << "Enter time quantum: ";
                std::cin >> quantum;

                simulator.runRoundRobin(quantum);
                break;
            }

            case 5: {
                int pageId;
                int pid;

                std::cout << "Enter page ID: ";
                std::cin >> pageId;

                std::cout << "Enter process ID: ";
                std::cin >> pid;

                bool hit = simulator.getMemoryManager()
                               .accessPage(pageId, pid);

                if (hit) {
                    std::cout << "Page HIT\n";
                } else {
                    std::cout << "Page FAULT - Page loaded into memory\n";
                }

                break;
            }

            case 6:
                simulator.getMemoryManager().displayMemory();
                break;

            case 7: {
                std::string fileName;

                std::cout << "Enter file name: ";
                std::cin >> fileName;

                if (simulator.getFileSystem().createFile(fileName)) {
                    std::cout << "File created successfully.\n";
                } else {
                    std::cout << "File creation failed.\n";
                }

                break;
            }

            case 8: {
                std::string fileName;
                std::string content;

                std::cout << "Enter file name: ";
                std::cin >> fileName;

                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n'
                );

                std::cout << "Enter content: ";
                std::getline(std::cin, content);

                if (simulator.getFileSystem().writeFile(
                        fileName, content)) {
                    std::cout << "File written successfully.\n";
                } else {
                    std::cout << "File not found.\n";
                }

                break;
            }

            case 9: {
                std::string fileName;

                std::cout << "Enter file name: ";
                std::cin >> fileName;

                if (simulator.getFileSystem().exists(fileName)) {
                    std::cout << "File Content: "
                              << simulator.getFileSystem().readFile(fileName)
                              << "\n";
                } else {
                    std::cout << "File not found.\n";
                }

                break;
            }

            case 10: {
                std::string fileName;

                std::cout << "Enter file name: ";
                std::cin >> fileName;

                if (simulator.getFileSystem().deleteFile(fileName)) {
                    std::cout << "File deleted successfully.\n";
                } else {
                    std::cout << "File not found.\n";
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
                int pid;
                int amount;

                std::cout << "Enter PID: ";
                std::cin >> pid;

                std::cout << "Enter resource amount: ";
                std::cin >> amount;

                if (simulator.getResourceManager().allocate(pid, amount)) {
                    std::cout << "Resources allocated successfully.\n";
                } else {
                    std::cout << "Allocation failed.\n";
                }

                break;
            }

            case 14: {
                int pid;
                int amount;

                std::cout << "Enter PID: ";
                std::cin >> pid;

                std::cout << "Enter resource amount to release: ";
                std::cin >> amount;

                if (simulator.getResourceManager().release(pid, amount)) {
                    std::cout << "Resources released successfully.\n";
                } else {
                    std::cout << "Release failed.\n";
                }

                break;
            }

            case 15:
                simulator.getResourceManager().displayResources();
                break;

            case 0:
                std::cout << "Exiting DataCenterOS...\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}