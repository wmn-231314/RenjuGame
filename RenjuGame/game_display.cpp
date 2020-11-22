#include "data.h"
#include "game_display.h"
#include "game_service.h"
#include "GUI_display.h"
#include "manmashine_service.h"
#include "web_service.h"



void startGame(int board[15][15]) { // ��ʼ˫����Ϸ
	initial(board); // ��ʼ������
	int now; // ��������
	int line;
	int row, bw, ans = 0;
	int turn = 1;
	IMAGE but, butd, imgbback, imgbsave, imgwback, imgwsave, imgdback;

	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // ���ذ�ť
	loadimage(&butd, _T("image\\drawbut.jpg"), 40, 40, true);
	Record* head = loadCurrent(); // ���ص�ǰ��֣�����оֹ��ܣ�
	Record* tail = head;

	if (tail != NULL) { // ���во�ʱ
		ans = disConQue(); // �ж��Ƿ��������
	}
	loadimage(NULL, _T("image\\board1.jpg")); // ˫����ϷͼƬ

	if (ans) { // ��������ʱ
		while (tail != NULL) { // ������ǰ���
			board[tail->x][tail->y] = tail->chess; // ����ִ洢��������
			if (tail->chess == BLACK_CHESS) { // �жϺ��ӺͰ���
				bw = 1;
			}
			else if (tail->chess == WHITE_CHESS) {
				bw = 0;
			}
			disChess(tail->x, tail->y, bw); // ��ʾ��������
			if (tail->next == NULL) { // ��βָ����������ĩβ
				turn++;
				break;
			}
			tail = tail->next;
			turn++; // �����������
		}
		now = clock(); // �ȴ�
		while (clock() - now < CLOCKS_PER_SEC);
		bw = turn % 2; // ���㵱ǰ�ִ�
		disHint(bw); // ��ʾ�ִ���ʾ
	}
	else { // �����زо�
		cleanBoard(head); // ����о�����
		tail = NULL; // ��βָ���ͷָ�붼��ֵΪ��
		head = NULL;
	}

	while (true) { // ��ʼ����
		int win; // ��������
		Record* add;
		MOUSEMSG mouse;
		bw = turn % 2; // ���㵱ǰ�ִ�

		while (true) { // ��ȡ�����Ϣ
			mouse = GetMouseMsg();
			if (mouse.x >= 205 && mouse.x <= 590 && mouse.y >= 105 && mouse.y <= 490) {
				if (mouse.mkLButton) {
					line = (mouse.x - 205) / 26; // ת������������
					row = (mouse.y - 105) / 26;
					if (board[line][row] == BLANK) { // ����
						if (bw) { // ��������Ϣ�洢��������
							board[line][row] = BLACK_CHESS;
						}
						else {
							board[line][row] = WHITE_CHESS;
						}
						FlushMouseMsgBuffer(); // ��������Ϣ������
						break;
					}
				}
				
			}
			else if (mouse.x >= 645 && mouse.x <= 755 && mouse.y >= 510 && mouse.y <= 570) {
				if (mouse.mkLButton) { // ���ز˵�
					saveCurrent(head,turn); // ���浱ǰ���
					return;
				}
			}
		}

		mciSendString(TEXT("seek chess to start"), NULL, 0, NULL); // ������Ч
		mciSendString(TEXT("play chess"), NULL, 0, NULL);
		disChess(line,row,bw); // ��ʾ�����ڻ�ͼ����
		win = maxStatus(judgeLine(turn,board), judgeRow(turn,board), judgeSlantR(turn,board), judgeSlantL(turn,board), drawGame(board)); // ��Ӯ

		add = (Record*)malloc(sizeof(Record)); // �������岽��
		add->x = line; // �������λ�ú�״̬��ֵ������Ԫ��
		add->y = row;
		add->chess = board[add->x][add->y];
		if (head == NULL) { // ��һ��Ԫ��ʱ
			head = add;
			tail = add;
			add->next = NULL;
		}
		else { // ����Ԫ��ʱ����������
			tail->next = add;
			add->next = NULL;
			tail = add;
		}

		if (win == 1) { // ��Ӯ
			now = clock(); // �ȴ�
			while (clock() - now < CLOCKS_PER_SEC);
			FlushMouseMsgBuffer(); // �����껺����
			if (bw) { // �жϵ�ǰ�ִ�
				loadimage(NULL, _T("image\\winb.jpg"), 800, 600, true); // �����ʤ
				getimage(&imgbsave, 265, 170, 40, 40); // ���ڰ�ť�ı���ͼ
				getimage(&imgbback, 265, 360, 40, 40);
			}
			else {
				loadimage(NULL, _T("image\\winw.jpg"), 800, 600, true); // �����ʤ
				getimage(&imgwsave, 55, 170, 40, 40); // ���ڰ�ť�ı���ͼ
				getimage(&imgwback, 55, 360, 40, 40);
			}
			while (true) {
				mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				if (bw) { // �ж��ִ�
					if (mouse.x >= 325 && mouse.x <= 645 && mouse.y >= 155 && mouse.y <= 225) {
						if (mouse.mkLButton) {
							saveBoard(head, turn); // ѡ�񱣴�
							break;
						}
						else {
							putimage(265, 170, &but); // ��ť
						}
					}
					else {
						putimage(265, 170, &imgbsave);
					}
					if (mouse.x >= 325 && mouse.x <= 645 && mouse.y >= 360 && mouse.y <= 410) {
						if (mouse.mkLButton) {
							break; // ѡ��ֱ�ӻص��˵�
						}
						else {
							putimage(265, 360, &but);
						}
					}
					else {
						putimage(265, 360, &imgbback);
					}
				}
				else {
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 155 && mouse.y <= 225) {
						if (mouse.mkLButton) {
							saveBoard(head, turn); // ѡ�񱣴�
							break;
						}
						else {
							putimage(55, 170, &but);
						}
					}
					else {
						putimage(55, 170, &imgwsave);
					}
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 360 && mouse.y <= 410) {
						if (mouse.mkLButton) { // ѡ��ֱ�ӻص��˵�
							break;
						}
						else {
							putimage(55, 360, &but);
						}
					}
					else {
						putimage(55, 360, &imgwback);
					}
				}
			}
			cleanBoard(head); // ��յ�ǰ������Ϣ
			break;
		}
		else if (win == 2) { // ƽ��
			now = clock(); // �ȴ�
			while (clock() - now < CLOCKS_PER_SEC);
			FlushMouseMsgBuffer(); // �����껺����
			loadimage(NULL, _T("image\\draw.jpg"), 800, 600, true); // ��ʾƽ��ͼƬ
			getimage(&imgdback, 115, 450, 40, 40); // ��ť����ͼ
			while (true) {
				mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				if (mouse.x >= 175 && mouse.x <= 395 && mouse.y >= 450 && mouse.y <= 495) {
					if (mouse.mkLButton) {
						break; // ���ز˵�
					}
					else {
						putimage(115, 450, &butd);
					}
				}
				else {
					putimage(115, 450, &imgdback);
				}
			}
			cleanBoard(head); // ��յ�ǰ���
			break;
		}
		turn++;
	}
}

