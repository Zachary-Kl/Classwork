// To compile
// Server: g++ server.cpp -o server.exe -lws2_32
// Client: g++ client.cpp -o client.exe -lws2_32

// To Run
// 1. Start the Server first: ./server.exe
// 2. Open the new terminal and run the client
// 3. Start the client: ./client.exe

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }
    SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servSock == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return -1;
    }
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY; // Listen on all network cards
    servAddr.sin_port = htons(8080);
    if (bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed" << std::endl;
        closesocket(servSock);
        WSACleanup();
        return -1;
    }
    if (listen(servSock, 5) == SOCKET_ERROR)
    {
        std::cerr << "Listen failed" << std::endl;
        closesocket(servSock);
        WSACleanup();
        return -1;
    }

    std::cout << "Server is running and waiting for numbers on port 8080..." << std::endl;

    while (true)
    {
            SOCKET clntSock = accept(servSock, nullptr, nullptr);
            if (clntSock == INVALID_SOCKET)
                continue;
            char buffer[1024] = {0};
            int bytesReceived = recv(clntSock, buffer, sizeof(buffer), 0);

            if (bytesReceived > 0)
            {
                std::cout << "Received: " << buffer << std::endl;
                std::string abreviation = buffer;
                std::string fullstate;
                if(abreviation.length() == 2){
                    std::cout << "Length Correct" << std::endl;
                    if(abreviation == "AL"){
                        fullstate = "Alabama";
                    }
                    else if(abreviation == "AK"){
                        fullstate = "Alaska";
                    }
                    else if(abreviation == "AZ"){
                        fullstate = "Arizona";
                    }
                    else if(abreviation == "AR"){
                        fullstate = "Arkansas";
                    }
                    else if(abreviation == "CA"){
                        fullstate = "California";
                    }
                    else if(abreviation == "CO"){
                        fullstate = "Colorado";
                    }
                    else if(abreviation == "CT"){
                        fullstate = "Connecticut";
                    }
                    else if(abreviation == "DE"){
                        fullstate = "Delaware";
                    }
                    else if(abreviation == "FL"){
                        fullstate = "Florida";
                    }
                    else if(abreviation == "GA"){
                        fullstate = "Georgia";
                    }
                    else if(abreviation == "HI"){
                        fullstate = "Hawaii";
                    }
                    else if(abreviation == "ID"){
                        fullstate = "Idaho";
                    }
                    else if(abreviation == "IL"){
                        fullstate = "Illinois";
                    }
                    else if(abreviation == "IN"){
                        fullstate = "Indiana";
                    }
                    else if(abreviation == "IA"){
                        fullstate = "Iowa";
                    }
                    else if(abreviation == "KS"){
                        fullstate = "Kansas";
                    }
                    else if(abreviation == "KY"){
                        fullstate = "Kentucky";
                    }
                    else if(abreviation == "LA"){
                        fullstate = "Louisiana";
                    }
                    else if(abreviation == "MA"){
                        fullstate = "Maine";
                    }
                    else if(abreviation == "MD"){
                        fullstate = "Maryland";
                    }
                    else if(abreviation == "MA"){
                        fullstate = "Massachusetts";
                    }
                    else if(abreviation == "MI"){
                        fullstate = "Michigan";
                    }
                    else if(abreviation == "MN"){
                        fullstate = "Minnesota";
                    }
                    else if(abreviation == "MS"){
                        fullstate = "Mississippi";
                    }
                    else if(abreviation == "MO"){
                        fullstate = "Missouri";
                    }
                    else if(abreviation == "MT"){
                        fullstate = "Montana";
                    }
                    else if(abreviation == "NE"){
                        fullstate = "Nebraska";
                    }
                    else if(abreviation == "NV"){
                        fullstate = "Nevada";
                    }
                    else if(abreviation == "NH"){
                        fullstate = "New Hampshire";
                    }
                    else if(abreviation == "NJ"){
                        fullstate = "New Jersey";
                    }
                    else if(abreviation == "NM"){
                        fullstate = "New Mexico";
                    }
                    else if(abreviation == "NY"){
                        fullstate = "New York";
                    }
                    else if(abreviation == "NC"){
                        fullstate = "North Carolina";
                    }
                    else if(abreviation == "ND"){
                        fullstate = "North Dakota";
                    }
                    else if(abreviation == "OH"){
                        fullstate = "Ohio";
                    }
                    else if(abreviation == "OK"){
                        fullstate = "Oklahoma";
                    }
                    else if(abreviation == "OR"){
                        fullstate = "Oregon";
                    }
                    else if(abreviation == "PA"){
                        fullstate = "Pennsylvania";
                    }
                    else if(abreviation == "RI"){
                        fullstate = "Rhode Island";
                    }
                    else if(abreviation == "SC"){
                        fullstate = "South Carolina";
                    }
                    else if(abreviation == "SD"){
                        fullstate = "South Dakota";
                    }
                    else if(abreviation == "TN"){
                        fullstate = "Tennessee";
                    }
                    else if(abreviation == "TX"){
                        fullstate = "Texas";
                    }
                    else if(abreviation == "UT"){
                        fullstate = "Utah";
                    }
                    else if(abreviation == "VT"){
                        fullstate = "Vermont";
                    }
                    else if(abreviation == "VA"){
                        fullstate = "Virginia";
                    }
                    else if(abreviation == "WA"){
                        fullstate = "Washington";
                    }
                    else if(abreviation == "WV"){
                        fullstate = "West Virginia";
                    }
                    else if(abreviation == "WI"){
                        fullstate = "Wisconsin";
                    }
                    else if(abreviation == "WY"){
                        fullstate = "Wyoming";
                    }
                    else {
                        fullstate = "No State Matches Your Input";
                    }                    
                }
                else{
                    fullstate = "Must be two characters long";
                }
                std::cout << fullstate << std::endl;

                send(clntSock, fullstate.c_str(), fullstate.size(), 0);
            }

            closesocket(clntSock);
    }


    closesocket(servSock);
    WSACleanup();
    return 0;
}