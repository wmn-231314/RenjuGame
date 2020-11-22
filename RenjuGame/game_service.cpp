#include "game_service.h"


int judgeLine(int turn,int board[15][15]) { // �к�����Ӯ
	int i, j, count; // ��������
	int line, result = 0;
	int bw = turn % 2; // �ж��ִ�
	for (i = 0; i < 15; i++) {
		for (j = 0; j <= 10; j++) { // ��������λ��
			count = 0;
			if (bw) { // �жϺ����Ƿ�ʤ��
				line = j;
				while (board[i][line] == BLACK_CHESS) {
					count++;
					line++;
					if (count >= 5) {
						result = 1; // ʤ��
						break;
					}
				}
				j = line;
			}
			else { // �жϰ����Ƿ�ʤ��
				line = j;
				while (board[i][line] == WHITE_CHESS) {
					count++;
					line++;
					if (count >= 5) {
						result = 1; // ʤ��
						break;
					}
				}
				j = line;
			}
			if (result) {
				return result; // ���ؽ��ֵ
			}
		}
	}
	return result; // �����жϽ��
}

int judgeRow(int turn,int board[15][15]) { // ��������Ӯ
	int i, j, count; // ��������
	int row, result = 0;
	int bw = turn % 2; // �ж��ִ�
	for (i = 0; i < 15; i++) {
		for (j = 0; j <= 10; j++) { // ��������λ��
			count = 0;
			if (bw) { // ��Ϊ����
				row = j;
				while (board[row][i] == BLACK_CHESS) {
					count++;
					row++;
					if (count >= 5) { // �ж�����������
						result = 1;
						break;
					}
				}
				j = row;
			}
			else { // ��Ϊ����
				row = j;
				while (board[row][i] == WHITE_CHESS) {
					count++;
					row++;
					if (count >= 5) { // �ж�����������
						result = 1;
						break;
					}
				}
				j = row;
			}
			if (result) { // ���ؽ��ֵ
				return result;
			}
		}
	}
	return result; // ���ؽ��ֵ
}

int judgeSlantR(int turn,int board[15][15]) { // ����б����Ӯ
	int i, j, count; // ��������
	int line, row, result = 0;
	int bw = turn % 2; // �ж��ִ�
	for (i = 0; i <= 10; i++) {
		for (j = 0; j <= 10; j++) { // ��������λ��
			count = 0;
			if (bw) { // ��Ϊ����
				line = i;
				row = j;
				while (board[line][row] == BLACK_CHESS) {
					count++;
					line++;
					row++;
					if (count >= 5) { // �ж�����������
						result = 1;
						break;
					}
				}
			}
			else { // ��Ϊ����
				line = i;
				row = j;
				while (board[line][row] == WHITE_CHESS) {
					count++;
					line++;
					row++;
					if (count >= 5) { // �ж�����������
						result = 1;
						break;
					}
				}
			}
			if (result) { // ���ؽ��ֵ
				return result;
			}
		}
	}
	return result; // ���ؽ��ֵ
}

int judgeSlantL(int turn,int board[15][15]) { // ����б����Ӯ
	int i, j, count; // ��������
	int line, row, result = 0;
	int bw = turn % 2; // �ж��ִ�
	for (i = 0; i <= 10; i++) {
		for (j = 4; j < 15; j++) {
			count = 0;
			if (bw) { // ��Ϊ����
				line = i;
				row = j;
				while (board[line][row] == BLACK_CHESS) {
					count++;
					line++;
					row--;
					if (count >= 5) { // ����������
						result = 1;
						break;
					}
				}
			}
			else { // ��Ϊ����
				line = i;
				row = j;
				while (board[line][row] == WHITE_CHESS) {
					count++;
					line++;
					row--;
					if (count >= 5) { // �ж�����������
						result = 1;
						break;
					}
				}
			}
			if (result) { // ���ؽ��ֵ
				return result;
			}
		}
	}
	return result; // ���ؽ��ֵ
}

int maxStatus(int a, int b, int c, int d, int e) { // �жϵ�ǰ����״̬
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
	return M; // �������ֵ
}

int drawGame(int board[15][15]) { // ��ƽ��
	int i, j;
	int draw = 2;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) { // ��������λ��
			if (board[i][j] == BLANK) {
				draw = 0;
				break;
			}
		}
	}
	return draw; // ���ؽ��ֵ
}