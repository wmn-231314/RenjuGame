#include "GUI_display.h"
#include "game_display.h"
#include "review_service.h"
#include "web_service.h"

void displayMenu(int board[15][15]) { // 显示菜单
	MOUSEMSG mous; // 声明鼠标
	int sound_but1 = 1, sound_but2 = 1; // 初始化声音按钮

	IMAGE but1,img1,img2,img3,img4,img5,img6,img7;
	loadimage(NULL, _T("image\\bg.jpg")); // 加载背景图
	loadimage(&but1, _T("image\\but1.jpg"), 40, 40, true); // 加载按钮
	getimage(&img1, 545, 110, 40, 40); // 按钮底部图片
	getimage(&img2, 540, 190, 40, 40);
	getimage(&img3, 540, 260, 40, 40);
	getimage(&img4, 540, 335, 40, 40);
	getimage(&img5, 585, 405, 40, 40);
	getimage(&img6, 580, 475, 40, 40);
	getimage(&img7, 580, 525, 40, 40);

	mciSendString("open sounds\\Kongshan.mp3 alias song", NULL, 0, NULL); // 加载背景音乐
	mciSendString("play song repeat", NULL, 0, NULL); // 播放背景音乐
	mciSendString("open sounds\\chess.mp3 alias chess", NULL, 0, NULL); // 加载音效

	while (true) {
		mous = GetMouseMsg(); // 获取鼠标信息
		if (mous.x >= 600 && mous.x <= 770 && mous.y >= 45 && mous.y <= 90) {
			if (mous.mkLButton) {
				disRules(); // 游戏规则
				loadimage(NULL, _T("image\\bg.jpg")); // 重新加载菜单
			}
			putimage(540, 45, &but1); // 显示按钮
		}
		else {
			putimage(540, 45, &img1); // 重载底部图片
		}
		if (mous.x >= 600 && mous.x <= 770 && mous.y >= 120 && mous.y <= 155) {
			if (mous.mkLButton) {
				disStart(board); // 双人游戏
				loadimage(NULL, _T("image\\bg.jpg")); // 重新加载菜单
			}
			putimage(545, 110, &but1); // 显示按钮
		}
		else {
			putimage(545, 110, &img1); // 重载底部图片
		}
		if (mous.x >= 600 && mous.x <= 770 && mous.y >= 190 && mous.y <= 225) {
			if (mous.mkLButton) {
				disManMashine(board); // 人机对战
				loadimage(NULL, _T("image\\bg.jpg")); // 重新加载菜单
			}
			else {
				putimage(540, 190, &but1); // 显示按钮
			}
		}
		else {
			putimage(540, 190, &img2); // 重载底部图片
		}
		if (mous.x >= 600 && mous.x <= 770 && mous.y >= 260 && mous.y <= 295) {
			if (mous.mkLButton) {
				reviewBoard(board); // 棋局回顾
				loadimage(NULL, _T("image\\bg.jpg")); // 重新加载菜单
			}
			else {
				putimage(540, 260, &but1); // 显示按钮
			}
		}
		else {
			putimage(540, 260, &img3); // 重载底部图片
		}
		if (mous.x >= 615 && mous.x <= 765 && mous.y >= 330 && mous.y <= 380) {
			if (mous.mkLButton) {
				rankList(); // 排行榜
				loadimage(NULL, _T("image\\bg.jpg")); // 重新加载菜单
			}
			else {
				putimage(555, 330, &but1); // 显示按钮
			}
		}
		else {
			putimage(555, 330, &img4); // 重载底部图片
		}
		if (mous.x >= 640 && mous.x <= 725 && mous.y >= 400 && mous.y <= 440) {
			if (mous.mkLButton) {
				disAbout(); // 关于
				loadimage(NULL, _T("image\\bg.jpg")); // 重新加载菜单
			}
			else {
				putimage(580, 400, &but1); // 显示按钮
			}
		}
		else {
			putimage(580, 400, &img5); // 重载底部图片
		}
		if (mous.x >= 640 && mous.x <= 730 && mous.y >= 465 && mous.y <= 505) {
			if (mous.mkLButton) {
				disSet(&sound_but1,&sound_but2); // 设置
				loadimage(NULL, _T("image\\bg.jpg")); // 重新加载菜单
			}
			else {
				putimage(580, 465, &but1); // 显示按钮
			}
		}
		else {
			putimage(580, 465, &img6); // 重载底部图片
		}
		if (mous.x >= 640 && mous.x <= 725 && mous.y >= 525 && mous.y <= 565) {
			if (mous.mkLButton) {
				return; // 退出
			}
			else {
				putimage(580, 525, &but1); // 显示按钮
			}
		}
		else {
			putimage(580, 525, &img6); // 重载底部图片
		}
		FlushMouseMsgBuffer(); // 清空鼠标缓冲区
	}

}

