#ifndef DISK_SCHEDULER_H
#define DISK_SCHEDULER_H

#include "disk/DiskRequest.h"

#include <string>
#include <vector>

namespace datacenteros {

enum class DiskAlgorithm {
    FCFS,
    SSTF,
    SCAN,
    CSCAN,
    LOOK
};

enum class Direction {
    LEFT,
    RIGHT
};

struct DiskScheduleResult {
    std::vector<DiskRequest> serviceOrder;
    std::vector<int> headPath;

    long long totalHeadMovement = 0;

    double averageSeekDistance = 0.0;
    double averageWaitingTime = 0.0;
};

class DiskScheduler {

private:
    int minTrack;
    int maxTrack;

public:
    DiskScheduler(int min = 0, int max = 199);

    DiskScheduleResult schedule(
        const std::vector<DiskRequest>& requests,
        int initialHead,
        DiskAlgorithm algorithm,
        Direction direction = Direction::RIGHT
    );

    static std::string getAlgorithmName(
        DiskAlgorithm algorithm
    );
};

}

#endif