void manMashine(int board[15][15]) { // ��ʼ�˻���ս
	initial(board); // ��ʼ������
	int line; // ��������
	char row;
	int turn = 1;
	IMAGE but, butd, imgsave, imgback, imgloss, imgdback;

	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // ���ذ�ť
	loadimage(&butd, _T("image\\drawbut.jpg"), 40, 40, true); // ����ƽ�ְ�ť

	Chess* pos;
	Record* head = NULL, * tail = NULL;
	int position[15][15] = {0}; // ��ʼ��λ�úͷ������飨���ڻ�����������λ�ã�
	int score[15][15] = {0};

	while (true) { // ��ʼ����
		int bw, win ,now; // ��������
		Record* add;
		MOUSEMSG mouse;
		bw = turn % 2;
		if (bw) { // ���ִ�
			while (true) {
				mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				if (mouse.x >= 205 && mouse.x <= 590 && mouse.y >= 105 && mouse.y <= 490) {
					if (mouse.mkLButton) {
						line = (mouse.x - 205) / 26; // ת������������
						row = (mouse.y - 105) / 26;
						if (board[line][row] == BLANK) { // �ж��Ƿ��ܹ�����
							board[line][row] = BLACK_CHESS;
							FlushMouseMsgBuffer(); // �����껺����
							break;
						}
					}

				}
			}
		}
		else {
			findPos(board,position); // ��������Χλ��
			nextScore(position,score,board); // ����λ�÷���
			pos = maxScore(score); // ������λ��
			line = pos->line; // �������
			row = pos->row;
			board[line][row] = WHITE_CHESS;
		}

		add = (Record*)malloc(sizeof(Record)); // �������岽��
		add->x = line;
		add->y = row;
		add->chess = board[add->x][add->y];
		if (head == NULL) { // ��һ��Ԫ��
			head = add;
			tail = add;
			add->next = NULL;
		}
		else { // ����Ԫ��
			tail->next = add;
			add->next = NULL;
			tail = add;
		}

		mciSendString(TEXT("seek chess to start"), NULL, 0, NULL); // ������Ч
		mciSendString(TEXT("play chess"), NULL, 0, NULL);
		disChess(line, row, bw); // ��ʾ����
		win = maxStatus(judgeLine(turn,board), judgeRow(turn,board), judgeSlantR(turn,board), judgeSlantL(turn,board), drawGame(board)); // ��Ӯ

		if (win == 1) { // ʤ��
			now = clock(); // �ȴ�
			while (clock() - now < CLOCKS_PER_SEC*2);
			if (bw) { // �жϵ�ǰ�ִ�
				loadimage(NULL, _T("image\\mmwin.jpg"), 800, 600, true); // ��ʤͼƬ
				getimage(&imgsave, 55, 170, 40, 40);
				getimage(&imgback, 55, 360, 40, 40);

			}
			else {
				loadimage(NULL, _T("image\\mmlose.jpg"), 800, 600, true); // ʧ��ͼƬ
				getimage(&imgloss, 370, 275, 40, 40);
			}
			while (true) {
				mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				if (bw) {	 // �жϵ�ǰ�ִ�
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 155 && mouse.y <= 225) {
						if (mouse.mkLButton) {
							saveBoard(head, turn); // ����
							break;
						}
						else {
							putimage(55, 170, &but); // ��ť
						}
						
					}
					else {
						putimage(55, 170, &imgsave);
					}
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 360 && mouse.y <= 410) {
						if (mouse.mkLButton) { // ֱ�ӷ���
							break;
						}
						else {
							putimage(55, 360, &but);
						}
					}
					else {
						putimage(55, 360, &imgback);
					}
				}
				else {
					if (mouse.x >= 430 && mouse.x <= 735 && mouse.y >= 265 && mouse.y <= 330) {
						if (mouse.mkLButton) { // ֱ�ӷ���
							break;
						}
						else {
							putimage(370, 275, &but);
						}
					}
					else {
						putimage(370, 275, &imgloss);

					}
				}
			}
			break;
		}
		else if (win == 2) { // ƽ��ʱ
			now = clock(); // �ȴ�
			while (clock() - now < CLOCKS_PER_SEC);
			FlushMouseMsgBuffer(); // �����껺����
			loadimage(NULL, _T("image\\draw.jpg"), 800, 600, true); // ����ƽ��ͼƬ
			getimage(&imgdback, 115, 450, 40, 40);
			while (true) {
				mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				if (mouse.x >= 175 && mouse.x <= 395 && mouse.y >= 450 && mouse.y <= 495) {
					if (mouse.mkLButton) { // ���ز˵�
						break;
					}
					else {
						putimage(115, 450, &butd);
					}
				}
				else {
					putimage(115, 450, &imgdback);
				}
			}
			break;
		}
		turn++; // �ִ�����
	}
}


