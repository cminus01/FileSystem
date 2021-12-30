#include <cstdio>
#include <cstring>
#include "Manager.hpp"

Manager manager;
int main() 
{
    while (true)
    {
        if (user.state == 0) 
        {
            printf("login: ");
            char s[1024];
            scanf("%s", s);
            user.login(s);
        }
        else
        {
            user.show();
            char s[1024];
            scanf("[^#]%s", s);
            if (strcmp(s, "logout") == 0)
            {
                user.logout();
            }
            else if (strcmp(s, "exit") == 0)
            {
                break;
            }
            else if (strcmp(s, "Usage") == 0)
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