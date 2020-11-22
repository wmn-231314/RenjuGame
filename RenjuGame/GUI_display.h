#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "global.h"

 // 界面显示相关函数

void displayMenu(int board[15][15]); // 显示菜单
void disStart(int board[15][15]); // 显示双人棋局
void disAbout(); // 显示关于
void disRules(); // 显示规则
void disSave(char name[100]); // 显示保存界面
void disManMashine(int board[15][15]); // 显示人机棋局
void disWinner(int rank,char name[],int turn); // 显示排名
void disChess(int line,int row,int bw); // 显示棋子在棋盘上
int disReviewQue(char name[100]); // 回顾棋局显示搜索界面
void disChar(int board[15][15]); // 显示角色选择界面
int disConQue(); // 显示是否继续棋局
void disHint(int bw);// 显示轮次提示
void disReady(); // 显示擂台准备动画
void disSetImg(int but1, int but2); // 显示设置图片
void disSet(int* but1, int* but2); // 设置

#endif // !_DISPLAY_H