void rankList() { // ���ز��������
	Winer* head = NULL,*search = NULL;
	int i = 0,rank;
	MOUSEMSG mouse;

	while (true) {
		if (i == 0) { // ��һҳ
			head = loadWiner(); // ��������
			search = head;
			loadimage(NULL, _T("image\\rank1.jpg"), 800, 600, true); // ��һҳͼƬ
		}
		while (search != NULL) { // ������������
			if (i == 5) { // �ڶ�ҳ
				loadimage(NULL, _T("image\\rank2.jpg"), 800, 600, true); // �ڶ�ҳͼƬ
			}
			i++;
			rank = ((i-1) % 5) + 1;
			disWinner(rank, search->name, search->turns); // ��ʾ����
			search = search->next;
			if (i % 5 == 0) {
				break;
			}
		}
		while (true) {
			mouse = GetMouseMsg(); // ��ȡ�����Ϣ
			if (mouse.mkLButton) {
				if (mouse.x >= 640 && mouse.x <= 750 && mouse.y >= 550 && mouse.y <= 580) {
					if (i > 5) { // ѡ����һҳ
						i = 0;
					}
					break;
				}
				else if (mouse.x >= 600 && mouse.x <= 720 && mouse.y >= 75 && mouse.y <= 120) {
					return; // ���ز˵�
				}
				else if (mouse.x >= 60 && mouse.x <= 165 && mouse.y >= 70 && mouse.y <= 125) {
					cleanRank(head); // �������
					i = 0;
					break;
				}
			}
		}
	}
}

