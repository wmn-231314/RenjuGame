#include "GUI_display.h"
#include "game_display.h"
#include "review_service.h"
#include "web_service.h"

void displayMenu(int board[15][15]) { // ��ʾ�˵�
	MOUSEMSG mous; // �������
	int sound_but1 = 1, sound_but2 = 1; // ��ʼ��������ť

	IMAGE but1,img1,img2,img3,img4,img5,img6,img7;
	loadimage(NULL, _T("image\\bg.jpg")); // ���ر���ͼ
	loadimage(&but1, _T("image\\but1.jpg"), 40, 40, true); // ���ذ�ť
	getimage(&img1, 545, 110, 40, 40); // ��ť�ײ�ͼƬ
	getimage(&img2, 540, 190, 40, 40);
	getimage(&img3, 540, 260, 40, 40);
	getimage(&img4, 540, 335, 40, 40);
	getimage(&img5, 585, 405, 40, 40);
	getimage(&img6, 580, 475, 40, 40);
	getimage(&img7, 580, 525, 40, 40);

	mciSendString("open sounds\\Kongshan.mp3 alias song", NULL, 0, NULL); // ���ر�������
	mciSendString("play song repeat", NULL, 0, NULL); // ���ű�������
	mciSendString("open sounds\\chess.mp3 alias chess", NULL, 0, NULL); // ������Ч

	while (true) {
		mous = GetMouseMsg(); // ��ȡ�����Ϣ
		if (mous.x >= 600 && mous.x <= 770 && mous.y >= 45 && mous.y <= 90) {
			if (mous.mkLButton) {
				disRules(); // ��Ϸ����
				loadimage(NULL, _T("image\\bg.jpg")); // ���¼��ز˵�
			}
			putimage(540, 45, &but1); // ��ʾ��ť
		}
		else {
			putimage(540, 45, &img1); // ���صײ�ͼƬ
		}
		if (mous.x >= 600 && mous.x <= 770 && mous.y >= 120 && mous.y <= 155) {
			if (mous.mkLButton) {
				disStart(board); // ˫����Ϸ
				loadimage(NULL, _T("image\\bg.jpg")); // ���¼��ز˵�
			}
			putimage(545, 110, &but1); // ��ʾ��ť
		}
		else {
			putimage(545, 110, &img1); // ���صײ�ͼƬ
		}
		if (mous.x >= 600 && mous.x <= 770 && mous.y >= 190 && mous.y <= 225) {
			if (mous.mkLButton) {
				disManMashine(board); // �˻���ս
				loadimage(NULL, _T("image\\bg.jpg")); // ���¼��ز˵�
			}
			else {
				putimage(540, 190, &but1); // ��ʾ��ť
			}
		}
		else {
			putimage(540, 190, &img2); // ���صײ�ͼƬ
		}
		if (mous.x >= 600 && mous.x <= 770 && mous.y >= 260 && mous.y <= 295) {
			if (mous.mkLButton) {
				reviewBoard(board); // ��ֻع�
				loadimage(NULL, _T("image\\bg.jpg")); // ���¼��ز˵�
			}
			else {
				putimage(540, 260, &but1); // ��ʾ��ť
			}
		}
		else {
			putimage(540, 260, &img3); // ���صײ�ͼƬ
		}
		if (mous.x >= 615 && mous.x <= 765 && mous.y >= 330 && mous.y <= 380) {
			if (mous.mkLButton) {
				rankList(); // ���а�
				loadimage(NULL, _T("image\\bg.jpg")); // ���¼��ز˵�
			}
			else {
				putimage(555, 330, &but1); // ��ʾ��ť
			}
		}
		else {
			putimage(555, 330, &img4); // ���صײ�ͼƬ
		}
		if (mous.x >= 640 && mous.x <= 725 && mous.y >= 400 && mous.y <= 440) {
			if (mous.mkLButton) {
				disAbout(); // ����
				loadimage(NULL, _T("image\\bg.jpg")); // ���¼��ز˵�
			}
			else {
				putimage(580, 400, &but1); // ��ʾ��ť
			}
		}
		else {
			putimage(580, 400, &img5); // ���صײ�ͼƬ
		}
		if (mous.x >= 640 && mous.x <= 730 && mous.y >= 465 && mous.y <= 505) {
			if (mous.mkLButton) {
				disSet(&sound_but1,&sound_but2); // ����
				loadimage(NULL, _T("image\\bg.jpg")); // ���¼��ز˵�
			}
			else {
				putimage(580, 465, &but1); // ��ʾ��ť
			}
		}
		else {
			putimage(580, 465, &img6); // ���صײ�ͼƬ
		}
		if (mous.x >= 640 && mous.x <= 725 && mous.y >= 525 && mous.y <= 565) {
			if (mous.mkLButton) {
				return; // �˳�
			}
			else {
				putimage(580, 525, &but1); // ��ʾ��ť
			}
		}
		else {
			putimage(580, 525, &img6); // ���صײ�ͼƬ
		}
		FlushMouseMsgBuffer(); // �����껺����
	}

}

