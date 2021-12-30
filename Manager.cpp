#include "Manager.hpp"

FileDirectory fd;
FileAccess space;

void Manager::Command(std::string s)
{
    if (s == "Create") 
    {
        int limit, maxLength;
        char path[1024];

        scanf("%s", path);
        std::cin >> limit >> maxLength;
        Create(path, limit, maxLength);
    }
    else if (s == "Open") 
    {
        int type;
        char path[1024];

        scanf("%s", path);
        std::cin >> type;
        int FD = Open(path, type);
        if (FD == -1)
        {
            return ;
        }
        cout << "FD: " << FD << endl;
        cout.flush();
    }
    else if (s == "Read") 
    {
        int FD, beginPos, len;

        std::cin >> FD >> beginPos >> len;
        Read(FD, beginPos, len);
    }
    else if (s == "Write")
    {
        int FD, beginPos, len;
        string c;

        std::cin >> FD >> beginPos >> len;
        std::cin >> c;
        Write(FD, beginPos, len, c);
    }
    else if (s == "Close")
    {
        int FD;
        std::cin >> FD;

        Close(FD);
    }
    else if (s == "Delete")
    {
        char path[1024];

        scanf("%s", path);
        Delete(path);
    }
    else if (s == "ls")
    {
        if (now == "")
        {
            fd.show_All();
        }
        else
        {
            fd.show_all(ts(now));
        }
    }
    else if (s == "cd")
    {
        std::string pos;
        std::cin >> pos;

        fd.Goto(pos);
    }
    else if (s == "ll")
    {
        fd.LL();
    }
    else
    {
        std::cerr << "没有这个命令！" << std::endl;
    }
}

void Manager::Create(char *path, int limit, int maxLength)
{
    if (!fd.check(path)) 
    {
        std::cerr << "创建失败，不符合命名规范！" << std::endl;
        return ;
    }
    if (!fd.check_double(path))
    {
        std::cerr << "创建失败，有重名文件！" << std::endl;
        return ;
    }
    int num = space.Apply(maxLength);
    if (num == -1)
    {
        std::cerr << "创建失败，空间不足！" << std::endl;
        return ;
    }
    if (mfd.Main[ts(now)].size > 10)
    {
        std::cerr << "创建失败，目录已满！" << std::endl;
        return ;
    }
    fd.Create(path, num, limit, maxLength);
    return ;
}

int Manager::Open(char *path, int type)
{
    if (fd.check_double(path))
    {
        std::cerr << "打开失败，不存在这个文件！" << std::endl;
        return ;
    }
    FCB* file = fd.FindPos(path);
    if (ts(file->use_name) != state)
    {
        std::cerr << "打开失败，没有权限！" << std::endl;
        return -1;
    }
    if (Fd2Table.size() >= opensize) 
    {
        std::cerr << "打开失败，打开数量已满！" << std::endl;
        return -1;
    }
    else
    {
        OpenFileTable a(type, file->Pno);
        Fd2Table[a.fd] = a;
        return a.fd;
    }
}

void Manager::Read(int FD, int beginPos, int len)
{
    if (Fd2Table.find(FD) == Fd2Table.end())
    {
        std::cerr << "读失败，不存在这个文件！" << std::endl;
        return ;
    }
    FCB* file = fd.Pno2FCB(Fd2Table[FD].Pno);
    if (ts(file->use_name) != state || !(file->limit & (1 << 2)))
    {
        std::cerr << "读失败，没有权限！" << std::endl;
        return ;
    }
    space.Read(file->address + beginPos, len);
}

void Manager::Write(int FD, int beginPos, int len, string s)
{
    if (Fd2Table.find(FD) == Fd2Table.end())
    {
        std::cerr << "写失败，不存在这个文件！" << std::endl;
        return ;
    }
    FCB* file = fd.Pno2FCB(Fd2Table[FD].Pno);
    if (ts(file->use_name) != state || !(file->limit & (1 << 1)))
    {
        std::cerr << "写失败，没有权限！" << std::endl;
        return ;
    }
    space.Write(file->address + beginPos, len, s);
}

void Manager::Close(int FD)
{
    if (Fd2Table.find(FD) == Fd2Table.end())
    {
        std::cerr << "关闭失败，不存在这个文件！" << std::endl;
        return ;
    }
    else
    {
        Fd2Table.erase(FD);
    }
}

void Manager::Delete(char* path)
{
    if (fd.check_double(path))
    {
        std::cerr << "删除失败，不存在该文件！" << std::endl;
        return ;
    }
    else
    {
        FCB* file = fd.FindPos(path);
        for (auto [a, b]:Fd2Table)
        {
            if (b.Pno == file->Pno)
            {
                std::cerr << "删除失败，该文件未被全部关闭！" << std::endl;
                return ;
            }
        }
        if (ts(file->use_name) != state)
        {
            std::cerr << "删除失败，没有权限！" << std::endl;
            return ;
        }
        space.Del(file->address, file->size);
        fd.Delete(path);
    }
    return ;
}