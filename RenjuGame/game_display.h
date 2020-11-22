#ifndef _GAME_DISPLAY_H
#define _GAME_DISPLAY_H

#include "model.h"
#include "global.h"

 // 游戏显示相关函数

void startGame(int board[15][15]); // 开始双人游戏
void manMashine(int board[15][15]); // 开始人机游戏
void rankList(); // 加载并输出排名
void displayWinerB(Winer* win,int board[15][15]); // 读取并输出回顾棋局
void startWebGame(SOCKET *newC,int board[15][15],int status); // 开始网络对战


#endif // !_GAME_DISPLAY_H

