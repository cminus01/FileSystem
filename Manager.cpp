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

int FileAccess::Apply(int size) {
	auto it = remaining_space.begin();

	// ������ѯ�Ƿ����㹻��С������ʣ��ռ�
	while (it != remaining_space.end()) {
		int x = it->first;
		int y = it->second;
		if (y - x + 1 < size) {
			// �������ռ䲻���󣬽��Ų�ѯ��һ�������ռ�
			++it;
			continue;
		}
		else {
			// �������ռ��㹻��
			it = remaining_space.erase(it);
			// ����С�㹻�Ŀ鲻�ᱻ���꣬����û�õ��Ĳ���
			if (x + size <= y) {
				remaining_space.insert(std::make_pair(x, x + size));
			}
			return x;
		}
	}

	return -1;
}

void FileAccess::Del(int pos, int size) {
	// ����ʣ��ռ�
	remaining_space.insert(std::make_pair(pos, pos + size - 1));

	// ����������ʣ��ռ��Ƿ������ʣ��ռ�����������������ϲ�
	auto it = remaining_space.find(std::make_pair(pos, pos + size - 1));
	auto tmp = it;
	if (it != remaining_space.begin()) {
		--tmp;
		if (tmp->second + 1 == it->first) {
			int x = tmp->first;
			int y = it->second;
			remaining_space.erase(tmp);
			remaining_space.erase(it);
			remaining_space.insert(std::make_pair(x, y));
			it = remaining_space.find(std::make_pair(x, y));
		}
		tmp = it;
	}
	++tmp;
	if (tmp != remaining_space.end()) {
		if (it->second + 1 == tmp->first) {
			int x = it->first;
			int y = tmp->second;
			remaining_space.erase(tmp);
			remaining_space.erase(it);
			remaining_space.insert(std::make_pair(x, y));
		}
	}
}

void FileAccess::Read(int begin, int len) {
	// ��������洢��Ϣ
	for (int i = begin; i < begin + len; ++i) {
		printf("%c", disk[i]);
	}
	printf("\n");
}

void FileAccess::Write(int begin, int len, std::string s) {
	// ����д��洢��Ϣ
	for (int i = 0; i < len; ++i) {
		disk[begin + i] = s[i];
	}
}
using namespace std;
int state;
class User
{
private:
    string password;
public:
    string name; 
    void init(string n, string p)
    {
        name = n; 
        password = p;
    }
    // 登出
    void logout()
    {
        state = 0;
    }
    // 返回是否登陆成功
    bool login()
    {
        std::cout << "Password: ";
        std::cout.flush();
        std::string pwd;
        std::cin >> pwd;
        if (pwd == password)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void show()
    {
        std::cout << "[" << name << "]:";
    }
}user[10];

std::map<std::string, int> mp;

string now; //当前目录
struct FCB
{
    int Pno; // 此目录里面的编号
    int size; // 大小
    string name; //用户中文件名
    string use_name; //用户
    int limit; //属性 ->只读/写/均可
    int address; // 地址
};

struct UFDnode{ // 用户文件目录
    string use_name; //用户名
    int size;//用户文件大小
    FCB fcb[10];
};

struct MFD{ //用户目录
    int size;//用户大小
    UFDnode Main[10];
}mfd; 

int ts(std::string now)
{
    for (int i = 0; i < 10; i++)
        if (mfd.Main[i].use_name == now)
        {
            return i;
        }
}
char tmp[10];
char* trans(int l)
{
    tmp[0] = tmp[1] = tmp[2] = '-';
    tmp[3] = '\n';
    if (l & (1 << 2))   tmp[0] = 'r';
    if (l & (1 << 1))   tmp[1] = 'w';
    if (l & (1 << 0))   tmp[2] = 'x';
    return tmp;
}

class FileDirectory {
public:

    // 是否合法
    bool check(char* name){
        bool ok = 0;
        string s;int len = strlen(name);
        for(int i = 0;i < len; ++i){
            if(name[i] == '\\') {ok = 1;continue;}
            if(ok == 1) s += name[i]; 
        }
        if(ok == 1 && !s.empty()){ return true;
        }
        else return false;
    }

    // 判重
    // true: 没有重复
    // false: 有重复
    bool check_double(char *path){
        bool ok = check(path);
        if (ok == false) {
            std::cerr << "路径不合法！" << std::endl;
            exit(1);
        }
        string use_name;
        string name;
        int len = strlen(path);
        ok = 0;
        for(int i = 0;i < len; ++i){
            if(path[i] == '\\') {ok = 1;continue;}
            if(ok == 0){use_name += path[i];}
            else {name += path[i];}
        }
        for(int i = 0;i < mfd.size; ++i){
            for(int j = 0;j < mfd.Main[i].size; ++j){
                if(mfd.Main[i].fcb[j].name == name && mfd.Main[i].fcb[j].use_name == use_name){
                    now = mfd.Main[i].use_name;
                    return false;
                }
            }
        }
        return true;
    }

    // ls
    void show_all(int no){ //用户名编号
        for(int i = 0;i < mfd.Main[no].size; ++i){
            cout << mfd.Main[no].fcb[i].name << " ";
        }
        cout << endl;
    }
    void show_All(){
        for(int i = 0;i < mfd.size; ++i){
            cout << mfd.Main[i].use_name << " ";
        }
        cout << endl;
    }

