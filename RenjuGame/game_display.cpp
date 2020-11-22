#include "data.h"
#include "game_display.h"
#include "game_service.h"
#include "GUI_display.h"
#include "manmashine_service.h"
#include "web_service.h"



void startGame(int board[15][15]) { // 开始双人游戏
	initial(board); // 初始化数组
	int now; // 声明变量
	int line;
	int row, bw, ans = 0;
	int turn = 1;
	IMAGE but, butd, imgbback, imgbsave, imgwback, imgwsave, imgdback;

	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // 加载按钮
	loadimage(&butd, _T("image\\drawbut.jpg"), 40, 40, true);
	Record* head = loadCurrent(); // 加载当前棋局（保存残局功能）
	Record* tail = head;

	if (tail != NULL) { // 当有残局时
		ans = disConQue(); // 判断是否继续下棋
	}
	loadimage(NULL, _T("image\\board1.jpg")); // 双人游戏图片

	if (ans) { // 继续下棋时
		while (tail != NULL) { // 遍历当前棋局
			board[tail->x][tail->y] = tail->chess; // 将棋局存储在数组中
			if (tail->chess == BLACK_CHESS) { // 判断黑子和白子
				bw = 1;
			}
			else if (tail->chess == WHITE_CHESS) {
				bw = 0;
			}
			disChess(tail->x, tail->y, bw); // 显示已下棋子
			if (tail->next == NULL) { // 将尾指针置于链表末尾
				turn++;
				break;
			}
			tail = tail->next;
			turn++; // 计算下棋次数
		}
		now = clock(); // 等待
		while (clock() - now < CLOCKS_PER_SEC);
		bw = turn % 2; // 计算当前轮次
		disHint(bw); // 显示轮次提示
	}
	else { // 不加载残局
		cleanBoard(head); // 清除残局数据
		tail = NULL; // 将尾指针和头指针都赋值为空
		head = NULL;
	}

	while (true) { // 开始下棋
		int win; // 声明变量
		Record* add;
		MOUSEMSG mouse;
		bw = turn % 2; // 计算当前轮次

		while (true) { // 获取鼠标信息
			mouse = GetMouseMsg();
			if (mouse.x >= 205 && mouse.x <= 590 && mouse.y >= 105 && mouse.y <= 490) {
				if (mouse.mkLButton) {
					line = (mouse.x - 205) / 26; // 转换坐标至数组
					row = (mouse.y - 105) / 26;
					if (board[line][row] == BLANK) { // 下棋
						if (bw) { // 将下棋信息存储到数组中
							board[line][row] = BLACK_CHESS;
						}
						else {
							board[line][row] = WHITE_CHESS;
						}
						FlushMouseMsgBuffer(); // 清空鼠标信息缓冲区
						break;
					}
				}
				
			}
			else if (mouse.x >= 645 && mouse.x <= 755 && mouse.y >= 510 && mouse.y <= 570) {
				if (mouse.mkLButton) { // 返回菜单
					saveCurrent(head,turn); // 保存当前棋局
					return;
				}
			}
		}

		mciSendString(TEXT("seek chess to start"), NULL, 0, NULL); // 下棋音效
		mciSendString(TEXT("play chess"), NULL, 0, NULL);
		disChess(line,row,bw); // 显示棋子在绘图窗口
		win = maxStatus(judgeLine(turn,board), judgeRow(turn,board), judgeSlantR(turn,board), judgeSlantL(turn,board), drawGame(board)); // 判赢

		add = (Record*)malloc(sizeof(Record)); // 储存下棋步骤
		add->x = line; // 将下棋的位置和状态赋值给链表元素
		add->y = row;
		add->chess = board[add->x][add->y];
		if (head == NULL) { // 第一个元素时
			head = add;
			tail = add;
			add->next = NULL;
		}
		else { // 其余元素时，连接链表
			tail->next = add;
			add->next = NULL;
			tail = add;
		}

		if (win == 1) { // 判赢
			now = clock(); // 等待
			while (clock() - now < CLOCKS_PER_SEC);
			FlushMouseMsgBuffer(); // 清空鼠标缓冲区
			if (bw) { // 判断当前轮次
				loadimage(NULL, _T("image\\winb.jpg"), 800, 600, true); // 黑棋获胜
				getimage(&imgbsave, 265, 170, 40, 40); // 用于按钮的背景图
				getimage(&imgbback, 265, 360, 40, 40);
			}
			else {
				loadimage(NULL, _T("image\\winw.jpg"), 800, 600, true); // 白棋获胜
				getimage(&imgwsave, 55, 170, 40, 40); // 用于按钮的背景图
				getimage(&imgwback, 55, 360, 40, 40);
			}
			while (true) {
				mouse = GetMouseMsg(); // 获取鼠标信息
				if (bw) { // 判断轮次
					if (mouse.x >= 325 && mouse.x <= 645 && mouse.y >= 155 && mouse.y <= 225) {
						if (mouse.mkLButton) {
							saveBoard(head, turn); // 选择保存
							break;
						}
						else {
							putimage(265, 170, &but); // 按钮
						}
					}
					else {
						putimage(265, 170, &imgbsave);
					}
					if (mouse.x >= 325 && mouse.x <= 645 && mouse.y >= 360 && mouse.y <= 410) {
						if (mouse.mkLButton) {
							break; // 选择直接回到菜单
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
							saveBoard(head, turn); // 选择保存
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
						if (mouse.mkLButton) { // 选择直接回到菜单
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
			cleanBoard(head); // 清空当前棋盘信息
			break;
		}
		else if (win == 2) { // 平局
			now = clock(); // 等待
			while (clock() - now < CLOCKS_PER_SEC);
			FlushMouseMsgBuffer(); // 清空鼠标缓冲区
			loadimage(NULL, _T("image\\draw.jpg"), 800, 600, true); // 显示平局图片
			getimage(&imgdback, 115, 450, 40, 40); // 按钮背景图
			while (true) {
				mouse = GetMouseMsg(); // 获取鼠标信息
				if (mouse.x >= 175 && mouse.x <= 395 && mouse.y >= 450 && mouse.y <= 495) {
					if (mouse.mkLButton) {
						break; // 返回菜单
					}
					else {
						putimage(115, 450, &butd);
					}
				}
				else {
					putimage(115, 450, &imgdback);
				}
			}
			cleanBoard(head); // 清空当前棋局
			break;
		}
		turn++;
	}
}

void manMashine(int board[15][15]) { // 开始人机对战
	initial(board); // 初始化数组
	int line; // 声明变量
	char row;
	int turn = 1;
	IMAGE but, butd, imgsave, imgback, imgloss, imgdback;

	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // 加载按钮
	loadimage(&butd, _T("image\\drawbut.jpg"), 40, 40, true); // 加载平局按钮

	Chess* pos;
	Record* head = NULL, * tail = NULL;
	int position[15][15] = {0}; // 初始化位置和分数数组（用于机器计算下棋位置）
	int score[15][15] = {0};

	while (true) { // 开始下棋
		int bw, win ,now; // 声明变量
		Record* add;
		MOUSEMSG mouse;
		bw = turn % 2;
		if (bw) { // 判轮次
			while (true) {
				mouse = GetMouseMsg(); // 获取鼠标信息
				if (mouse.x >= 205 && mouse.x <= 590 && mouse.y >= 105 && mouse.y <= 490) {
					if (mouse.mkLButton) {
						line = (mouse.x - 205) / 26; // 转换坐标至数组
						row = (mouse.y - 105) / 26;
						if (board[line][row] == BLANK) { // 判断是否能够落子
							board[line][row] = BLACK_CHESS;
							FlushMouseMsgBuffer(); // 清空鼠标缓冲区
							break;
						}
					}

				}
			}
		}
		else {
			findPos(board,position); // 找棋子周围位置
			nextScore(position,score,board); // 计算位置分数
			pos = maxScore(score); // 最大分数位置
			line = pos->line; // 获得坐标
			row = pos->row;
			board[line][row] = WHITE_CHESS;
		}

		add = (Record*)malloc(sizeof(Record)); // 储存下棋步骤
		add->x = line;
		add->y = row;
		add->chess = board[add->x][add->y];
		if (head == NULL) { // 第一个元素
			head = add;
			tail = add;
			add->next = NULL;
		}
		else { // 其余元素
			tail->next = add;
			add->next = NULL;
			tail = add;
		}

		mciSendString(TEXT("seek chess to start"), NULL, 0, NULL); // 下棋音效
		mciSendString(TEXT("play chess"), NULL, 0, NULL);
		disChess(line, row, bw); // 显示棋子
		win = maxStatus(judgeLine(turn,board), judgeRow(turn,board), judgeSlantR(turn,board), judgeSlantL(turn,board), drawGame(board)); // 判赢

		if (win == 1) { // 胜利
			now = clock(); // 等待
			while (clock() - now < CLOCKS_PER_SEC*2);
			if (bw) { // 判断当前轮次
				loadimage(NULL, _T("image\\mmwin.jpg"), 800, 600, true); // 获胜图片
				getimage(&imgsave, 55, 170, 40, 40);
				getimage(&imgback, 55, 360, 40, 40);

			}
			else {
				loadimage(NULL, _T("image\\mmlose.jpg"), 800, 600, true); // 失败图片
				getimage(&imgloss, 370, 275, 40, 40);
			}
			while (true) {
				mouse = GetMouseMsg(); // 获取鼠标信息
				if (bw) {	 // 判断当前轮次
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 155 && mouse.y <= 225) {
						if (mouse.mkLButton) {
							saveBoard(head, turn); // 保存
							break;
						}
						else {
							putimage(55, 170, &but); // 按钮
						}
						
					}
					else {
						putimage(55, 170, &imgsave);
					}
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 360 && mouse.y <= 410) {
						if (mouse.mkLButton) { // 直接返回
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
						if (mouse.mkLButton) { // 直接返回
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
		else if (win == 2) { // 平局时
			now = clock(); // 等待
			while (clock() - now < CLOCKS_PER_SEC);
			FlushMouseMsgBuffer(); // 清空鼠标缓冲区
			loadimage(NULL, _T("image\\draw.jpg"), 800, 600, true); // 加载平局图片
			getimage(&imgdback, 115, 450, 40, 40);
			while (true) {
				mouse = GetMouseMsg(); // 获取鼠标信息
				if (mouse.x >= 175 && mouse.x <= 395 && mouse.y >= 450 && mouse.y <= 495) {
					if (mouse.mkLButton) { // 返回菜单
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
		turn++; // 轮次增加
	}
}


void rankList() { // 加载并输出排名
	Winer* head = NULL,*search = NULL;
	int i = 0,rank;
	MOUSEMSG mouse;

	while (true) {
		if (i == 0) { // 第一页
			head = loadWiner(); // 加载排名
			search = head;
			loadimage(NULL, _T("image\\rank1.jpg"), 800, 600, true); // 第一页图片
		}
		while (search != NULL) { // 遍历排名链表
			if (i == 5) { // 第二页
				loadimage(NULL, _T("image\\rank2.jpg"), 800, 600, true); // 第二页图片
			}
			i++;
			rank = ((i-1) % 5) + 1;
			disWinner(rank, search->name, search->turns); // 显示排名
			search = search->next;
			if (i % 5 == 0) {
				break;
			}
		}
		while (true) {
			mouse = GetMouseMsg(); // 获取鼠标信息
			if (mouse.mkLButton) {
				if (mouse.x >= 640 && mouse.x <= 750 && mouse.y >= 550 && mouse.y <= 580) {
					if (i > 5) { // 选择下一页
						i = 0;
					}
					break;
				}
				else if (mouse.x >= 600 && mouse.x <= 720 && mouse.y >= 75 && mouse.y <= 120) {
					return; // 返回菜单
				}
				else if (mouse.x >= 60 && mouse.x <= 165 && mouse.y >= 70 && mouse.y <= 125) {
					cleanRank(head); // 清除排名
					i = 0;
					break;
				}
			}
		}
	}
}

void displayWinerB(Winer* win,int board[15][15]) { // 读取并输出回顾棋局
	Record* search; // 声明变量
	int now,bw,winer;

	initial(board); // 初始化棋盘
	search = win->winb; // 读取棋盘数据
	winer = win->turns % 2; // 读取步数

	if (winer) { // 判断获胜者持方
		loadimage(NULL, _T("image\\reviewb.jpg")); // 黑胜
	}
	else {
		loadimage(NULL, _T("image\\revieww.jpg")); // 白胜
	}

	while (search != NULL) { // 回顾棋局
		board[search->x][search->y] = search->chess;
		if (search->chess == BLACK_CHESS) { // 判断当前为黑或白
			bw = 1;
		}
		else {
			bw = 0;
		}
		now = clock(); // wait
		while (clock() - now < CLOCKS_PER_SEC); // 等待时间
		mciSendString(TEXT("seek chess to start"), NULL, 0, NULL); // 下棋音效
		mciSendString(TEXT("play chess"), NULL, 0, NULL);
		disChess(search->x,search->y,bw); // 显示棋局
		search = search->next;
	}
	now = clock(); // 等待
	while (clock() - now < CLOCKS_PER_SEC*2); // 等待展示时间
}

void startWebGame(SOCKET* newC, int board[15][15], int status) { // 开始网络对战
	initial(board); // 初始化数组
	int line; // 声明变量
	int row, bw;
	int turn = 1;
	IMAGE but, butd, imgsave, imgback, imgloss, imgdback;

	loadimage(&but, _T("image\\but1.jpg"), 40, 40, true); // 加载按钮图片
	loadimage(&butd, _T("image\\drawbut.jpg"), 40, 40, true);
	Record* head = NULL, * tail = NULL;

	while (true) {
		int win = 0, now;
		Record* add;
		MOUSEMSG mouse;
		Chess* chess;
		bw = turn % 2;
		if (bw == status) { // 判断下棋轮次（自己下）
			while (true) {
				mouse = GetMouseMsg(); // 获取鼠标信息
				if (mouse.x >= 205 && mouse.x <= 590 && mouse.y >= 105 && mouse.y <= 490) {
					if (mouse.mkLButton) {
						line = (mouse.x - 205) / 26; // 转换坐标
						row = (mouse.y - 105) / 26;
						if (board[line][row] == BLANK) { // 下棋
							if (status) { // 根据持方给数组赋值黑棋或白棋
								board[line][row] = BLACK_CHESS;
							}
							else {
								board[line][row] = WHITE_CHESS;
							}
							FlushMouseMsgBuffer(); // 清空鼠标缓冲区
							break;
						}
					}

				}
			}
			sentChat(newC,line,row); // 发送下棋坐标
		}
		else { // 对方下棋
			chess = receiveChat(newC); // 获取下棋坐标
			line = chess->line; // 行
			row = chess->row; // 列
			if (board[line][row] == BLANK) { // 下棋
				if (!status) { // 根据对方持方赋值黑棋或白棋
					board[line][row] = BLACK_CHESS;
				}
				else {
					board[line][row] = WHITE_CHESS;
				}
				FlushMouseMsgBuffer(); // 清空鼠标缓冲区
			}
		}

		mciSendString(TEXT("seek chess to start"), NULL, 0, NULL); // 下棋音效
		mciSendString(TEXT("play chess"), NULL, 0, NULL);
		disChess(line, row, bw); // 显示棋子
		win = maxStatus(judgeLine(turn, board), judgeRow(turn, board), judgeSlantR(turn, board), judgeSlantL(turn, board), drawGame(board)); // 判赢

		add = (Record*)malloc(sizeof(Record)); // 储存下棋步骤
		add->x = line; // 将当前步骤的坐标和状态赋值给链表元素
		add->y = row;
		add->chess = board[add->x][add->y];
		if (head == NULL) { // 第一个元素
			head = add;
			tail = add;
			add->next = NULL;
		}
		else { // 其余元素
			tail->next = add;
			add->next = NULL;
			tail = add;
		}

		if (win == 1) { // 获胜
			now = clock(); // wait
			while (clock() - now < CLOCKS_PER_SEC * 2); // 等待并展示的时间
			if (bw == status) { // 根据持方来判断输赢
				loadimage(NULL, _T("image\\mmwin.jpg"), 800, 600, true); // 获胜
				getimage(&imgsave, 55, 170, 40, 40); // 加载按钮背景图
				getimage(&imgback, 55, 360, 40, 40);

			}
			else {
				loadimage(NULL, _T("image\\mmlose.jpg"), 800, 600, true); // 输
				getimage(&imgloss, 370, 275, 40, 40);
			}
			while (true) {
				mouse = GetMouseMsg(); // 获取鼠标信息
				if (bw == status) { // 根据持方判断显示界面
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 155 && mouse.y <= 225) {
						if (mouse.mkLButton) {
							saveBoard(head, turn); // 保存
							break;
						}
						else {
							putimage(55, 170, &but); // 显示按钮
						}

					}
					else {
						putimage(55, 170, &imgsave);
					}
					if (mouse.x >= 115 && mouse.x <= 445 && mouse.y >= 360 && mouse.y <= 410) {
						if (mouse.mkLButton) { // 返回菜单
							break;
						}
						else {
							putimage(55, 360, &but); // 显示按钮
						}
					}
					else {
						putimage(55, 360, &imgback);
					}
				}
				else {
					if (mouse.x >= 430 && mouse.x <= 735 && mouse.y >= 265 && mouse.y <= 330) {
						if (mouse.mkLButton) { // 返回菜单
							break;
						}
						else {
							putimage(370, 275, &but); // 显示按钮
						}
					}
					else {
						putimage(370, 275, &imgloss);

					}
				}
			}
			break;
		}
		else if (win == 2) { // 平局
			now = clock(); // wait
			while (clock() - now < CLOCKS_PER_SEC); // 等待并展示的时间
			FlushMouseMsgBuffer(); // 清空鼠标缓冲区
			loadimage(NULL, _T("image\\draw.jpg"), 800, 600, true); // 加载平局图片
			getimage(&imgdback, 115, 450, 40, 40); // 加载按钮背景
			while (true) {
				mouse = GetMouseMsg(); // 获取鼠标信息
				if (mouse.x >= 175 && mouse.x <= 395 && mouse.y >= 450 && mouse.y <= 495) {
					if (mouse.mkLButton) { // 返回菜单
						break;
					}
					else {
						putimage(115, 450, &butd); // 显示按钮
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
