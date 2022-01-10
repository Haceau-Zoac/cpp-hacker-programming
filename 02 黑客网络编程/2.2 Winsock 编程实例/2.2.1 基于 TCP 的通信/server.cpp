#include <cstdio>
#include <cstring>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

int main() {
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  SOCKET server{ socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) };

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.S_un.S_addr = inet_addr("10.10.30.12");
  addr.sin_port = htons(1234);

  bind(server, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr));

  listen(server, SOMAXCONN);

  sockaddr_in clientAddr;
  int size{ sizeof(clientAddr) };

  SOCKET client{ accept(server, reinterpret_cast<SOCKADDR*>(&clientAddr), &size) };

  std::printf("Client IP: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

  char message[MAXBYTE]{};
  lstrcpyA(message, "hello Client!\n");
  send(client, message, std::strlen(message) + sizeof(char), 0);

  recv(client, message, MAXBYTE, 0);
  printf("Client Message: %s\n", message);

  closesocket(server);
  closesocket(client);

  WSACleanup();
}