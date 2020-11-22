#ifndef _MAN_H
#define _MAN_H

#include "model.h"
#include "global.h"

 // 人机对战逻辑相关函数

void findPos(int board[15][15],int pos[15][15]); // 找到棋盘存在的棋子
Chess* maxScore(int score[15][15]); // 计算当前棋盘状态的最大分数
void nextScore(int pos[15][15], int score[15][15],int board[15][15]); // 计算每个pos下一步的得分
int calScore(int different, int same, int blank); // 不同状态的分值设定
int scanLine(int l, int r, int status, int board[15][15]); // 计算当前横线分值
int scanRow(int l, int r, int status, int board[15][15]); // 计算当前竖线分值
int scanSlantR(int l, int r, int status, int board[15][15]); // 计算当前右斜线分值
int scanSlantL(int l, int r, int status, int board[15][15]); // 计算当前左斜线分值
void checkPos(int line, int row, int board[15][15], int pos[15][15]); // 找到棋子周围的空位pos

#endif // !_MAN_H
