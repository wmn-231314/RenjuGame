#ifndef _GLOBAL_H
#define _GLOBAL_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "Winmm.lib")

enum Status { // Æå×Ó
	BLACK_CHESS = 1,
	WHITE_CHESS = -1,
	BLANK = 0
};

#endif // !_GLOBAL_H