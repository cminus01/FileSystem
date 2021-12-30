#include "utils.cpp"
#include <map>
int state;
class User
{
private:
    std::string name, password;
public:
    void logout()
    {
        state = 0;
    }
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