void disRules() { // ��ʾ����
	loadimage(NULL, _T("image\\rules.jpg")); // ���ع���ͼƬ
	MOUSEMSG mous;
	while (true) {
		mous = GetMouseMsg();
		if (mous.x >= 650 && mous.x <= 700 && mous.y >= 335 && mous.y <= 550) {
			if (mous.mkLButton) {
				return; // ���ز˵�
			}
		}
	}
}

void disStart(int board[15][15]) { // ��ʾ˫�����
	IMAGE but, img1,img2; // ��������
	MOUSEMSG mouse;

	loadimage(NULL, _T("image\\choice.jpg")); // ����ѡ��ͼƬ
	loadimage(&but,_T("image\\but1.jpg"), 40, 40, true); // ���ذ�ť
	getimage(&img1,30,275,40,40); // ���ذ�ť��ͼ
	getimage(&img2,380,275,40,40);

	while (true) {
		mouse = GetMouseMsg(); // ��ȡ�����Ϣ
		if (mouse.x >= 90 && mouse.x <= 350 && mouse.y >= 270 && mouse.y <= 325) {
			if (mouse.mkLButton) {
				startGame(board); // ��ʼ��Ϸ
				break;
			}
			else {
				putimage(30, 275, &but); // ��ʾ��ť
			}
		}
		else {
			putimage(30, 275, &img1); // ���ص�ͼ
		}
		if (mouse.x >= 450 && mouse.x <= 705 && mouse.y >= 270 && mouse.y <= 325) {
			if (mouse.mkLButton) {
				disChar(board); // ��ʾ��ɫѡ�����
				break;
			}
			else {
				putimage(380, 275, &but); // ��ʾ��ť
			}
		}
		else {
			putimage(380, 275, &img2); // ���ص�ͼ
		}
		if (mouse.x >= 540 && mouse.x <= 750 && mouse.y >= 495 && mouse.y <= 535) {
			if (mouse.mkLButton) {
				return; // ���ز˵�
			}
		}
	}
}

