/**
 * Jerred Shepherd
 * 1-31-18
 * myEcho client for Networking
 */
#include <iostream>
#include <winsock2.h>
#include "connectsock.cpp"
using namespace std;
#pragma comment (lib, "ws2_32.lib")

#define MAXBUF  4096
#define MAXNAME 80

// Utility socket function
SOCKET passivesock (char*,char*);

int main() {

    WORD wVersion = 0x0202;
    WSADATA wsaData;
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

    SOCKET s = connectsock(host, service, "tcp");
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

        char receivedBuffer[MAXBUF];
        int numberOfBytesReceived = recv(s, receivedBuffer, MAXBUF - 1, 0);
        if (numberOfBytesReceived > 0) {
            cout << "Received Message: ";
            receivedBuffer[numberOfBytesReceived] = '\0';
            cout << receivedBuffer << endl;
            cout << "Number of bytes received: " << numberOfBytesReceived << endl << endl;
        } else {
            cout << "Nothing received" << endl << endl;
        }
        closesocket(s);
    }

    WSACleanup();

    return 0;
}
