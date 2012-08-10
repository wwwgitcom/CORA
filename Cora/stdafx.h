// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <map>

using namespace std;
// TODO: reference additional headers your program requires here

//The WIN32_LEAN_AND_MEAN macro prevents the Winsock.h from being included by the Windows.h header.
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif

#include "_windows.h"

#include <Strsafe.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")



#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")



#include <ppl.h>
#include <array>

using namespace Concurrency;

