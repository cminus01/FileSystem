#include "FileDir_lz.cpp"

int cnt; //fd的序号
struct OpenFileTable {
    int fd; //文件描述符
    int Pno; //文件编号
    int type; //打开方式
    OpenFileTable(int t, int pno)
    {
        type = t;
        fd = ++cnt;
        Pno = pno;
    }
};
std::map <int, OpenFileTable> Fd2Table; //记录文件编号到文件打开表的映射

int opensize = 5; //最大打开文件数量

class Manager {
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