void disRules() { // 显示规则
	loadimage(NULL, _T("image\\rules.jpg")); // 加载规则图片
	MOUSEMSG mous;
	while (true) {
		mous = GetMouseMsg();
		if (mous.x >= 650 && mous.x <= 700 && mous.y >= 335 && mous.y <= 550) {
			if (mous.mkLButton) {
				return; // 返回菜单
			}
		}
	}
}

void disStart(int board[15][15]) { // 显示双人棋局
	IMAGE but, img1,img2; // 声明变量
	MOUSEMSG mouse;

	loadimage(NULL, _T("image\\choice.jpg")); // 加载选择图片
	loadimage(&but,_T("image\\but1.jpg"), 40, 40, true); // 加载按钮
	getimage(&img1,30,275,40,40); // 加载按钮底图
	getimage(&img2,380,275,40,40);

	while (true) {
		mouse = GetMouseMsg(); // 获取鼠标信息
		if (mouse.x >= 90 && mouse.x <= 350 && mouse.y >= 270 && mouse.y <= 325) {
			if (mouse.mkLButton) {
				startGame(board); // 开始游戏
				break;
			}
			else {
				putimage(30, 275, &but); // 显示按钮
			}
		}
		else {
			putimage(30, 275, &img1); // 重载底图
		}
		if (mouse.x >= 450 && mouse.x <= 705 && mouse.y >= 270 && mouse.y <= 325) {
			if (mouse.mkLButton) {
				disChar(board); // 显示角色选择界面
				break;
			}
			else {
				putimage(380, 275, &but); // 显示按钮
			}
		}
		else {
			putimage(380, 275, &img2); // 重载底图
		}
		if (mouse.x >= 540 && mouse.x <= 750 && mouse.y >= 495 && mouse.y <= 535) {
			if (mouse.mkLButton) {
				return; // 返回菜单
			}
		}
	}
}

void disChar(int board[15][15]) { // 显示角色选择界面
	SOCKET NewConnection; // 声明变量
	SOCKET* newC = &NewConnection;
	SOCKET ListeningSocket;
	SOCKET* listenS = &ListeningSocket;
	IMAGE but, img1, img2, img3;
	MOUSEMSG mouse;

	loadimage(NULL, _T("image\\character.jpg")); // 加载角色选择图片
	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // 加载按钮
	getimage(&img1, 230, 125, 40, 40); // 加载底图
	getimage(&img2, 465, 125, 40, 40);
	getimage(&img3, 480, 500, 40, 40);

	while (true) {
		mouse = GetMouseMsg(); // 获取鼠标信息
		if (mouse.x >= 290 && mouse.x <= 410 && mouse.y >= 120 && mouse.y <= 175) {
			if (mouse.mkLButton) {
				setWeb(newC,listenS,0); // 初始化并设置服务器，连接客户端
				loadimage(NULL, _T("image\\board.jpg")); // 双人游戏图片
				startWebGame(newC,board,0); // 开始网络游戏
				closeWeb(newC, listenS,0); // 关闭服务器
				break;
			}
			else {
				putimage(230, 125, &but); // 显示按钮
			}
		}
		else {
			putimage(230, 125, &img1); // 显示底图
		}
		if (mouse.x >= 525 && mouse.x <= 700 && mouse.y >= 120 && mouse.y <= 175) {
			if (mouse.mkLButton) {
				setWeb(newC,listenS,1); // 初始化并设置客户端，连接服务器
				loadimage(NULL, _T("image\\board.jpg")); // 双人游戏图片
				startWebGame(newC,board,1); // 开始网络游戏
				closeWeb(newC,listenS,1); // 关闭客户端
				break;
			}
			else {
				putimage(465, 125, &but); // 显示按钮
			}
		}
		else {
			putimage(465, 125, &img2); // 显示底图
		}
		if (mouse.x >= 540 && mouse.x <= 750 && mouse.y >= 495 && mouse.y <= 535) {
			if (mouse.mkLButton) {
				return; // 返回菜单
			}
			else {
				putimage(480, 500, &but); // 显示按钮
			}
		}
		else {
			putimage(480, 500, &img3); // 显示底图
		}
	}

}

