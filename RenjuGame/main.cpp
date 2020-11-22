/*
  Name: RenjuGame.dev
  Description: 五子连珠游戏
  Author: 19301050-wumengning
  Date: 29-06-20 13:00
*/

#include "GUI_display.h"
#include "global.h"
#include "model.h"

int main() { // 主函数
	int board[15][15] = { 0 }; // 创建棋盘并初始化
	initgraph(800, 600); // 初始化图形界面大小
	displayMenu(board); // 菜单
	closegraph(); //关闭绘图窗口
	return 0;
}