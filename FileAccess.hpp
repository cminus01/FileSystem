#include <cstdio>

class FileAccess {
public:
    struct Index {
        int num, beginPos, size;
    };
    // 申请一块空间，返回物理地址
    // 如果无法申请，返回-1
    int Apply(int size);
};