## 基于两级目录结构的简单文件系统的管理与操作

### 问题描述

​		为了模拟文件系统实现的基本功能，了解文件系统的基本结构和文件的各种管理方法，加深理解文件系统的内部功能及内部实现，理解文件管理的工作过程，加深各种文件操作命令的实质内容和执行过程的了解，现要求编程模拟一个简单的文件系统，以实现对文件系统的管理和控制功能，支持用户对自己文件的管理与操作。

### 具体要求

- 要求本文件系统采用两级目录，即设置主文件目录[MFD]和用户文件目录[UED]。在主文件目录中，每个用户目录都占有一个目录项，其目录项中包含文件名和指向该文件目录文件。在用户文件目录UFD中，这些文件目录具有相似的结构，它由用户文件的文件块组成。另外，可考虑为打开文件设置运行文件目录[AFD]。具体测试时可考虑：设计一个10个用户的文件系统，每次用户可保存10个文件，一次运行用户可以打开5个文件，并需要对文件设置保护措施。
- 设计并实现Create、Open、Read、Write、Close、Delete等文件命令的算法，以实现用户通过菜单方式或者API方式实现对自己文件的管理。

### 设计方案

#### 数据结构

+ FCB

  ```c++
  struct FCB {
      int Pno; // 此目录里面的编号
      int size; // 大小
      string name; //用户中文件名
      string use_name; //用户
      int address; // 地址
  };
  ```

+ 文件目录结构

  ```c++
  struct UFDnode{ // 用户文件目录
      string use_name; //用户名
      int size;//用户文件大小
      FCB fcb[10];
  };
  struct MFD{ //用户目录
      int size;//用户大小
      UFDnode Main[10];
  }mfd; 
  ```

+ 运行文件目录

  ```c++
  struct OpenFileTable {
      int fd; //文件描述符
      int Pno; //文件编号
      int type; //打开方式
  };
  ```

#### 模块划分

##### User模块

负责用户的登录部分 

+ 账户、密码正确性检测
+ 修改与当前登入用户相关的信息

```c++
class User {
    bool login(); // 返回是否登陆成功
    void logout(); // 登出
};
```



##### FileDirectory模块

文件目录部分

```c++
class FileDirectory {
public:
    bool Check(char *path);
    FCB* FindPos(char* path, char* state);
}
```



##### FileAccess模块

文件存储管理部分

```c++

```



##### Manager模块

实现用户命令的模块

包括下面几个API

```c++
class Manager {
public:
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
```











