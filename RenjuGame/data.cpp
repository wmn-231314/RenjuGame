#include "data.h"
#include "GUI_display.h"

void initial(int arr[15][15]) { // 初始化棋盘
	int i, j;
	for (i = 0; i < 15; i++) { // 遍历数组，将棋盘初值设为0
		for (j = 0; j < 15; j++) {
			arr[i][j] = 0;
		}
	}
}

void saveCurrent(Record* board, int turn) { // 保存目前棋盘状态
	Record* head = board,*del;
	FILE* outfile;
	errno_t err;

	err = fopen_s(&outfile, "currentboard", "wb"); // 创建文件并清空原数据
	if (err != 0) { // 判断是否成功创建文件
		printf("Failed to create the data file.\n");
		exit(1);
	}
	while (head != NULL) { // 遍历链表
		del = head;
		fwrite(head, sizeof(Record), 1, outfile); // 将链表中的元素输出到文件中
		head = head->next;
		free(del); // 释放无用内存
	}
	fclose(outfile); // 关闭文件
}

Record* loadCurrent() { // 加载当前棋盘状况
	FILE* outfile;
	errno_t err;
	Record* head = NULL, * tail = NULL;

	err = fopen_s(&outfile, "currentboard", "rb"); // 打开存储当前状况的二进制文件
	if (err != 0) { // 判断是否有文件
		err = fopen_s(&outfile, "currentboard", "wb"); // 没有文件时重新创建
		if (err != 0) { // 判断是否成功创建
			printf("Failed to create the file"); // 创建失败提示
			exit(1);
		}
	}
	while (1) { // 读取链表
		Record* add;
		add = (Record*)malloc(sizeof(Record)); // 创建链表元素
		if (fread(add, sizeof(Record), 1, outfile) != 0) { // 从文件中读取数据
			if (head == NULL) { // 连接链表（第一个元素）
				head = add;
				tail = add;
				tail->next = NULL;
			}
			else { // 连接链表
				tail->next = add;
				add->next = NULL;
				tail = add;
			}
		}
		else {
			free(add); // 释放不需要的内存
			break;
		}
	}
	fclose(outfile); // 关闭文件
	return head; // 返回当前状态的头指针
}

void saveBoard(Record* board, int turn) { // 保存棋局
	FILE* outfile; // 声明变量
	Winer* head = NULL, * search = NULL;
	Winer* add, * front = NULL;
	Record* save;
	errno_t err;
	char name[100];
	int i;
	int search_turn, add_turn;

	add = (Winer*)malloc(sizeof(Winer)); // 创建链表
	disSave(name); // 获取获胜者姓名
	strcpy_s(add->name, name); // 将姓名赋值到链表元素中
	add->turns = turn; // 给链表元素赋值
	add->winb = board;
	head = loadWiner(); // 加载原排名
	if (head == NULL) { // 排名为空时，将新棋盘作为新排名
		head = add;
		add->next = NULL;
	}
	else { // 排名不为空时，将新棋盘插入原排名中
		search = head;
		add_turn = (add->turns + 1) / 2;
		while (search != NULL) {
			search_turn = (search->turns + 1) / 2;
			if (search_turn < add_turn) { // 寻找插入的位置
				front = search;
				search = search->next;
			}
			else {
				break;
			}
		}
		if (front == NULL) {
			add->next = head;
			head = add;
		}
		else {
			add->next = front->next;
			front->next = add;
		}
	}
	err = fopen_s(&outfile,"renjudata", "wb"); // 创建文件并清空原数据
	if (err != 0) { // 判断是否成功创建文件
		printf("Failed to create the data file.\n");
		exit(1);
	}
	while (head != NULL) { // 遍历链表并将输出到文件
		fwrite(head, sizeof(Winer), 1, outfile); // 输出获胜者信息
		save = head->winb;
		for (i = 0; i < head->turns; i++) {
			fwrite(save, sizeof(Record), 1, outfile); // 输出获胜者所下棋盘
			save = save->next;
		}
		head = head->next;
	}
	fclose(outfile); // 关闭文件
}

Winer* loadWiner() { // 加载排名
	FILE* outfile;
	errno_t err;
	Winer* head = NULL, * tail = NULL;

	err = fopen_s(&outfile,"renjudata", "rb"); // 打开排名文件
	if (err != 0) { // 若无原有文件则创建新文件
		err = fopen_s(&outfile,"renjudata", "wb");
		if (err != 0) { // 判断是否创建成功
			printf("Failed to create the file");
			exit(1);
		}
	}
	while (1) {
		Winer* add;
		add = (Winer*)malloc(sizeof(Winer)); // 创建链表
		if (fread(add, sizeof(Winer), 1, outfile) != 0) { //从文件中读取排名
			if (head == NULL) { // 若为第一个元素
				head = add;
				tail = add;
				tail->next = NULL;
			}
			else {
				tail->next = add;
				add->next = NULL;
				tail = add;
			}
			loadBoard(outfile, add); // 加载棋局
		}
		else {
			free(add); // 释放不需要的内存
			break;
		}
	}
	fclose(outfile); // 关闭文件
	return head;
}

void loadBoard(FILE* file, Winer* win) { // 加载棋局
	Record* tail = NULL;
	int i;

	for (i = 0; i < win->turns; i++) { // 共加载turns次棋盘元素
		Record* add;
		add = (Record*)malloc(sizeof(Record)); // 创建链表
		fread(add, sizeof(Record), 1, file);
		if (i == 0) { // 第一个元素
			win->winb = add;
			tail = add;
			add->next = NULL;
		}
		else { // 其余元素
			tail->next = add;
			add->next = NULL;
			tail = add;
		}
	}
}

void cleanRank(Winer* head) { // 清空链表（排名）
	FILE* cleanfile; // 变量声明
	errno_t err;
	Winer* clean, * search;

	err = fopen_s(&cleanfile,"renjudata", "wb"); // 即重新创建文件
	if (err != 0) { // 判断是否成功创建
		printf("Failed to clean the rank.\n");
		return;
	}
	search = head;
	head = NULL;
	while (search != NULL) { // 遍历排名
		clean = search;
		search = search->next;
		free(clean); // 释放无用内存
	}
	fclose(cleanfile); // 关闭文件
}

void cleanBoard(Record* head) { // 清空当前棋盘数据
	FILE* cleanfile; // 变量声明
	errno_t err;
	Record* clean, * search;

	err = fopen_s(&cleanfile, "currentboard", "wb"); // 即重新创建文件
	if (err != 0) { // 判断是否成功创建
		printf("Failed to clean the board.\n");
		return;
	}
	search = head;
	head = NULL;
	while (search != NULL) { // 遍历链表
		clean = search;
		search = search->next;
		free(clean); // 释放无用内存
	}
	fclose(cleanfile); // 关闭文件
}
