#include "FileAccess.hpp"
#include <iostream>
#include <set>
#include <map>
// #include <FileDirectory.h>
#include "User.hpp"
#include "FileDir_lz.cpp"
int cnt; //fd的序号
struct OpenFileTable {
    OpenFileTable(int t, int pno)
    {
        type = t;
        fd = ++cnt;
        Pno = pno;
    }
    int fd; //文件描述符
    int Pno; //文件编号
    int type; //打开方式
};
std::map <int, OpenFileTable> Fd2Table; //记录文件编号到文件打开表的映射

int opensize = 10; //最大打开文件数量

class Manager {
public:
    void Command(std::string s);

    void Create(char *path, int limit, int maxLength);

    int Open(char *path, int type);

    void Read(int FD, int beginPos, int len);

    void Write(int FD, int beginPos, int len, string s);

    void Close(int FD);

    void Delete(char* path);
};