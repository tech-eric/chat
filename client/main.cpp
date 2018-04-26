#include  <iostream>
#include  <sys/socket.h>
#include  <arpa/inet.h>
#include  <string.h>
#include  <netinet/in.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
    char buf[1000] = {"Hello Server"};
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

    if(connect(socket_d, (struct sockaddr *)&name, sizeof(name)) < 0){
        cout <<"connet faild" << endl;
    }else{
        cout << "Connect succefully" << endl;
        send(socket_d, buf, strlen(buf), 0);
    }

    cout << "Exit"<< endl;

    return 0;
}
