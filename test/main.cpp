#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>

int main() {
	initgraph(800, 600);
	loadimage(NULL, _T("C://Users/jenny/Desktop/shstudy/mmlose.jpg"));
	initgraph(800, 600);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			setfillcolor(RED);
			solidcircle(m.x, m.y, 20);
			break;
		case WM_RBUTTONDOWN:
			setfillcolor(RGB(255, 0, 255));
			solidellipse(m.x - 40, m.y - 20, m.x + 40, m.y + 20);
			break;
		case WM_MOUSEMOVE:
			char s[12];
			loadimage(NULL, _T("C://Users/jenny/Desktop/shstudy/setting.jpg"));
			//setfillcolor(BLACK);//黑色矩形覆盖上次坐标记录
			//solidrectangle(0, 0, 75, 20);
			sprintf(s, "[%d,%d]", m.x, m.y);
			outtextxy(0, 0, s);
		}
	}

	getchar();
	closegraph();
	return 0;

}
