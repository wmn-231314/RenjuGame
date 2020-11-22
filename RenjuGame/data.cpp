#include "data.h"
#include "GUI_display.h"

void initial(int arr[15][15]) { // ��ʼ������
	int i, j;
	for (i = 0; i < 15; i++) { // �������飬�����̳�ֵ��Ϊ0
		for (j = 0; j < 15; j++) {
			arr[i][j] = 0;
		}
	}
}

void saveCurrent(Record* board, int turn) { // ����Ŀǰ����״̬
	Record* head = board,*del;
	FILE* outfile;
	errno_t err;

	err = fopen_s(&outfile, "currentboard", "wb"); // �����ļ������ԭ����
	if (err != 0) { // �ж��Ƿ�ɹ������ļ�
		printf("Failed to create the data file.\n");
		exit(1);
	}
	while (head != NULL) { // ��������
		del = head;
		fwrite(head, sizeof(Record), 1, outfile); // �������е�Ԫ��������ļ���
		head = head->next;
		free(del); // �ͷ������ڴ�
	}
	fclose(outfile); // �ر��ļ�
}

Record* loadCurrent() { // ���ص�ǰ����״��
	FILE* outfile;
	errno_t err;
	Record* head = NULL, * tail = NULL;

	err = fopen_s(&outfile, "currentboard", "rb"); // �򿪴洢��ǰ״���Ķ������ļ�
	if (err != 0) { // �ж��Ƿ����ļ�
		err = fopen_s(&outfile, "currentboard", "wb"); // û���ļ�ʱ���´���
		if (err != 0) { // �ж��Ƿ�ɹ�����
			printf("Failed to create the file"); // ����ʧ����ʾ
			exit(1);
		}
	}
	while (1) { // ��ȡ����
		Record* add;
		add = (Record*)malloc(sizeof(Record)); // ��������Ԫ��
		if (fread(add, sizeof(Record), 1, outfile) != 0) { // ���ļ��ж�ȡ����
			if (head == NULL) { // ����������һ��Ԫ�أ�
				head = add;
				tail = add;
				tail->next = NULL;
			}
			else { // ��������
				tail->next = add;
				add->next = NULL;
				tail = add;
			}
		}
		else {
			free(add); // �ͷŲ���Ҫ���ڴ�
			break;
		}
	}
	fclose(outfile); // �ر��ļ�
	return head; // ���ص�ǰ״̬��ͷָ��
}

void saveBoard(Record* board, int turn) { // �������
	FILE* outfile; // ��������
	Winer* head = NULL, * search = NULL;
	Winer* add, * front = NULL;
	Record* save;
	errno_t err;
	char name[100];
	int i;
	int search_turn, add_turn;

	add = (Winer*)malloc(sizeof(Winer)); // ��������
	disSave(name); // ��ȡ��ʤ������
	strcpy_s(add->name, name); // ��������ֵ������Ԫ����
	add->turns = turn; // ������Ԫ�ظ�ֵ
	add->winb = board;
	head = loadWiner(); // ����ԭ����
	if (head == NULL) { // ����Ϊ��ʱ������������Ϊ������
		head = add;
		add->next = NULL;
	}
	else { // ������Ϊ��ʱ���������̲���ԭ������
		search = head;
		add_turn = (add->turns + 1) / 2;
		while (search != NULL) {
			search_turn = (search->turns + 1) / 2;
			if (search_turn < add_turn) { // Ѱ�Ҳ����λ��
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
	err = fopen_s(&outfile,"renjudata", "wb"); // �����ļ������ԭ����
	if (err != 0) { // �ж��Ƿ�ɹ������ļ�
		printf("Failed to create the data file.\n");
		exit(1);
	}
	while (head != NULL) { // ����������������ļ�
		fwrite(head, sizeof(Winer), 1, outfile); // �����ʤ����Ϣ
		save = head->winb;
		for (i = 0; i < head->turns; i++) {
			fwrite(save, sizeof(Record), 1, outfile); // �����ʤ����������
			save = save->next;
		}
		head = head->next;
	}
	fclose(outfile); // �ر��ļ�
}

Winer* loadWiner() { // ��������
	FILE* outfile;
	errno_t err;
	Winer* head = NULL, * tail = NULL;

	err = fopen_s(&outfile,"renjudata", "rb"); // �������ļ�
	if (err != 0) { // ����ԭ���ļ��򴴽����ļ�
		err = fopen_s(&outfile,"renjudata", "wb");
		if (err != 0) { // �ж��Ƿ񴴽��ɹ�
			printf("Failed to create the file");
			exit(1);
		}
	}
	while (1) {
		Winer* add;
		add = (Winer*)malloc(sizeof(Winer)); // ��������
		if (fread(add, sizeof(Winer), 1, outfile) != 0) { //���ļ��ж�ȡ����
			if (head == NULL) { // ��Ϊ��һ��Ԫ��
				head = add;
				tail = add;
				tail->next = NULL;
			}
			else {
				tail->next = add;
				add->next = NULL;
				tail = add;
			}
			loadBoard(outfile, add); // �������
		}
		else {
			free(add); // �ͷŲ���Ҫ���ڴ�
			break;
		}
	}
	fclose(outfile); // �ر��ļ�
	return head;
}

void loadBoard(FILE* file, Winer* win) { // �������
	Record* tail = NULL;
	int i;

	for (i = 0; i < win->turns; i++) { // ������turns������Ԫ��
		Record* add;
		add = (Record*)malloc(sizeof(Record)); // ��������
		fread(add, sizeof(Record), 1, file);
		if (i == 0) { // ��һ��Ԫ��
			win->winb = add;
			tail = add;
			add->next = NULL;
		}
		else { // ����Ԫ��
			tail->next = add;
			add->next = NULL;
			tail = add;
		}
	}
}

void cleanRank(Winer* head) { // �������������
	FILE* cleanfile; // ��������
	errno_t err;
	Winer* clean, * search;

	err = fopen_s(&cleanfile,"renjudata", "wb"); // �����´����ļ�
	if (err != 0) { // �ж��Ƿ�ɹ�����
		printf("Failed to clean the rank.\n");
		return;
	}
	search = head;
	head = NULL;
	while (search != NULL) { // ��������
		clean = search;
		search = search->next;
		free(clean); // �ͷ������ڴ�
	}
	fclose(cleanfile); // �ر��ļ�
}

void cleanBoard(Record* head) { // ��յ�ǰ��������
	FILE* cleanfile; // ��������
	errno_t err;
	Record* clean, * search;

	err = fopen_s(&cleanfile, "currentboard", "wb"); // �����´����ļ�
	if (err != 0) { // �ж��Ƿ�ɹ�����
		printf("Failed to clean the board.\n");
		return;
	}
	search = head;
	head = NULL;
	while (search != NULL) { // ��������
		clean = search;
		search = search->next;
		free(clean); // �ͷ������ڴ�
	}
	fclose(cleanfile); // �ر��ļ�
}