void disChar(int board[15][15]) { // ��ʾ��ɫѡ�����
	SOCKET NewConnection; // ��������
	SOCKET* newC = &NewConnection;
	SOCKET ListeningSocket;
	SOCKET* listenS = &ListeningSocket;
	IMAGE but, img1, img2, img3;
	MOUSEMSG mouse;

	loadimage(NULL, _T("image\\character.jpg")); // ���ؽ�ɫѡ��ͼƬ
	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // ���ذ�ť
	getimage(&img1, 230, 125, 40, 40); // ���ص�ͼ
	getimage(&img2, 465, 125, 40, 40);
	getimage(&img3, 480, 500, 40, 40);

	while (true) {
		mouse = GetMouseMsg(); // ��ȡ�����Ϣ
		if (mouse.x >= 290 && mouse.x <= 410 && mouse.y >= 120 && mouse.y <= 175) {
			if (mouse.mkLButton) {
				setWeb(newC,listenS,0); // ��ʼ�������÷����������ӿͻ���
				loadimage(NULL, _T("image\\board.jpg")); // ˫����ϷͼƬ
				startWebGame(newC,board,0); // ��ʼ������Ϸ
				closeWeb(newC, listenS,0); // �رշ�����
				break;
			}
			else {
				putimage(230, 125, &but); // ��ʾ��ť
			}
		}
		else {
			putimage(230, 125, &img1); // ��ʾ��ͼ
		}
		if (mouse.x >= 525 && mouse.x <= 700 && mouse.y >= 120 && mouse.y <= 175) {
			if (mouse.mkLButton) {
				setWeb(newC,listenS,1); // ��ʼ�������ÿͻ��ˣ����ӷ�����
				loadimage(NULL, _T("image\\board.jpg")); // ˫����ϷͼƬ
				startWebGame(newC,board,1); // ��ʼ������Ϸ
				closeWeb(newC,listenS,1); // �رտͻ���
				break;
			}
			else {
				putimage(465, 125, &but); // ��ʾ��ť
			}
		}
		else {
			putimage(465, 125, &img2); // ��ʾ��ͼ
		}
		if (mouse.x >= 540 && mouse.x <= 750 && mouse.y >= 495 && mouse.y <= 535) {
			if (mouse.mkLButton) {
				return; // ���ز˵�
			}
			else {
				putimage(480, 500, &but); // ��ʾ��ť
			}
		}
		else {
			putimage(480, 500, &img3); // ��ʾ��ͼ
		}
	}

}

void disAbout() { // ��ʾ����
	MOUSEMSG mous; // ��������
	IMAGE but,img;

	loadimage(NULL, _T("image\\about.jpg")); // ����ͼƬ
	loadimage(&but, _T("image\\butabout.jpg"), 40, 40, true); // ��ť
	getimage(&img, 140, 500, 40, 40); // ���ص�ͼ

	while (true) {
		mous = GetMouseMsg(); // ��ȡ�����Ϣ
		if (mous.x >= 200 && mous.x <= 445 && mous.y >= 500 && mous.y <= 550) {
			if (mous.mkLButton) {
				return; // ���ز˵�
			}
			else {
				putimage(140, 500, &but); // ��ʾ��ť
			}
		}
		else {
			putimage(140, 500, &img); // ��ʾ��ͼ
		}
	}
}

void disChess(int line, int row, int bw) { // ��ʾ������������
	IMAGE imgb, imgw; // ��������
	int x, y;

	loadimage(&imgb, _T("image\\chessb1.jpg"), 20, 20, true); // ��������ͼƬ
	loadimage(&imgw, _T("image\\chessw.jpg"), 20, 20, true);

	x = (int)((double)line * 26.5 + 205); // ����������Ͷ��������
	y = (int)((double)row * 26.5 + 105);
	if (bw) { // �жϺڰ�
		putimage(x,y,&imgb); // ��ʾ����
	}
	else {
		putimage(x,y,&imgw); // ��ʾ����
	}
}

void disSave(char name[100]) { // ��ʾ�������
	loadimage(NULL, _T("image\\save.jpg"),800,600,true); // ���ر������
	InputBox(name, 100, NULL, NULL, NULL, 400,0,true); // ��������
}

int disReviewQue(char name[100]) { // �ع������ʾ��������
	int quit = 0; // ��������
	IMAGE but,imgback;
	MOUSEMSG mouse;

	loadimage(NULL, _T("image\\reviewque.jpg"), 800, 600, true); // ���ر������
	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // ���ذ�ť

	while(InputBox(name, 100, NULL, NULL, NULL, 400, 0, false)) {// ��������
		if(strcmp(name, "\0") != 0) { // �Ƚ��Ƿ�Ϊ��
			return quit;
		}
	}
	getimage(&imgback, 390, 420, 40, 40); // ���ص�ͼ
	while (true) {
		mouse = GetMouseMsg(); // ��ȡ�����Ϣ
		if (mouse.x >= 450 && mouse.x <= 695 && mouse.y >= 415 && mouse.y <= 465) {
			if (mouse.mkLButton) {
				quit = 1; // ���ز˵�
				break;
			}
			else {
				putimage(390, 420, &but); // ���ذ�ť
			}
		}
		else {
			putimage(390, 420, &imgback); // ���ص�ͼ
		}
	}
	return quit;
}