void disAbout() { // 显示关于
	MOUSEMSG mous; // 声明变量
	IMAGE but,img;

	loadimage(NULL, _T("image\\about.jpg")); // 关于图片
	loadimage(&but, _T("image\\butabout.jpg"), 40, 40, true); // 按钮
	getimage(&img, 140, 500, 40, 40); // 加载底图

	while (true) {
		mous = GetMouseMsg(); // 获取鼠标信息
		if (mous.x >= 200 && mous.x <= 445 && mous.y >= 500 && mous.y <= 550) {
			if (mous.mkLButton) {
				return; // 返回菜单
			}
			else {
				putimage(140, 500, &but); // 显示按钮
			}
		}
		else {
			putimage(140, 500, &img); // 显示底图
		}
	}
}

void disChess(int line, int row, int bw) { // 显示棋子在棋盘上
	IMAGE imgb, imgw; // 声明变量
	int x, y;

	loadimage(&imgb, _T("image\\chessb1.jpg"), 20, 20, true); // 加载棋子图片
	loadimage(&imgw, _T("image\\chessw.jpg"), 20, 20, true);

	x = (int)((double)line * 26.5 + 205); // 将界面坐标投射至数组
	y = (int)((double)row * 26.5 + 105);
	if (bw) { // 判断黑白
		putimage(x,y,&imgb); // 显示黑棋
	}
	else {
		putimage(x,y,&imgw); // 显示白棋
	}
}

void disSave(char name[100]) { // 显示保存界面
	loadimage(NULL, _T("image\\save.jpg"),800,600,true); // 加载保存界面
	InputBox(name, 100, NULL, NULL, NULL, 400,0,true); // 输入姓名
}

int disReviewQue(char name[100]) { // 回顾棋局显示搜索界面
	int quit = 0; // 声明变量
	IMAGE but,imgback;
	MOUSEMSG mouse;

	loadimage(NULL, _T("image\\reviewque.jpg"), 800, 600, true); // 加载保存界面
	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // 加载按钮

	while(InputBox(name, 100, NULL, NULL, NULL, 400, 0, false)) {// 输入姓名
		if(strcmp(name, "\0") != 0) { // 比较是否为空
			return quit;
		}
	}
	getimage(&imgback, 390, 420, 40, 40); // 加载底图
	while (true) {
		mouse = GetMouseMsg(); // 获取鼠标信息
		if (mouse.x >= 450 && mouse.x <= 695 && mouse.y >= 415 && mouse.y <= 465) {
			if (mouse.mkLButton) {
				quit = 1; // 返回菜单
				break;
			}
			else {
				putimage(390, 420, &but); // 加载按钮
			}
		}
		else {
			putimage(390, 420, &imgback); // 加载底图
		}
	}
	return quit;
}

void disManMashine(int board[15][15]) { // 显示人机棋局
	loadimage(NULL, _T("image\\mm.jpg")); // 加载人机图片
	manMashine(board); // 人机
}