    //ll
    void LL()
    {
        if (now == "")
        {
            for(int i = 0;i < mfd.size; ++i){
                if (mfd.Main[i].use_name == user[state].name)
                {
                    printf("drwx %8s %6d ", user[state].name, mfd.Main[i].size);
                }
                else
                {
                    printf("dr-- %8s %6d ", mfd.Main[i].use_name, mfd.Main[i].size);
                }
                cout << mfd.Main[i].use_name << "/" << endl;
            }
        }
        else
        {
            int no = ts(now);
            for(int i = 0; i < mfd.Main[no].size; ++i){
                if (now == user[state].name)
                {
                    printf("-%s %8s %6d ", trans(mfd.Main[i].fcb->limit), user[state].name, mfd.Main[no].fcb[i].size);
                }
                else
                {
                    printf("---- %8s %6d ", mfd.Main[no].fcb[i].use_name, mfd.Main[no].fcb[i].size);
                }
                cout << mfd.Main[no].fcb[i].name << endl;
            }
        }
    }

    // cd
    void Goto(string name){
        if(name == ".."){
            now = "";
        }
        else {
            if (now != "")
            {
                cerr << "没有这个文件或者目录" << endl;
                return ;
            }
            now = name;
        }
    }


    //通过文件的Pno去找其FCB
    FCB* Pno2FCB(int fd){
        for(int i = 0;i < mfd.size; ++i){
            for(int j = 0;j < mfd.Main[i].size; ++j){
                if(mfd.Main[i].fcb[j].Pno == fd){
                    now = mfd.Main[i].use_name;
                    return &mfd.Main[i].fcb[j];
                }
            }
        }
        return nullptr;      
    }


    //通过路径去找FCB
    FCB* FindPos(char* path){
        bool ok = check(path);
        if(ok == false) return nullptr;
        string use_name;
        string name;
        int len = strlen(path);
        ok = 0;
        for(int i = 0;i < len; ++i){
            if(path[i] == '\\') {ok = 1;continue;}
            if(ok == 0){use_name += path[i];}
            else {name += path[i];}
        }
        for(int i = 0;i < mfd.size; ++i){
            for(int j = 0;j < mfd.Main[i].size; ++j){
                if(mfd.Main[i].fcb[j].name == name && mfd.Main[i].fcb[j].use_name == use_name){
                    now = mfd.Main[i].use_name;
                    return &mfd.Main[i].fcb[j];
                }
            }
        }
    }
    void Create(char *path, int pos, int limit, int maxLength){
        string use_name;
        string name;
        int len = strlen(path);
        int ok = 0;
        for(int i = 0;i < len; ++i){
            if(path[i] == '\\') {ok = 1;continue;}
            if(ok == 0){use_name += path[i];}
            else {name += path[i];}
        }
        int size;
        int id;
        for(int i = 0;i < mfd.size; ++i){
            if(mfd.Main[i].use_name == use_name){
                size = mfd.Main[i].size;
                id = i;
                break;
            }
        }
        mfd.Main[state].fcb[size].use_name = use_name;
        mfd.Main[state].fcb[size].name = name;
        mfd.Main[state].fcb[size].address = pos;
        mfd.Main[state].fcb[size].size = maxLength;
        mfd.Main[state].fcb[size].limit = limit;
        mfd.Main[id].size++;

    }
    void Delete(char *path){
        string use_name;
        string name;
        int len = strlen(path);
        int ok = 0;
        for(int i = 0;i < len; ++i){
            if(path[i] == '\\') {ok = 1;continue;}
            if(ok == 0){use_name += path[i];}
            else {name += path[i];}
        }
        for(int i = 0;i < mfd.size; ++i){
            if(mfd.Main[i].use_name == use_name){
                int id;
                for(int j = 0;j < mfd.Main[i].size; ++i){
                    if(mfd.Main[i].fcb[j].name == name){
                        id = j;
                        break;
                    }
                }
                reverse(mfd.Main[i].fcb + id,mfd.Main[i].fcb + mfd.Main[i].size);
                mfd.Main[i].size--;
                reverse(mfd.Main[i].fcb + id,mfd.Main[i].fcb + mfd.Main[i].size);
                return ;
            }
        }
    }
};

class Manager {
private:
    int cnt; //fd的序号
    struct OpenFileTable {
        int fd; //文件描述符
        int Pno; //文件编号
        int type; //打开方式
        void init(int t, int pno, int cnt)
        {
            type = t;
            fd = cnt;
            Pno = pno;
        }
    };
    std::map <int, OpenFileTable> Fd2Table; //记录文件编号到文件打开表的映射

    int opensize = 5; //最大打开文件数量
public:
    // 解析所有命令
    void Command(std::string s);

    /** 
     * 写一个文件
     * @param[in]   path    文件路径
     * @param[in]   limit   文件限制
     * @param[in]   maxLength   文件最大大小
     * 
     */
    void Create(char *path, int limit, int maxLength);

    /** 
     * 写一个文件
     * @param[in]   path    文件路径
     * @param[in]   type    模式
     * 
     */
    int Open(char *path, int type);

    /** 
     * 读一个文件
     * @param[in]   FD    文件描述符
     * @param[in]   beginPos    开始位置
     * @param[in]   len 长度
     * 
     */
    void Read(int FD, int beginPos, int len);

    /** 
     * 写一个文件
     * @param[in]   FD    文件描述符
     * @param[in]   beginPos    开始位置
     * @param[in]   len 长度
     * @param[in]   s   写的内容
     * 
     */
    void Write(int FD, int beginPos, int len, string s);

    /** 
     * 关闭一个文件
     * @param[in]   FD    文件描述符
     * 
     */
    void Close(int FD);

    /** 
     * 删除一个文件
     * @param[in]   path    需要删除文件的路径
     * 
     */
    void Delete(char* path);
};

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
        exit(1);
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
        OpenFileTable a; a.init(type, file->Pno, ++cnt);
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