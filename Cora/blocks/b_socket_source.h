#pragma once


DEFINE_BLOCK(b_tcp_socket_source_v4, 0, 4)
{
  SOCKET  ConnectSocket ;
  WSADATA wsaData;

  #define DEFAULT_PORT "27015"

  BLOCK_INIT
  {
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
      printf("WSAStartup failed: %d\n", iResult);
      return;
    }

    struct addrinfo *result = NULL,
      *ptr = NULL,
      hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo($["ip"], $["port"], &hints, &result);
    if (iResult != 0) {
      printf("getaddrinfo failed: %d\n", iResult);
      WSACleanup();
      return;
    }

    ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
      ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET) {
      printf("Error at socket(): %ld\n", WSAGetLastError());
      freeaddrinfo(result);
      WSACleanup();
      return;
    }
  }
};