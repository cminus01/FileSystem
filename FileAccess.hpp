#include <cstdio>
#include <vector>
#include <set>
#include <iostream>

class FileAccess {
public:
    struct Index {
        int num, beginPos, size;
        Index(int _num, int _beginPos, int _size) : num(_num), beginPos(_beginPos), size(_size) {}
    };
    std::vector<Index> index;
    std::set<std::pair<int, int>> remaining_space;
    FileAccess() : remaining_space({0, 999}) {}
    FileAccess(int size) : remaining_space({0, size-1}) {}
    // 申请一块空间，返回物理地址
    // 如果无法申请，返回-1
    int Apply(int size);
};