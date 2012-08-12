#pragma once


DEFINE_BLOCK(b_tcp_socket_source_v4, 0, 4)
{
  SOCKET  ListenSocket;
  SOCKET  ClientSocket;
  BOOL    bConnected;
  
  BLOCK_INIT
  {
    WSADATA wsaData;
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

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, $["port"].c_str(), &hints, &result);
    if ( iResult != 0 ) {
      printf("getaddrinfo failed with error: %d\n", iResult);
      WSACleanup();
      return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
      printf("socket failed with error: %ld\n", WSAGetLastError());
      freeaddrinfo(result);
      WSACleanup();
      return;
    }

    // Setup the TCP listening socket
    iResult = ::bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
      printf("bind failed with error: %d\n", WSAGetLastError());
      freeaddrinfo(result);
      closesocket(ListenSocket);
      WSACleanup();
      return;
    }

    bConnected = false;
  }

  BLOCK_DEINIT
  {
    if (ListenSocket != INVALID_SOCKET) 
    {
      closesocket(ListenSocket);
    }

    if (ClientSocket != INVALID_SOCKET) 
    {
      closesocket(ClientSocket);      
    }
    WSACleanup();
  }

  bool RecvData(uint8 *recvbuf, uint32 recvbuflen)
  {
    int iResult;

    if (!bConnected)
    {
      iResult = listen(ListenSocket, SOMAXCONN);
      if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return false;
      }

      // Accept a client socket
      ClientSocket = accept(ListenSocket, NULL, NULL);
      if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return false;
      }

      bConnected = true;
    }

    iResult = recv(ClientSocket, (char*)recvbuf, recvbuflen, 0);
    if (iResult > 0) 
    {
#if 0
      printf("Received %d bytes.\n", iResult);
      for (int i = 0; i < iResult; i++)
      {
        printf("%02X ", recvbuf[i]);
      }
      printf("\n\n");
#endif
    }
    else if (iResult == 0)
    {
      closesocket(ClientSocket);
      bConnected = false;
      printf("Connection closing...\n");
    }
    else
    {
      printf("recv failed with error: %d\n", WSAGetLastError());
      closesocket(ClientSocket);
      bConnected = false;

      return false;
    }

    return true;
  }
};



DEFINE_BLOCK(b_tcp_socket_sink_4v, 4, 0)
{
  SOCKET  ConnectSocket ;

  BLOCK_INIT
  {
    WSADATA wsaData;
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
    iResult = getaddrinfo($["ip"].c_str(), $["port"].c_str(), &hints, &result);
    if (iResult != 0) {
      printf("getaddrinfo failed: %d\n", iResult);
      WSACleanup();
      return;
    }

    ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

      // Create a SOCKET for connecting to server
      ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
        ptr->ai_protocol);
      if (ConnectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return;
      }

      // Connect to server.
      iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
      if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        continue;
      }
      break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) 
    {
      printf("Error at socket(): %ld\n", WSAGetLastError());
      WSACleanup();
      return;
    }
  }

  BLOCK_DEINIT
  {
    if (ConnectSocket != INVALID_SOCKET) 
    {
      closesocket(ConnectSocket);
      WSACleanup();
    }
  }

  bool SendData(uint8* sendbuf, uint32 sendbuflen)
  {
    int iResult;
    // Send an initial buffer

    iResult = send( ConnectSocket, (char*)sendbuf, sendbuflen, 0 );
    if (iResult == SOCKET_ERROR) 
    {
      printf("send failed with error: %d\n", WSAGetLastError());
      closesocket(ConnectSocket);
      WSACleanup();
      return false;
    }

#if 0
    printf("Sent %d bytes.\n", sendbuflen);
    for (int i = 0; i < sendbuflen; i++)
    {
      printf("%02X ", sendbuf[i]);
    }
    printf("\n\n");
#endif

    return true;
  }
};
