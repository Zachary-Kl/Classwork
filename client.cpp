// To compile
// Server: g++ server.cpp -o server.exe -lws2_32
// Client: g++ client.cpp -o client.exe -lws2_32

// To Run
// 1. Start the Server first: ./server.exe
// 2. Open the new terminal and run the client
// 3. Start the client: ./client.exe

#include <iostream>
#include <string>
#include <winsock2.h> 
#include <ws2tcpip.h> 
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Winsock initialization failed" << std::endl;
        return 1;
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        std::cout << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8080);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
    {
        std::cout << "Connection Failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    std::string abbrev;
    std::cout << "Enter Abbrevatition for the State: ";
    std::cin >> abbrev;

    // 5. Send raw data and receive the sum
    send(sock, abbrev.c_str(), abbrev.size(), 0);
    char buffer[1024] = {0};
    int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
    std::string fullname = buffer;
    std::cout << "The Server returned the State Name: " << fullname << std::endl;

    closesocket(sock);
    WSACleanup();
    return 0;
}