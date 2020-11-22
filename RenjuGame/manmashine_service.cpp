#include "manmashine_service.h"
#include "data.h"

void findPos(int board[15][15],int position[15][15]) { // 找存在棋盘的棋子
	initial(position); // 初始化位置的二维数组
	int i, j;
	for (i = 0; i < 15; i++) { // 遍历棋盘
		for (j = 0; j < 15; j++) {
			if (board[i][j] != BLANK) {
				checkPos(i, j,board,position); // 找到棋子周围空位
			}
		}
	}
}

Chess* maxScore(int score[15][15]) { // 分数最大值
	int i, j,same = 0; // 声明变量
	int random = 0,find = 0;
	int max = score[0][0];
	Chess* maxpos;
	maxpos = (Chess*)malloc(sizeof(Chess)); // 分配内存
	maxpos->line = 0;
	maxpos->row = 0;
	for (i = 0; i < 15; i++) { // 遍历
		for (j = 0; j < 15; j++) {
			if (score[i][j] > max) { // 找到最大值
				same = 1;
				max = score[i][j];
				maxpos->line = i;
				maxpos->row = j;
			}
			else if (score[i][j] == max) {
				same++; // 计算有几个相同的最大值
			}
		}
	}
	if (same > 1) { // 超过一个时
		srand((unsigned)time(NULL)); // 随机选择一个
		random = rand()%same;
		for (i = 0; i < 15; i++) { // 遍历
			for (j = 0; j < 15; j++) {
				if (score[i][j] == max) { // 找到最大值
					if (random == 0) {
						find = 1;
						maxpos->line = i;
						maxpos->row = j;
						break;
					}
					random--;
				}
			}
			if (find) { // 找到选择的那个最大值
				break;
			}
		}
	}
	return maxpos; // 返回最大值的结构体指针
}

void nextScore(int position[15][15],int score[15][15],int board[15][15]) { // 计算每个pos下一步的得分
	int i, j; // 声明变量
	initial(score); // 初始化分数的二维数组
	int score1, score2, score3, score4, totals; // 机器的4项分数
	int scorem1, scorem2, scorem3, scorem4, totalsm; // 人的4项分数
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) { // 遍历数组
			if (position[i][j] == 1) { // 找到棋子周围空位
				score1 = scanLine(i, j, WHITE_CHESS,board); // 计算各项分数
				score2 = scanRow(i, j, WHITE_CHESS,board);
				score3 = scanSlantR(i, j, WHITE_CHESS,board);
				score4 = scanSlantL(i, j, WHITE_CHESS,board);
				totals = score1 + score2 + score3 + score4; // 机器得分
				scorem1 = scanLine(i, j, BLACK_CHESS,board);
				scorem2 = scanRow(i, j, BLACK_CHESS,board);
				scorem3 = scanSlantR(i, j, BLACK_CHESS,board);
				scorem4 = scanSlantL(i, j, BLACK_CHESS,board);
				totalsm = scorem1 + scorem2 + scorem3 + scorem4; // 人可能的得分
				score[i][j] = totals + totalsm; // 该位置总分
			}
		}
	}
}

int calScore(int different, int same, int blank) { // 不同状态的分值设定
	int score = 0;
	switch (same) {
	case 1: // 一颗子
		switch (different) {
		case 0:
			score = 100;
			break;
		case 1:
			score = 50;
			break;
		case 2:
			score = 30;
			break;
		default:
			printf("Error!!");
		}
		break;
	case 2: // 两颗
		switch (different) {
		case 0:
			score = 500;
			break;
		case 1:
			score = 200;
			break;
		case 2:
			score = 30;
			break;
		default:
			printf("Error!!");
		}
		break;
	case 3: // 三颗
		switch (different) {
		case 0:
			score = 3000;
			break;
		case 1:
			score = 1000;
			break;
		case 2:
			score = 30;
			break;
		default:
			printf("Error!!");
		}
		break;
	case 4:
		switch (different) {
		case 0:
			score = 50000;
			break;
		case 1:
			score = 3000;
			break;
		case 2:
			score = 30;
			break;
		default:
			printf("Error!!");
		}
		break;
	case 5:
		score = 2000000;
		break;
	default:
		printf("Error!!");
	}
	return score; // 返回分数
}

