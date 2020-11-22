#include "manmashine_service.h"
#include "data.h"

void findPos(int board[15][15],int position[15][15]) { // �Ҵ������̵�����
	initial(position); // ��ʼ��λ�õĶ�ά����
	int i, j;
	for (i = 0; i < 15; i++) { // ��������
		for (j = 0; j < 15; j++) {
			if (board[i][j] != BLANK) {
				checkPos(i, j,board,position); // �ҵ�������Χ��λ
			}
		}
	}
}

Chess* maxScore(int score[15][15]) { // �������ֵ
	int i, j,same = 0; // ��������
	int random = 0,find = 0;
	int max = score[0][0];
	Chess* maxpos;
	maxpos = (Chess*)malloc(sizeof(Chess)); // �����ڴ�
	maxpos->line = 0;
	maxpos->row = 0;
	for (i = 0; i < 15; i++) { // ����
		for (j = 0; j < 15; j++) {
			if (score[i][j] > max) { // �ҵ����ֵ
				same = 1;
				max = score[i][j];
				maxpos->line = i;
				maxpos->row = j;
			}
			else if (score[i][j] == max) {
				same++; // �����м�����ͬ�����ֵ
			}
		}
	}
	if (same > 1) { // ����һ��ʱ
		srand((unsigned)time(NULL)); // ���ѡ��һ��
		random = rand()%same;
		for (i = 0; i < 15; i++) { // ����
			for (j = 0; j < 15; j++) {
				if (score[i][j] == max) { // �ҵ����ֵ
					if (random == 0) {
						find = 1;
						maxpos->line = i;
						maxpos->row = j;
						break;
					}
					random--;
				}
			}
			if (find) { // �ҵ�ѡ����Ǹ����ֵ
				break;
			}
		}
	}
	return maxpos; // �������ֵ�Ľṹ��ָ��
}

void nextScore(int position[15][15],int score[15][15],int board[15][15]) { // ����ÿ��pos��һ���ĵ÷�
	int i, j; // ��������
	initial(score); // ��ʼ�������Ķ�ά����
	int score1, score2, score3, score4, totals; // ������4�����
	int scorem1, scorem2, scorem3, scorem4, totalsm; // �˵�4�����
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) { // ��������
			if (position[i][j] == 1) { // �ҵ�������Χ��λ
				score1 = scanLine(i, j, WHITE_CHESS,board); // ����������
				score2 = scanRow(i, j, WHITE_CHESS,board);
				score3 = scanSlantR(i, j, WHITE_CHESS,board);
				score4 = scanSlantL(i, j, WHITE_CHESS,board);
				totals = score1 + score2 + score3 + score4; // �����÷�
				scorem1 = scanLine(i, j, BLACK_CHESS,board);
				scorem2 = scanRow(i, j, BLACK_CHESS,board);
				scorem3 = scanSlantR(i, j, BLACK_CHESS,board);
				scorem4 = scanSlantL(i, j, BLACK_CHESS,board);
				totalsm = scorem1 + scorem2 + scorem3 + scorem4; // �˿��ܵĵ÷�
				score[i][j] = totals + totalsm; // ��λ���ܷ�
			}
		}
	}
}

int calScore(int different, int same, int blank) { // ��ͬ״̬�ķ�ֵ�趨
	int score = 0;
	switch (same) {
	case 1: // һ����
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
	case 2: // ����
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
	case 3: // ����
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
	return score; // ���ط���
}

int scanLine(int l, int r, int status,int board[15][15]) { // ���㵱ǰλ�ú��ߵķ�ֵ
	int i; // ��������
	int score;
	int blank = 0, same = 1, different = 0;
	i = r;
	while (i > 0) {
		i--;
		if (board[l][i] == status) { // ��ͬ����״̬
			same++;
		}
		else if (board[l][i] == -status) { // ��ͬ����״̬
			different++;
			break;
		}
		else {
			blank++; // �ո�
			break;
		}
	}
	i = r;
	while (i < 14) {
		i++;
		if (board[l][i] == status) { // ��ͬ����״̬
			same++;
		}
		else if (board[l][i] == -status) { // ��ͬ����״̬
			different++;
			break;
		}
		else {
			blank++; // �ո�
			break;
		}
	}
	score = calScore(different, same, blank); // �������
	return score; // ���ط���
}

int scanRow(int l, int r, int status, int board[15][15]) { // ���㵱ǰλ�����ߵķ�ֵ
	int i;
	int score;
	int blank = 0, same = 1, different = 0;
	i = l;
	while (i > 0) {
		i--;
		if (board[i][r] == status) { // ��ͬ����״̬
			same++;
		}
		else if (board[i][r] == -status) { // ��ͬ����״̬
			different++;
			break;
		}
		else {
			blank++; // �ո�
			break;
		}
	}
	i = l;
	while (i < 14) {
		i++;
		if (board[i][r] == status) { // ��ͬ����״̬
			same++;
		}
		else if (board[i][r] == -status) { // ��ͬ����״̬
			different++;
			break;
		}
		else {
			blank++; // �ո�
			break;
		}
	}
	score = calScore(different, same, blank); // �������
	return score; // ���ط���ֵ
}

int scanSlantR(int l, int r, int status, int board[15][15]) { // ���㵱ǰλ����б�ߵķ�ֵ
	int i, j; // ��������
	int score;
	int blank = 0, same = 1, different = 0;
	i = l;
	j = r;
	while (i > 0 && j > 0) {
		i--;
		j--;
		if (board[i][j] == status) { // ��ͬ����״̬
			same++;
		}
		else if (board[i][j] == -status) { // ��ͬ����״̬
			different++;
			break;
		}
		else {
			blank++; // �ո�
			break;
		}
	}
	i = l;
	j = r;
	while (i < 14 && j < 14) {
		i++;
		j++;
		if (board[i][j] == status) { // ��ͬ����״̬
			same++;
		}
		else if (board[i][j] == -status) { // ��ͬ����״̬
			different++;
			break;
		}
		else {
			blank++; // �ո�
			break;
		}
	}
	score = calScore(different, same, blank);
	return score;
}

int scanSlantL(int l, int r, int status, int board[15][15]) { // ���㵱ǰλ����б�ߵķ�ֵ
	int i, j; // ��������
	int score;
	int blank = 0, same = 1, different = 0;
	i = l;
	j = r;
	while (i > 0 && j < 14) {
		i--;
		j++;
		if (board[i][j] == status) { // ��ͬ����״̬
			same++;
		}
		else if (board[i][j] == -status) { // ��ͬ����״̬
			different++;
			break;
		}
		else {
			blank++; // �ո�
			break;
		}
	}
	i = l;
	j = r;
	while (i < 14 && j > 0) {
		i++;
		j--;
		if (board[i][j] == status) { // ��ͬ����״̬
			same++;
		}
		else if (board[i][j] == -status) { // ��ͬ����״̬
			different++;
			break;
		}
		else {
			blank++; // �ո�
			break;
		}
	}
	score = calScore(different, same, blank); // �������
	return score; // ���ط���ֵ
}

void checkPos(int line, int row, int board[15][15], int position[15][15]) { // ��������Χ��λ
	if (line > 0) { // �������
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
	if (row > 0) { // �Ϻ�����
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
	if (line < 14) { // �Һ�����
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
	if (row < 14) { // �º�����
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
