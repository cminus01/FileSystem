struct FCB
{
    int Pno;
    int size;
    string name;
    string use_name;
    string address;
};

struct UFDnode{
    int size;
    FCB fcb[10];
};

struct MFD{
    int size;
    UFDnode Main[10];
}mfd; 

class FileDirectory {
public:

    // 是否合法
    bool check(char* name){
        string s;int len = strlen(name);
        for(int i = 0;i < len; ++i){
            if(name[i] == '\\') ok = 1,continue;
            if(ok == 1) s += name[i]; 
        }
        if(ok == 1 && !s.empyt()){ return true;
        }
        else return false;
    }

    // 判重
    bool check_double(char *name,int no){
        //bool ok = 0;
        int num = 0;
        for(int i = 0;i < mfd.Main[no].size; ++i){
            if(strcmp(mfd.Main[no].fbb[i],name) == 0){
                ++num;
            }
        }if(num > 1) return true;return false;
    }

    // ls
    void show_all(int no){ //用户名编号
        for(int i = 0;i < mfd.Main[no].size; ++i){
            cout << mfd.Main[no].pcb[i].name << " ";
        }
        cout << endl;
    }

    //通过文件的Pno去找其FCB
    FCB* OpenFile(int fd){
        for(int i = 0;i < mfd.size; ++i){
            for(int j = 0;j < mfd.Main[i].size; ++j){
                if(mfd.Main[i].fcb[j].Pno == fd){
                    return *mfd.Main[i].fcb[j];
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
        bool ok = 0;
        for(int i = 0;i < len; ++i){
            if(path[i] == '\\') ok = 1;
            if(ok == 0){use_name += path[i];}
            else {name += path[i];}
        }
        for(int i = 0;i < mfd.size; ++i){
            for(int j = 0;j < mfs.Main[i].size; ++j){
                if(mfd.Main[i].fcb[j].name == name && mfd.Main[i].fcb[j].use_name == use_name){
                    return *mfd.Main[i].fcb[j];
                }
            }
        }
    }
}