int scanLine(int l, int r, int status,int board[15][15]) { // 计算当前位置横线的分值
	int i; // 声明变量
	int score;
	int blank = 0, same = 1, different = 0;
	i = r;
	while (i > 0) {
		i--;
		if (board[l][i] == status) { // 相同棋子状态
			same++;
		}
		else if (board[l][i] == -status) { // 不同棋子状态
			different++;
			break;
		}
		else {
			blank++; // 空格
			break;
		}
	}
	i = r;
	while (i < 14) {
		i++;
		if (board[l][i] == status) { // 相同棋子状态
			same++;
		}
		else if (board[l][i] == -status) { // 不同棋子状态
			different++;
			break;
		}
		else {
			blank++; // 空格
			break;
		}
	}
	score = calScore(different, same, blank); // 计算分数
	return score; // 返回分数
}

int scanRow(int l, int r, int status, int board[15][15]) { // 计算当前位置竖线的分值
	int i;
	int score;
	int blank = 0, same = 1, different = 0;
	i = l;
	while (i > 0) {
		i--;
		if (board[i][r] == status) { // 相同棋子状态
			same++;
		}
		else if (board[i][r] == -status) { // 不同棋子状态
			different++;
			break;
		}
		else {
			blank++; // 空格
			break;
		}
	}
	i = l;
	while (i < 14) {
		i++;
		if (board[i][r] == status) { // 相同棋子状态
			same++;
		}
		else if (board[i][r] == -status) { // 不同棋子状态
			different++;
			break;
		}
		else {
			blank++; // 空格
			break;
		}
	}
	score = calScore(different, same, blank); // 计算分数
	return score; // 返回分数值
}

int scanSlantR(int l, int r, int status, int board[15][15]) { // 计算当前位置右斜线的分值
	int i, j; // 声明变量
	int score;
	int blank = 0, same = 1, different = 0;
	i = l;
	j = r;
	while (i > 0 && j > 0) {
		i--;
		j--;
		if (board[i][j] == status) { // 相同棋子状态
			same++;
		}
		else if (board[i][j] == -status) { // 不同棋子状态
			different++;
			break;
		}
		else {
			blank++; // 空格
			break;
		}
	}
	i = l;
	j = r;
	while (i < 14 && j < 14) {
		i++;
		j++;
		if (board[i][j] == status) { // 相同棋子状态
			same++;
		}
		else if (board[i][j] == -status) { // 不同棋子状态
			different++;
			break;
		}
		else {
			blank++; // 空格
			break;
		}
	}
	score = calScore(different, same, blank);
	return score;
}

int scanSlantL(int l, int r, int status, int board[15][15]) { // 计算当前位置左斜线的分值
	int i, j; // 声明变量
	int score;
	int blank = 0, same = 1, different = 0;
	i = l;
	j = r;
	while (i > 0 && j < 14) {
		i--;
		j++;
		if (board[i][j] == status) { // 相同棋子状态
			same++;
		}
		else if (board[i][j] == -status) { // 不同棋子状态
			different++;
			break;
		}
		else {
			blank++; // 空格
			break;
		}
	}
	i = l;
	j = r;
	while (i < 14 && j > 0) {
		i++;
		j--;
		if (board[i][j] == status) { // 相同棋子状态
			same++;
		}
		else if (board[i][j] == -status) { // 不同棋子状态
			different++;
			break;
		}
		else {
			blank++; // 空格
			break;
		}
	}
	score = calScore(different, same, blank); // 计算分数
	return score; // 返回分数值
}

void checkPos(int line, int row, int board[15][15], int position[15][15]) { // 找棋子周围空位
	if (line > 0) { // 左和左上
		line--;
		if (board[line][row] == BLANK) {
			position[line][row] = 1;
		}
		if (row > 0) {
			row--;
			if (board[line][row] == BLANK) {
				position[line][row] = 1;
			}
			row++;
		}
		line++;
	}
	if (row > 0) { // 上和右上
		row--;
		if (board[line][row] == BLANK) {
			position[line][row] = 1;
		}
		if (line < 14) {
			line++;
			if (board[line][row] == BLANK) {
				position[line][row] = 1;
			}
			line--;
		}
		row++;
	}
	if (line < 14) { // 右和右下
		line++;
		if (board[line][row] == BLANK) {
			position[line][row] = 1;
		}
		if (row < 14) {
			row++;
			if (board[line][row] == BLANK) {
				position[line][row] = 1;
			}
			row--;
		}
		line--;
	}
	if (row < 14) { // 下和左下
		row++;
		if (board[line][row] == BLANK) {
			position[line][row] = 1;
		}
		if (line > 0) {
			line--;
			if (board[line][row] == BLANK) {
				position[line][row] = 1;
			}
			line++;
		}
		row--;
	}
}
