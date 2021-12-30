#include "FileAccess.hpp"
using namespace std;

int state; //用户
string now; //当前目录
struct FCB
{
    int Pno; // 此目录里面的编号
    int size; // 大小
    string name; //用户中文件名
    string use_name; //用户
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
    // cd
    void Goto(string name){
        if(name == "home"){
            now = "";
        }
        else now = name;
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
    void Create(char *path,int pos,int maxLength){
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




int main(){
    return 0;
}