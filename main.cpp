#include <iostream>
#include "connectsock.cpp";

using std::cout;
using std::cin;
using std::endl;

SOCKET

int main() {

    WORD wVersion = 0x0202;
    WSA wsaData;
    int iResult = WSAStartup(wVersion, &wsaData);
    if (iResult != 0) {
        cout << "Unable to initialize Windows Socket library." << endl;
    }

    char host[MAXNAME];
    cout << "Which ECHO server? ";
    cin >> host;

    char service[MAXNAME];
    cout << "Which service name or port number? ";
    cin >> service;


    SOCKET s = connectsock("si", "echo", "tcp");
    if (s != INVALID_SOCKET) {
        cout << "TCP connection established!" << endl << endl;

        char message[MAXBUF];
        cin.ignore();
        cout << "Message to send?";
        cin.getline(message, MAXBUF - 1);

        int numberOfBytesSent = send(s, message, strlen(message), 0);

        if (numberOfBytesSent > 0) {
            cout << "Number of bytes actually sent = " << numberOfBytesSent << endl;
            cout << endl;
        } else {
            cout << "Unable to send message to remote server." << endl << endl;
            return 0;
        }

        char recievedBuffer[MAXBUF];
        int numberOfBytesReceived = recv(s, recievedBuffer, MAXBUF - 1, 0);
        if (numberOfBytesReceived > 0) {
            cout << "Received Message: ";
            recievedBuffer[numberOfBytesReceived] = '\0';
            cout << recievedBuffer << endl;
            cout << "Number of bytes received: " << numberOfBytesReceived << endl << endl;
        }
        closesocket(s);
    }

    WSACleanup();

    return 0;
}
