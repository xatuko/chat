#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

int main()
{
    cout << "choose your way: \n1 - server\n2 - client" << endl;
    int server, way = 0;
    cin >> way;
    switch (way)
    {
        case 1:
            cout << "your IP is: " << "<smth>" << "\nshare it with your friend";
            server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (server < 0)
            {
                cout << "cannot creat socket";
                return 1;
            }
            cout << "lets go" << endl;

            break;
        case 2:
            cout << "specify server ip: " << endl;

            break;
        default:
            cout << "wrong number";
            break;
    }
    
    return 0;
}