void disManMashine(int board[15][15]) { // ��ʾ�˻����
	loadimage(NULL, _T("image\\mm.jpg")); // �����˻�ͼƬ
	manMashine(board); // �˻�
}

void disWinner(int rank,char name[],int turn) { // ��ʾ����
	LOGFONT font;
	gettextstyle(&font); // ����������ָ�ʽ
	font.lfHeight = 55;
	_tcscpy_s(font.lfFaceName, _T("�����п�"));
	settextstyle(&font);
	settextcolor(BLACK);
	setbkcolor(RGB(246, 246, 246));
	setbkmode(TRANSPARENT);

	int x, y;
	char turns[10] = {0};
	int winer_turn = (turn + 1) / 2;
	sprintf_s(turns, "%4d��", winer_turn); // �����������ַ���
	x = 150;

	switch (rank) { // ��������λ����������
		case 1:
			y = 155;
			break;
		case 2:
			y = 240;
			break;
		case 3:
			y = 335;
			break;
		case 4:
			y = 420;
			break;
		case 5:
			y = 505;
			break;
		default:
			fprintf(stderr, "Error!!");
	}
	outtextxy(x, y, name); // �������
	outtextxy(x + 350, y, turns); // �������
}

int disConQue() { // ��ʾ�Ƿ�������
	int answer = 0; // ��������
	IMAGE but, img1, img2;
	MOUSEMSG mouse;

	loadimage(NULL, _T("image\\continueque.jpg")); // �����Ƿ����ͼƬ
	loadimage(&but, _T("image\\but1.jpg"),40,40,true); // ���ذ�ť
	getimage(&img1, 160, 395, 40, 40); // ���ص�ͼ
	getimage(&img2, 480, 395, 40, 40);

	while (true) {
		mouse = GetMouseMsg(); // ��ȡ�����Ϣ
		if (mouse.x >= 220 && mouse.x <= 280 && mouse.y >= 390 && mouse.y <= 455) {
			if (mouse.mkLButton) {
				answer = 1; // ����
				break;
			}
			else {
				putimage(160, 395, &but); // ��ʾ��ť
			}
		}
		else {
			putimage(160, 395, &img1); // ��ʾ��ͼ
		}
		if (mouse.x >= 540&& mouse.x <= 605 && mouse.y >= 390 && mouse.y <= 455) {
			if (mouse.mkLButton) {
				answer = 0; // ������
				break;
			}
			else {
				putimage(480, 395, &but); // ��ʾ��ť
			}
		}
		else {
			putimage(480, 395, &img2); // ��ʾ��ͼ
		}
	}
	return answer; // �����Ƿ������ѡ��
}

void disHint(int bw) { // ��ʾ�ִ���ʾ
	int now,i; // ��������
	IMAGE bg;

	char turnw[] = "image\\animation1\\wturn"; // �ִΰ�
	char turnb[] = "image\\animation1\\bturn"; // �ִκ�
	char paste[] = ".jpg"; // ճ������
	char copyturn[50] = { 0 }; // ���ڸ���ճ�����ַ���
	getimage(&bg, 0, 0, 800, 600); // ��ȡ��ͼ

	if (bw) { // �ж��ִ�
		for (i = 1; i <= 5; i++) {
			sprintf_s(copyturn, "%s%d%s", turnb, i, paste); // ���춯����ַ�ַ���
			loadimage(NULL, _T(copyturn)); // ����ͼƬ
			now = clock(); // wait
			if (i == 1) {
				while (clock() - now < CLOCKS_PER_SEC); // �ȴ�
			}
			else {
				while (clock() - now < CLOCKS_PER_SEC / 4);
			}
		}
	}
	else {
		for (i = 1; i <= 5; i++) {
			sprintf_s(copyturn, "%s%d%s", turnw, i, paste); // ���춯����ַ�ַ���
			loadimage(NULL, _T(copyturn)); // ����ͼƬ
			now = clock(); // wait
			if (i == 1) {
				while (clock() - now < CLOCKS_PER_SEC); // �ȴ�
			}
			else {
				while (clock() - now < CLOCKS_PER_SEC / 4);
			}
		}
	}
	now = clock(); // wait
	while (clock() - now < CLOCKS_PER_SEC);
	putimage(0, 0, &bg); // ���ص�ͼ
}

