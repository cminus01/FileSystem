#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include "Manager.hpp"

void init()
{
    user[0].init("admin", "11111");
    user[1].init("user2", "67290");
    user[2].init("user3", "123456");
    user[3].init("user4", "567890");
    user[4].init("user5", "1234567");
    user[5].init("user6", "4567890");
    user[6].init("user7", "1234");
    user[7].init("user8", "5678");
    user[8].init("user9", "7890");
    user[9].init("user10", "4567");
    for (int i = 0; i <= 9; i++)
        mp[user[i].name] = i; 
}

void ShowUsage()
{

}

Manager manager;
int main() 
{
    init();
    while (true)
    {
        if (state == 0) 
        {
            printf("login: ");
            char s[1024];
            scanf("%s", s);
            if (user[mp[s]].login())
            {
                state = mp[s];
                now = s;
            }
        }
        else
        {
            user[state].show();
            if (now == "")
            {
                cout << "/$";
                cout.flush();
            }
            else
            {
                cout << "/" << now << "$";
                cout.flush();
            }
            std::string s;
            std::cin >> s;
            if (s == "logout")
            {
                user[state].logout();
            }
            else if (s == "exit")
            {
                break;
            }
            else if (s == "Usage")
            {
               ShowUsage();
            }
            else
            {
                manager.Command(s);
            }
        }
    }
    return 0;
}