void displayWinerB(Winer* win,int board[15][15]) { // ��ȡ������ع����
	Record* search; // ��������
	int now,bw,winer;

	initial(board); // ��ʼ������
	search = win->winb; // ��ȡ��������
	winer = win->turns % 2; // ��ȡ����

	if (winer) { // �жϻ�ʤ�ַ߳�
		loadimage(NULL, _T("image\\reviewb.jpg")); // ��ʤ
	}
	else {
		loadimage(NULL, _T("image\\revieww.jpg")); // ��ʤ
	}

	while (search != NULL) { // �ع����
		board[search->x][search->y] = search->chess;
		if (search->chess == BLACK_CHESS) { // �жϵ�ǰΪ�ڻ��
			bw = 1;
		}
		else {
			bw = 0;
		}
		now = clock(); // wait
		while (clock() - now < CLOCKS_PER_SEC); // �ȴ�ʱ��
		mciSendString(TEXT("seek chess to start"), NULL, 0, NULL); // ������Ч
		mciSendString(TEXT("play chess"), NULL, 0, NULL);
		disChess(search->x,search->y,bw); // ��ʾ���
		search = search->next;
	}
	now = clock(); // �ȴ�
	while (clock() - now < CLOCKS_PER_SEC*2); // �ȴ�չʾʱ��
}

