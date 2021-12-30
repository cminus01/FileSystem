#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>

class FileAccess {
private:
    static const int maxn = 1 << 20;
public:
    char disk[maxn];

    std::set< std::pair<int, int> > remaining_space;
    FileAccess()
    {
        remaining_space.insert(std::make_pair(0, maxn-1));
    }

    // 申请一块空间，返回物理地址
    // 如果无法申请，返回-1
    int Apply(int size);

    // 删除从pos开始，长度为size的空间中的信息
    void Del(int pos, int size);

    // 读取begin开始，长度位len的空间中的信息
    void Read(int begin, int len);

    // 把begin开始，长度位len的空间中的信息写为s
    void Write(int begin, int len, std::string s);
};