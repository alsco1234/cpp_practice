#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>
#include "server.h"

#define BUFSIZE 1024

using namespace std;

Server::Server(int port) {
    int serv_sock;
    struct sockaddr_in serv_addr;
    int str_len;
    struct timeval timeout;
    fd_set reads, temps;
    char nicknames[10][BUFSIZE] = {'\0'}; //최대 10명의 닉네임 저장
    char all_nicknames[BUFSIZE*10] = "현재 참여자 : ";
    char send_message[BUFSIZE] = "";
    int fd_max;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        error_handling("socket() error");
    }

    // server의 주소 만들기
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    // socket 에러 출력하기
    if (::bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }

    // server의 에러 출력하기
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    // select를 위한 FD_SET 만들기
    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;

    connect_to_client(serv_sock, reads, fd_max, nicknames, all_nicknames, send_message);
}

void Server::error_handling(const char* msg) {
    cerr << msg << endl;
    exit(1);
}

void Server::connect_to_client(int serv_sock, fd_set reads, int& fd_max, char nicknames[][BUFSIZE], char* all_nicknames, char* send_message){
    char message[BUFSIZE];
    struct timeval timeout;

    while (1) {
        int fd, str_len;
        int clnt_sock, clnt_len;
        struct sockaddr_in clnt_addr;

        fd_set temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // select 에러 출력하기
        if (select(fd_max + 1, &temps, 0, 0, &timeout) == -1) {
            error_handling("select() error");
        }

        for (fd = 0; fd < fd_max+1; fd++){
            message[0] = '\0';
            // 5-1. FD_ISSET이 true인경우
            if (FD_ISSET(fd, &temps)){
                // 1) fd가 serv_sock이다 => 클라이언트가 연결 받았다
                if (fd == serv_sock) { /* connect request from a client*/
                    clnt_len = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, (socklen_t *)&clnt_len);
                    FD_SET(clnt_sock, &reads);
                    // 이때 새 client 발견했다면
                    if (fd_max < clnt_sock)
                        fd_max=clnt_sock;
                }
                // 2) fd가 serv_sock이 아니다 => 클라이언트가 메세지 보낸다
                else {
                    message[0] = '\0';
                    str_len = read(fd, message, BUFSIZE);
                    if(str_len == -1){
                        // 에러 발생 시 해당 소켓을 집합에서 제거
                        FD_CLR(fd, &reads);
                        error_handling("read() error");
                    }
                    message[str_len] = '\0' ;

                    // 2-1) len이 0이다 => 연결이 끊어졌다
                    if(str_len == 0) { /* connection close */
                        FD_CLR(fd, &reads);
                        close(fd);

                        send_message[0] = '\0';
                        strcat(send_message, nicknames[fd]);
                        strcat(send_message, " (이)가 채팅방을 떠났습니다.\n");
                        printf("%s", send_message);
                        //모두에게 출력
                        for (fd = 0; fd < fd_max+1; fd++){
                            if (strcmp(nicknames[fd], "") != 0) {
                                write (fd, send_message, BUFSIZE);
                            }
                        }
                        // 2-2) len이 0이 아니다 => 메세지 보냈다
                    } else {
                        //아직 닉네임이 설정되지 않음 (닉네임이 옴)
                        if (strcmp(nicknames[fd], "") == 0) {
                            strcpy(nicknames[fd], message);
                            strcat(all_nicknames, nicknames[fd]);
                            strcat(all_nicknames, " ");
                            write(fd, all_nicknames, BUFSIZE);

                            send_message[0] = '\0';
                            strcat(send_message, nicknames[fd]);
                            strcat(send_message, " (이)가 채팅방에 들어왔습니다.\n");
                            printf("%s", send_message);
                            //모두에게 출력
                            for (fd = 0; fd < fd_max+1; fd++){
                                if (strcmp(nicknames[fd], "") != 0) {
                                    write (fd, send_message, BUFSIZE);
                                }
                            }
                        }
                        //닉네임이 설정되고 또 옴 (메세지가 옴)
                        else{
                            send_message[0] = '\0';
                            strcpy(send_message, "");
                            strcat(send_message, "[");
                            strcat(send_message, nicknames[fd]);
                            strcat(send_message, "] : ");
                            strcat(send_message, message);
                            printf("%s", send_message);
                            //모두에게 출력
                            for (fd = 0; fd < fd_max+1; fd++){
                                if (strcmp(nicknames[fd], "") != 0) {
                                    write (fd, send_message, BUFSIZE);
                                }
                            }
                        }
                    }
                }
            } //if(FD_ISSET(fd, &temps))
        } //for(fd=0; fd<fd_max+1; fd++)
    } //while(1)
}