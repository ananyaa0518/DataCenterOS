#ifndef PAGE_H
#define PAGE_H

namespace datacenteros {

struct Page {
    int pageId;
    int processId;

    Page(int id, int pid)
        : pageId(id), processId(pid) {}
};

}

#endif