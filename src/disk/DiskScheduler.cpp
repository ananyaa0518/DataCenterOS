#include "disk/DiskScheduler.h"

#include <algorithm>
#include <cmath>

namespace datacenteros {

// ==================== FCFS ====================

DiskScheduleResult DiskScheduler::FCFS(
    std::vector<DiskRequest> requests,
    int initialHead
) {
    DiskScheduleResult result;

    int currentHead = initialHead;
    int totalWaitingTime = 0;

    result.headPath.push_back(initialHead);

    for (const auto& request : requests) {

        int movement = std::abs(currentHead - request.track);

        result.totalHeadMovement += movement;

        totalWaitingTime += result.totalHeadMovement;

        currentHead = request.track;

        result.serviceOrder.push_back(request.requestId);
        result.headPath.push_back(currentHead);
    }

    if (!requests.empty()) {
        result.averageSeekDistance =
            static_cast<double>(result.totalHeadMovement) / requests.size();

        result.averageWaitingTime =
            static_cast<double>(totalWaitingTime) / requests.size();
    }

    return result;
}


// ==================== SSTF ====================

DiskScheduleResult DiskScheduler::SSTF(
    std::vector<DiskRequest> requests,
    int initialHead
) {
    DiskScheduleResult result;

    int currentHead = initialHead;
    int totalWaitingTime = 0;

    result.headPath.push_back(initialHead);

    while (!requests.empty()) {

        int closestIndex = 0;
        int minimumDistance =
            std::abs(currentHead - requests[0].track);

        // Find the request closest to the current head
        for (int i = 1; i < static_cast<int>(requests.size()); i++) {

            int distance =
                std::abs(currentHead - requests[i].track);

            if (distance < minimumDistance) {
                minimumDistance = distance;
                closestIndex = i;
            }
        }

        // Select the closest request
        DiskRequest selectedRequest = requests[closestIndex];

        // Calculate head movement
        int movement =
            std::abs(currentHead - selectedRequest.track);

        result.totalHeadMovement += movement;

        totalWaitingTime += result.totalHeadMovement;

        // Move disk head
        currentHead = selectedRequest.track;

        // Record result
        result.serviceOrder.push_back(selectedRequest.requestId);
        result.headPath.push_back(currentHead);

        // Remove serviced request
        requests.erase(requests.begin() + closestIndex);
    }

    if (!result.serviceOrder.empty()) {
        result.averageSeekDistance =
            static_cast<double>(result.totalHeadMovement)
            / result.serviceOrder.size();

        result.averageWaitingTime =
            static_cast<double>(totalWaitingTime)
            / result.serviceOrder.size();
    }

    return result;
}

}