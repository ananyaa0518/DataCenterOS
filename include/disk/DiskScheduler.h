#ifndef DISK_SCHEDULER_H
#define DISK_SCHEDULER_H

#include <vector>
#include "disk/DiskRequest.h"

namespace datacenteros {

struct DiskScheduleResult {
    std::vector<int> serviceOrder;
    std::vector<int> headPath;

    int totalHeadMovement = 0;
    double averageSeekDistance = 0.0;
    double averageWaitingTime = 0.0;
};

class DiskScheduler {
public:
    DiskScheduleResult FCFS(
        std::vector<DiskRequest> requests,
        int initialHead
    );

    DiskScheduleResult SSTF(
        std::vector<DiskRequest> requests,
        int initialHead
    );
};

}

#endif