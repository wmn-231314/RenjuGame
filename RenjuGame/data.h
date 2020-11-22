#ifndef _DATA_H
#define _DATA_H

#include "model.h"
#include "global.h"

// 数据处理相关函数

void saveBoard(Record* board, int turn); // 保存棋局
Winer* loadWiner(); // 加载排名
void loadBoard(FILE*, Winer*); // 加载棋局
void cleanRank(Winer* head); // 清空排名链表
void initial(int arr[15][15]); // 初始化棋盘
void saveCurrent(Record* board,int turn); // 保存目前棋盘状态
Record* loadCurrent(); // 加载当前棋盘状况
void cleanBoard(Record* head); // 清空当前棋盘数据

#endif // !_DATA_H
