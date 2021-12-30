#include <iostream>
#include <map>
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