void startWebGame(SOCKET* newC, int board[15][15], int status) { // ��ʼ�����ս
	initial(board); // ��ʼ������
	int line; // ��������
	int row, bw;
	int turn = 1;
	IMAGE but, butd, imgsave, imgback, imgloss, imgdback;

	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // ���ذ�ťͼƬ
	loadimage(&butd, _T("image\\drawbut.jpg"), 40, 40, true);
	Record* head = NULL, * tail = NULL;

	while (true) {
		int win = 0, now;
		Record* add;
		MOUSEMSG mouse;
		Chess* chess;
		bw = turn % 2;
		if (bw == status) { // �ж������ִΣ��Լ��£�
			while (true) {
				mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				if (mouse.x >= 205 && mouse.x <= 590 && mouse.y >= 105 && mouse.y <= 490) {
					if (mouse.mkLButton) {
						line = (mouse.x - 205) / 26; // ת������
						row = (mouse.y - 105) / 26;
						if (board[line][row] == BLANK) { // ����
							if (status) { // ���ݳַ������鸳ֵ��������
								board[line][row] = BLACK_CHESS;
							}
							else {
								board[line][row] = WHITE_CHESS;
							}
							FlushMouseMsgBuffer(); // �����껺����
							break;
						}
					}

				}
			}
			sentChat(newC,line,row); // ������������
		}
		else { // �Է�����
			chess = receiveChat(newC); // ��ȡ��������
			line = chess->line; // ��
			row = chess->row; // ��
			if (board[line][row] == BLANK) { // ����
				if (!status) { // ���ݶԷ��ַ���ֵ��������
					board[line][row] = BLACK_CHESS;
				}
				else {
					board[line][row] = WHITE_CHESS;
				}
				FlushMouseMsgBuffer(); // �����껺����
			}
		}

		mciSendString(TEXT("seek chess to start"), NULL, 0, NULL); // ������Ч
		mciSendString(TEXT("play chess"), NULL, 0, NULL);
		disChess(line, row, bw); // ��ʾ����
		win = maxStatus(judgeLine(turn, board), judgeRow(turn, board), judgeSlantR(turn, board), judgeSlantL(turn, board), drawGame(board)); // ��Ӯ

		add = (Record*)malloc(sizeof(Record)); // �������岽��
		add->x = line; // ����ǰ����������״̬��ֵ������Ԫ��
		add->y = row;
		add->chess = board[add->x][add->y];
		if (head == NULL) { // ��һ��Ԫ��
			head = add;
			tail = add;
			add->next = NULL;
		}
		else { // ����Ԫ��
			tail->next = add;
			add->next = NULL;
			tail = add;
		}

		if (win == 1) { // ��ʤ
			now = clock(); // wait
			while (clock() - now < CLOCKS_PER_SEC * 2); // �ȴ���չʾ��ʱ��
			if (bw == status) { // ���ݳַ����ж���Ӯ
				loadimage(NULL, _T("image\\mmwin.jpg"), 800, 600, true); // ��ʤ
				getimage(&imgsave, 55, 170, 40, 40); // ���ذ�ť����ͼ
				getimage(&imgback, 55, 360, 40, 40);

			}
			else {
				loadimage(NULL, _T("image\\mmlose.jpg"), 800, 600, true); // ��
				getimage(&imgloss, 370, 275, 40, 40);
			}
			while (true) {
				mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				if (bw == status) { // ���ݳַ��ж���ʾ����
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 155 && mouse.y <= 225) {
						if (mouse.mkLButton) {
							saveBoard(head, turn); // ����
							break;
						}
						else {
							putimage(55, 170, &but); // ��ʾ��ť
						}

					}
					else {
						putimage(55, 170, &imgsave);
					}
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 360 && mouse.y <= 410) {
						if (mouse.mkLButton) { // ���ز˵�
							break;
						}
						else {
							putimage(55, 360, &but); // ��ʾ��ť
						}
					}
					else {
						putimage(55, 360, &imgback);
					}
				}
				else {
					if (mouse.x >= 430 && mouse.x <= 735 && mouse.y >= 265 && mouse.y <= 330) {
						if (mouse.mkLButton) { // ���ز˵�
							break;
						}
						else {
							putimage(370, 275, &but); // ��ʾ��ť
						}
					}
					else {
						putimage(370, 275, &imgloss);

					}
				}
			}
			break;
		}
		else if (win == 2) { // ƽ��
			now = clock(); // wait
			while (clock() - now < CLOCKS_PER_SEC); // �ȴ���չʾ��ʱ��
			FlushMouseMsgBuffer(); // �����껺����
			loadimage(NULL, _T("image\\draw.jpg"), 800, 600, true); // ����ƽ��ͼƬ
			getimage(&imgdback, 115, 450, 40, 40); // ���ذ�ť����
			while (true) {
				mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				if (mouse.x >= 175 && mouse.x <= 395 && mouse.y >= 450 && mouse.y <= 495) {
					if (mouse.mkLButton) { // ���ز˵�
						break;
					}
					else {
						putimage(115, 450, &butd); // ��ʾ��ť
					}
				}
				else {
					putimage(115, 450, &imgdback);
				}
			}
			break;
		}

		turn++;
	}
}
