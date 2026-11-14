#include "disk/DiskScheduler.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace datacenteros {

DiskScheduler::DiskScheduler(int min, int max)
    : minTrack(min), maxTrack(max) {

    if (min < 0 || max <= min) {
        throw std::invalid_argument("Invalid disk range");
    }
}

DiskScheduleResult DiskScheduler::schedule(
    const std::vector<DiskRequest>& requests,
    int initialHead,
    DiskAlgorithm algorithm,
    Direction direction
) {

    if (initialHead < minTrack || initialHead > maxTrack) {
        throw std::out_of_range("Invalid initial head position");
    }

    for (const auto& r : requests) {
        if (r.track < minTrack || r.track > maxTrack) {
            throw std::out_of_range("Invalid request track");
        }
    }

    DiskScheduleResult result;
    result.headPath.push_back(initialHead);

    if (requests.empty()) {
        return result;
    }

    struct Event {
        int track;
        int requestIndex;
    };

    // requestIndex = -1 means a disk boundary.

    std::vector<Event> events;

    auto addEvent = [&](int track, int index) {
        events.push_back({track, index});
    };

    // FCFS
    if (algorithm == DiskAlgorithm::FCFS) {

        for (int i = 0; i < (int)requests.size(); i++) {
            addEvent(requests[i].track, i);
        }
    }

    // SSTF
    else if (algorithm == DiskAlgorithm::SSTF) {

        std::vector<int> remaining;

        for (int i = 0; i < (int)requests.size(); i++) {
            remaining.push_back(i);
        }

        int head = initialHead;

        while (!remaining.empty()) {

            auto nearest = std::min_element(
                remaining.begin(),
                remaining.end(),

                [&](int a, int b) {

                    int da = std::abs(requests[a].track - head);
                    int db = std::abs(requests[b].track - head);

                    if (da != db) {
                        return da < db;
                    }

                    return requests[a].requestId <
                           requests[b].requestId;
                }
            );

            int index = *nearest;

            addEvent(requests[index].track, index);

            head = requests[index].track;

            remaining.erase(nearest);
        }
    }

    // SCAN, C-SCAN and LOOK
    else {

        std::vector<int> atHead;
        std::vector<int> left;
        std::vector<int> right;

        for (int i = 0; i < (int)requests.size(); i++) {

            int track = requests[i].track;

            if (track == initialHead) {
                atHead.push_back(i);
            }
            else if (track < initialHead) {
                left.push_back(i);
            }
            else {
                right.push_back(i);
            }
        }

        auto ascending = [&](int a, int b) {
            if (requests[a].track != requests[b].track) {
                return requests[a].track < requests[b].track;
            }
            return requests[a].requestId < requests[b].requestId;
        };

        auto descending = [&](int a, int b) {
            if (requests[a].track != requests[b].track) {
                return requests[a].track > requests[b].track;
            }
            return requests[a].requestId < requests[b].requestId;
        };

        // Requests already under the head are served first.
        for (int i : atHead) {
            addEvent(initialHead, i);
        }

        if (direction == Direction::RIGHT) {

            std::sort(right.begin(), right.end(), ascending);
            std::sort(left.begin(), left.end(), descending);

            // Move right first.
            for (int i : right) {
                addEvent(requests[i].track, i);
            }

            if (algorithm == DiskAlgorithm::SCAN && !left.empty()) {
                addEvent(maxTrack, -1);
            }

            if (algorithm == DiskAlgorithm::CSCAN && !left.empty()) {
                addEvent(maxTrack, -1);
                addEvent(minTrack, -1);
            }

            // Reverse direction or wrap around.
            for (int i : left) {
                addEvent(requests[i].track, i);
            }
        }

        else {

            std::sort(left.begin(), left.end(), descending);
            std::sort(right.begin(), right.end(), ascending);

            // Move left first.
            for (int i : left) {
                addEvent(requests[i].track, i);
            }

            if (algorithm == DiskAlgorithm::SCAN && !right.empty()) {
                addEvent(minTrack, -1);
            }

            if (algorithm == DiskAlgorithm::CSCAN && !right.empty()) {
                addEvent(minTrack, -1);
                addEvent(maxTrack, -1);
            }

            // Reverse direction or wrap around.
            for (int i : right) {
                addEvent(requests[i].track, i);
            }
        }
    }

    // Calculate performance metrics.

    int currentHead = initialHead;

    long long elapsedMovement = 0;
    long long waitingTimeSum = 0;

    for (const auto& event : events) {

        long long movement = std::abs(
            event.track - currentHead
        );

        // Waiting time is recorded when a request starts service.
        if (event.requestIndex != -1) {

            result.serviceOrder.push_back(
                requests[event.requestIndex]
            );

            waitingTimeSum += elapsedMovement;
        }

        elapsedMovement += movement;

        currentHead = event.track;

        if (result.headPath.back() != currentHead) {
            result.headPath.push_back(currentHead);
        }
    }

    result.totalHeadMovement = elapsedMovement;

    result.averageSeekDistance =
        static_cast<double>(elapsedMovement) / requests.size();

    result.averageWaitingTime =
        static_cast<double>(waitingTimeSum) / requests.size();

    return result;
}

// Algorithm names.

std::string DiskScheduler::getAlgorithmName(
    DiskAlgorithm algorithm
) {

    switch (algorithm) {

        case DiskAlgorithm::FCFS:
            return "FCFS";

        case DiskAlgorithm::SSTF:
            return "SSTF";

        case DiskAlgorithm::SCAN:
            return "SCAN";

        case DiskAlgorithm::CSCAN:
            return "C-SCAN";

        case DiskAlgorithm::LOOK:
            return "LOOK";
    }

    return "Unknown";
}

}