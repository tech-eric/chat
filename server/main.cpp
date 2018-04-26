#include  <iostream>
#include  <sys/socket.h>
#include  <arpa/inet.h>
#include  <string.h>
#include  <netinet/in.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <signal.h>

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

    int conn;
    int thread_cnt = 0;

    cout << "Wating for conneting"<< endl;

    signal(SIGCLD, SIG_IGN);

    while(1){

        /* Wating for client conneting */
        conn = accept(socket_d, (struct sockaddr *)&client_addr, &address_size);
        thread_cnt++;

        /* Fork a new thread to receive msg */
        if(fork() == 0){
            char *msg = new char[100];
            int cnt;

            cout << "Thread " << thread_cnt <<": Establish a connecion" << endl;

            while(1){
                cnt = recv(conn, msg, 1000, 0);
                if(cnt <= 0){
                    cout << "Thread " << thread_cnt << ": Thread exit" << endl;
                    break;
                }
                msg[cnt] = '\0';
                cout << "Thread " << thread_cnt << ": Receive Msg:" << msg << endl;
            }

            close(conn);
            delete(msg);
            exit(0);
        }
    }

    close(socket_d);
    cout << "Exit"<< endl;

    return 0;
}
