#ifndef _GAME_SERVICE_H
#define _GAME_SERVICE_H

#include "global.h"
#include "model.h"

 // 游戏逻辑和输赢判断相关函数

int judgeLine(int turn, int board[15][15]); // 判断横线胜负
int judgeRow(int turn, int board[15][15]); // 判断竖线胜负
int judgeSlantR(int turn, int board[15][15]); // 判断右斜线胜负
int judgeSlantL(int turn, int board[15][15]); // 判断左斜线胜负
int maxStatus(int, int, int, int, int); // 判断目前棋局状态
int drawGame(int board[15][15]); // 判断平局


#endif // !_GAME_SERVICE_H
