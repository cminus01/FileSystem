#include "FileAccess.hpp"
#include "User.hpp"
using namespace std;

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
