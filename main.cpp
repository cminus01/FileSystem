#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include "Manager.hpp"

Manager manager;
int main() 
{
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
            }
        }
        else
        {
            user[state].show();
            
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
               // ShowUsage();
            }
            else
            {
                manager.Command(s);
            }
        }
    }
    return 0;
}