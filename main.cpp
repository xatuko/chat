#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char** argv)
{
    cout << "choose your way: \n1 - server\n2 - client" << endl;
    struct sockaddr_in address, serv_addr;
    int server, client, way = 0, opt = 1, new_socket, addlen = sizeof(address);
    char buffer[1024] = {0}, mess[1024] = {'H', 'e', 'l', 'l', 'o'};
    cout << mess;
    cout << endl << "Dlina : " << strlen(mess) << endl;
    cin >> way;
    switch (way)
    {
        case 1:
            server = socket(AF_INET, SOCK_STREAM, 0);
            
            if (server == 0)
            {
                cout << "cannot creat socket";
                return 1;
            }
            
            if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
            {
                perror("setsockport");
                return 1;
            }

            
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            
            address.sin_port = htons(42069);

            cout << "bindim";

            
            if ((bind(server, (sockaddr*)&address, sizeof(address)) < 0))
            {
                perror("bind failed");
                return 1;
            }

            cout << "uspex s bindom";
            
            if (listen(server, 3) < 0)
            {
                perror("listen");
                return 1;
            }

            cout << "uspex s listenom";
            cout << "im here";

            
            new_socket = accept(server, (sockaddr*)&address, (socklen_t*)&addlen);
            if ( new_socket <= 0)
            {
                perror("accept");
                return 1;
            }
            cout << "uspex s connectom";
            cout << recv(new_socket, buffer, sizeof(buffer), MSG_DONTWAIT)  ;
            cout << "Readed: "<< buffer << endl;
            send(new_socket, mess, strlen(mess), 0);
            cout << "message sent" << endl;
            close(server);

            break;
        case 2:
            client = socket(AF_INET, SOCK_STREAM, 0);

            if (client < 0)
            {
                cout << "cannot creat socket";
                return 1;
            }

            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(42069);

            if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
            {
                cout << "beda s adresom";
                return 1;
            }

            if (connect(client, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
            {
                cout << "beda s connectom";
                return 1;
            }
            cout << send(client, mess, sizeof(mess), 0);
            cout << "message sent" << endl;
            cout << "READED: " << buffer << endl;
            close(client);
            break;
        default:
            cout << "wrong number";
            break;
    }
    
    return 0;
}