void disReady() { // ��ʾ��̨׼������
	int now, i; // ��������
	char animation[] = "image\\animation2\\ready"; // ����ͼƬ��ַ
	char waste[] = ".jpg"; // ��ʽ
	char copyturn[50] = { 0 };

	for (i = 1; i <= 4; i++) {
		sprintf_s(copyturn, "%s%d%s", animation, i, waste); // ���춯��ͼƬ��ַ
		loadimage(NULL, _T(copyturn)); // ��ʾͼƬ
		now = clock(); // wait
		while (clock() - now < CLOCKS_PER_SEC/2); // �ȴ�
	}
}

void disSet(int *but1,int *but2) { // ����
	MOUSEMSG mouse; // ��������

	disSetImg(*but1, *but2); // ��ʾͼƬ
	while (true) {
		mouse = GetMouseMsg(); // ��ȡ�����Ϣ
		if (mouse.x >= 230 && mouse.x <= 265 && mouse.y >= 410 && mouse.y <= 450) {
			if (mouse.mkLButton) {
				*but1 = 1; // �������ֿ�
				mciSendString(TEXT("play song repeat"), NULL, NULL, NULL);//��������
				disSetImg(*but1,*but2); // ��ʾͼƬ
			}
		}

		if (mouse.x >= 230 && mouse.x <= 265 && mouse.y >= 510 && mouse.y <= 550) {
			if (mouse.mkLButton) {
				*but1 = 0; // �������ֹ�
				mciSendString(TEXT("pause song"), NULL, 0, NULL); // ֹͣ����
				disSetImg(*but1, *but2); // ��ʾͼƬ
			}
		}

		if (mouse.x >= 445 && mouse.x <= 480 && mouse.y >= 410 && mouse.y <= 450) {
			if (mouse.mkLButton) {
				*but2 = 1; // ������Ч��
				mciSendString("open sounds\\chess1.mp3 alias chess", NULL, 0, NULL); // ����Ч
				disSetImg(*but1, *but2); // ��ʾͼƬ
			}
		}

		if (mouse.x >= 445 && mouse.x <= 480 && mouse.y >= 510 && mouse.y <= 550) {
			if (mouse.mkLButton) {
				*but2 = 0; // ������Ч��
				mciSendString(TEXT("close chess"), NULL, 0, NULL); // �ر���Ч
				disSetImg(*but1, *but2); // ��ʾͼƬ
			}
		}

		if (mouse.x >= 640 && mouse.x <= 690 && mouse.y >= 345 && mouse.y <= 560) {
			if (mouse.mkLButton) {
				break; // �˳�
			}
		}
	}
}

void disSetImg(int but1, int but2) { // ��ʾ����ͼƬ
	if (but1 && but2) { // ���������ص�״̬��ʾ��ǰ����ͼƬ
		loadimage(NULL, _T("image\\setting.jpg"));
	}
	else if (!but1 && !but2) {
		loadimage(NULL, _T("image\\setting1.jpg"));
	}
	else if (!but1 && but2) {
		loadimage(NULL, _T("image\\setting2.jpg"));
	}
	else if (but1 && !but2) {
		loadimage(NULL, _T("image\\setting3.jpg"));

	}
}


