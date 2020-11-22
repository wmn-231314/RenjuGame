#include "game_service.h"


int judgeLine(int turn,int board[15][15]) { // 判横线输赢
	int i, j, count; // 声明变量
	int line, result = 0;
	int bw = turn % 2; // 判断轮次
	for (i = 0; i < 15; i++) {
		for (j = 0; j <= 10; j++) { // 遍历所有位置
			count = 0;
			if (bw) { // 判断黑棋是否胜利
				line = j;
				while (board[i][line] == BLACK_CHESS) {
					count++;
					line++;
					if (count >= 5) {
						result = 1; // 胜利
						break;
					}
				}
				j = line;
			}
			else { // 判断白棋是否胜利
				line = j;
				while (board[i][line] == WHITE_CHESS) {
					count++;
					line++;
					if (count >= 5) {
						result = 1; // 胜利
						break;
					}
				}
				j = line;
			}
			if (result) {
				return result; // 返回结果值
			}
		}
	}
	return result; // 返回判断结果
}

int judgeRow(int turn,int board[15][15]) { // 判竖线输赢
	int i, j, count; // 声明变量
	int row, result = 0;
	int bw = turn % 2; // 判断轮次
	for (i = 0; i < 15; i++) {
		for (j = 0; j <= 10; j++) { // 遍历所有位置
			count = 0;
			if (bw) { // 若为黑棋
				row = j;
				while (board[row][i] == BLACK_CHESS) {
					count++;
					row++;
					if (count >= 5) { // 判断五子连成线
						result = 1;
						break;
					}
				}
				j = row;
			}
			else { // 若为白棋
				row = j;
				while (board[row][i] == WHITE_CHESS) {
					count++;
					row++;
					if (count >= 5) { // 判断五子连成线
						result = 1;
						break;
					}
				}
				j = row;
			}
			if (result) { // 返回结果值
				return result;
			}
		}
	}
	return result; // 返回结果值
}

int judgeSlantR(int turn,int board[15][15]) { // 判右斜线输赢
	int i, j, count; // 声明变量
	int line, row, result = 0;
	int bw = turn % 2; // 判断轮次
	for (i = 0; i <= 10; i++) {
		for (j = 0; j <= 10; j++) { // 遍历所有位置
			count = 0;
			if (bw) { // 若为黑棋
				line = i;
				row = j;
				while (board[line][row] == BLACK_CHESS) {
					count++;
					line++;
					row++;
					if (count >= 5) { // 判断五子连成线
						result = 1;
						break;
					}
				}
			}
			else { // 若为白棋
				line = i;
				row = j;
				while (board[line][row] == WHITE_CHESS) {
					count++;
					line++;
					row++;
					if (count >= 5) { // 判断五子连成线
						result = 1;
						break;
					}
				}
			}
			if (result) { // 返回结果值
				return result;
			}
		}
	}
	return result; // 返回结果值
}

int judgeSlantL(int turn,int board[15][15]) { // 判左斜线输赢
	int i, j, count; // 声明变量
	int line, row, result = 0;
	int bw = turn % 2; // 判断轮次
	for (i = 0; i <= 10; i++) {
		for (j = 4; j < 15; j++) {
			count = 0;
			if (bw) { // 若为黑棋
				line = i;
				row = j;
				while (board[line][row] == BLACK_CHESS) {
					count++;
					line++;
					row--;
					if (count >= 5) { // 五子连成线
						result = 1;
						break;
					}
				}
			}
			else { // 若为白子
				line = i;
				row = j;
				while (board[line][row] == WHITE_CHESS) {
					count++;
					line++;
					row--;
					if (count >= 5) { // 判断五子连成线
						result = 1;
						break;
					}
				}
			}
			if (result) { // 返回结果值
				return result;
			}
		}
	}
	return result; // 返回结果值
}

int maxStatus(int a, int b, int c, int d, int e) { // 判断当前棋盘状态
	int M = a;
	if (M < b) {
		M = b;
	}
	if (M < c) {
		M = c;
	}
	if (M < d) {
		M = d;
	}
	if (M < e) {
		M = e;
	}
	return M; // 返回最大值
}

int drawGame(int board[15][15]) { // 判平局
	int i, j;
	int draw = 2;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) { // 遍历所有位置
			if (board[i][j] == BLANK) {
				draw = 0;
				break;
			}
		}
	}
	return draw; // 返回结果值
}