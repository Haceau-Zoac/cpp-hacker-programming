#include <cstdio>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

int main() {
  WSAData wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  SOCKET client{ socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) };
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.S_un.S_addr = inet_addr("10.10.30.12");
  addr.sin_port = htons(1234);
  
  connect(client, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr));

  char message[MAXBYTE]{};
  recv(client, message, MAXBYTE, 0);
  std::printf("Server Message:%s", message);

  lstrcpyA(message, "hello Server!\n");
  send(client, message, sizeof(message) + sizeof(char), 0);

  closesocket(client);
  WSACleanup();
}