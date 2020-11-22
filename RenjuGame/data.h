#ifndef _DATA_H
#define _DATA_H

#include "model.h"
#include "global.h"

// ���ݴ�����غ���

void saveBoard(Record* board, int turn); // �������
Winer* loadWiner(); // ��������
void loadBoard(FILE*, Winer*); // �������
void cleanRank(Winer* head); // �����������
void initial(int arr[15][15]); // ��ʼ������
void saveCurrent(Record* board,int turn); // ����Ŀǰ����״̬
Record* loadCurrent(); // ���ص�ǰ����״��
void cleanBoard(Record* head); // ��յ�ǰ��������

#endif // !_DATA_H