void disWinner(int rank,char name[],int turn) { // 显示排名
	LOGFONT font;
	gettextstyle(&font); // 设置输出文字格式
	font.lfHeight = 55;
	_tcscpy_s(font.lfFaceName, _T("华文行楷"));
	settextstyle(&font);
	settextcolor(BLACK);
	setbkcolor(RGB(246, 246, 246));
	setbkmode(TRANSPARENT);

	int x, y;
	char turns[10] = {0};
	int winer_turn = (turn + 1) / 2;
	sprintf_s(turns, "%4d步", winer_turn); // 创建步数的字符串
	x = 150;

	switch (rank) { // 按排名的位置设置坐标
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
	outtextxy(x, y, name); // 输出姓名
	outtextxy(x + 350, y, turns); // 输出步数
}

int disConQue() { // 显示是否继续棋局
	int answer = 0; // 声明变量
	IMAGE but, img1, img2;
	MOUSEMSG mouse;

	loadimage(NULL, _T("image\\continueque.jpg")); // 加载是否继续图片
	loadimage(&but, _T("image\\but1.jpg"),40,40,true); // 加载按钮
	getimage(&img1, 160, 395, 40, 40); // 加载底图
	getimage(&img2, 480, 395, 40, 40);

	while (true) {
		mouse = GetMouseMsg(); // 获取鼠标信息
		if (mouse.x >= 220 && mouse.x <= 280 && mouse.y >= 390 && mouse.y <= 455) {
			if (mouse.mkLButton) {
				answer = 1; // 继续
				break;
			}
			else {
				putimage(160, 395, &but); // 显示按钮
			}
		}
		else {
			putimage(160, 395, &img1); // 显示底图
		}
		if (mouse.x >= 540&& mouse.x <= 605 && mouse.y >= 390 && mouse.y <= 455) {
			if (mouse.mkLButton) {
				answer = 0; // 不继续
				break;
			}
			else {
				putimage(480, 395, &but); // 显示按钮
			}
		}
		else {
			putimage(480, 395, &img2); // 显示底图
		}
	}
	return answer; // 返回是否继续的选择
}

void disHint(int bw) { // 显示轮次提示
	int now,i; // 声明变量
	IMAGE bg;

	char turnw[] = "image\\animation1\\wturn"; // 轮次白
	char turnb[] = "image\\animation1\\bturn"; // 轮次黑
	char paste[] = ".jpg"; // 粘贴部分
	char copyturn[50] = { 0 }; // 用于复制粘贴的字符串
	getimage(&bg, 0, 0, 800, 600); // 获取底图

	if (bw) { // 判断轮次
		for (i = 1; i <= 5; i++) {
			sprintf_s(copyturn, "%s%d%s", turnb, i, paste); // 构造动画地址字符串
			loadimage(NULL, _T(copyturn)); // 加载图片
			now = clock(); // wait
			if (i == 1) {
				while (clock() - now < CLOCKS_PER_SEC); // 等待
			}
			else {
				while (clock() - now < CLOCKS_PER_SEC / 4);
			}
		}
	}
	else {
		for (i = 1; i <= 5; i++) {
			sprintf_s(copyturn, "%s%d%s", turnw, i, paste); // 构造动画地址字符串
			loadimage(NULL, _T(copyturn)); // 加载图片
			now = clock(); // wait
			if (i == 1) {
				while (clock() - now < CLOCKS_PER_SEC); // 等待
			}
			else {
				while (clock() - now < CLOCKS_PER_SEC / 4);
			}
		}
	}
	now = clock(); // wait
	while (clock() - now < CLOCKS_PER_SEC);
	putimage(0, 0, &bg); // 重载底图
}

void disReady() { // 显示擂台准备动画
	int now, i; // 声明变量
	char animation[] = "image\\animation2\\ready"; // 动画图片地址
	char waste[] = ".jpg"; // 格式
	char copyturn[50] = { 0 };

	for (i = 1; i <= 4; i++) {
		sprintf_s(copyturn, "%s%d%s", animation, i, waste); // 构造动画图片地址
		loadimage(NULL, _T(copyturn)); // 显示图片
		now = clock(); // wait
		while (clock() - now < CLOCKS_PER_SEC/2); // 等待
	}
}

void disSet(int *but1,int *but2) { // 设置
	MOUSEMSG mouse; // 声明变量

	disSetImg(*but1, *but2); // 显示图片
	while (true) {
		mouse = GetMouseMsg(); // 获取鼠标信息
		if (mouse.x >= 230 && mouse.x <= 265 && mouse.y >= 410 && mouse.y <= 450) {
			if (mouse.mkLButton) {
				*but1 = 1; // 背景音乐开
				mciSendString(TEXT("play song repeat"), NULL, NULL, NULL);//播放音乐
				disSetImg(*but1,*but2); // 显示图片
			}
		}

		if (mouse.x >= 230 && mouse.x <= 265 && mouse.y >= 510 && mouse.y <= 550) {
			if (mouse.mkLButton) {
				*but1 = 0; // 背景音乐关
				mciSendString(TEXT("pause song"), NULL, 0, NULL); // 停止音乐
				disSetImg(*but1, *but2); // 显示图片
			}
		}

		if (mouse.x >= 445 && mouse.x <= 480 && mouse.y >= 410 && mouse.y <= 450) {
			if (mouse.mkLButton) {
				*but2 = 1; // 下棋音效开
				mciSendString("open sounds\\chess1.mp3 alias chess", NULL, 0, NULL); // 打开音效
				disSetImg(*but1, *but2); // 显示图片
			}
		}

		if (mouse.x >= 445 && mouse.x <= 480 && mouse.y >= 510 && mouse.y <= 550) {
			if (mouse.mkLButton) {
				*but2 = 0; // 下棋音效关
				mciSendString(TEXT("close chess"), NULL, 0, NULL); // 关闭音效
				disSetImg(*but1, *but2); // 显示图片
			}
		}

		if (mouse.x >= 640 && mouse.x <= 690 && mouse.y >= 345 && mouse.y <= 560) {
			if (mouse.mkLButton) {
				break; // 退出
			}
		}
	}
}

void disSetImg(int but1, int but2) { // 显示设置图片
	if (but1 && but2) { // 根据两开关的状态显示当前设置图片
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


