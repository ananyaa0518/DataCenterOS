#ifndef DISK_REQUEST_H
#define DISK_REQUEST_H

namespace datacenteros {

struct DiskRequest {
    int requestId;
    int track;
    int processId;

    DiskRequest(int id, int trackNumber, int pid)
        : requestId(id),
          track(trackNumber),
          processId(pid) {}
};

}

#endif