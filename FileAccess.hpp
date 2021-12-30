#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <string>

class FileAccess {
public:
    char disk[1024*1024];
    struct eBlock
    {
        int pos;
        int size;
        struct eBlock* nt;
    };
    FileAccess()
    {
        
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