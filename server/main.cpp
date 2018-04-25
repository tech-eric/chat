#include  <iostream>
#include  <sys/socket.h>
#include  <arpa/inet.h>
#include  <string.h>
#include  <netinet/in.h>
#include  <stdio.h>
#include  <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
    // Create socket
    int socket_d = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_d == -1){
        cout << "Socket create fail" << endl;
    }

    //Bind to port
    struct  sockaddr_in name;

    memset(&name, 0, sizeof(name));

    name.sin_family = AF_INET;
    name.sin_port = htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    int c = bind(socket_d, (struct sockaddr *)&name, sizeof(name));
    if(c == -1){
        cout << "Bind port fail" << endl;
    }

    //Listening client connet
    if(listen(socket_d, 10) == -1){
        cout << "Listenin start fial" <<endl;
    }

    //Wating for connet
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);

    int connet_d = accept(socket_d, (struct sockaddr *)&client_addr, &address_size);
    if(connet_d == -1){
        cout << "Accept client fail" <<endl;
    }else{
        cout << "Accepted a client succefully" << endl;
    }

    cout << "Exit"<< endl;

    return 0;
}
