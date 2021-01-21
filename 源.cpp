#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<easyx.h>
#include<conio.h>
#include<graphics.h>
using namespace std;
int board[10][10] = { 0 }, answer[10][10] = { 0 }, key[10][10] = { 0 };
int num_num[10] = { 0 };
int total = 0, life = 3;

void DrawTheBoard();
void fill_in();
bool inMap(int, int);
bool obey_the_rule(int, int, int);
void answer_sodu(int);
void play_game();
void end_the_game();

void DrawTheBoard()
{
	setbkcolor(RGB(238, 239, 255)); //背景颜色
	cleardevice();

	TCHAR name[] = _T("九宫数独");
	settextcolor(RGB(58, 67, 200));
	setbkmode(TRANSPARENT);
	settextstyle(28, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
	outtextxy(175, 40, name);

	// 退出按钮
	setfillcolor(RGB(179, 185, 255)); //按钮颜色
	solidroundrect(440, 30, 480, 50, 3, 3);//退出按钮
	TCHAR exit_game[] = _T("退出");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(16, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
	outtextxy(445, 33, exit_game);


	// 画棋盘格子
	setfillcolor(RGB(255, 255, 255));
	fillroundrect(56, 96, 403, 443, 9, 9);

	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			for (int ii = 0; ii <= 2; ii++)
			{
				for (int jj = 0; jj <= 2; jj++)
				{
					setfillcolor(RGB(215, 218, 255)); //棋盘颜色
					solidroundrect(115 * i + 60 + ii * 37, 115 * j + 37 * jj + 100, 115 * i + 37 * ii + 95, 115 * j + 37 * jj + 135, 5, 5);//画棋盘
				}
			}
		}
	}

	//下方的9个数字选项
	for (int i = -4; i <= 4; i++)
	{
		setfillcolor(RGB(255, 255, 255));
		solidroundrect(212 + 45 * i, 458, 252 + 45 * i, 500, 7, 7);

		setfillcolor(RGB(213, 216, 254)); //棋盘颜色
		if (num_num[i + 5] == 9)
			setfillcolor(RGB(170, 176, 255));
		solidroundrect(214 + 45 * i, 460, 250 + 45 * i, 498, 5, 5);

		settextcolor(RGB(0, 0, 0)); //数字颜色
		setbkmode(TRANSPARENT);
		settextstyle(28, 22, _T("楷体"), 0, 0, 0, 0, 0, 0);
		outtextxy(222 + 45 * i, 466, i + '5');
	}

	TCHAR life_num[] = _T("生命值: ");
	settextcolor(RGB(58, 67, 200));
	setbkmode(TRANSPARENT);
	settextstyle(18, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
	outtextxy(320, 80, life_num);
	outtextxy(390, 80, life + 48);

	fill_in();

	if (life == 0)
	{
		setfillcolor(RGB(227, 228, 255));
		solidroundrect(20, 205, 455, 345, 30, 30);
		setlinecolor(RGB(255, 255, 255));
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
		roundrect(20, 205, 455, 345, 30, 30);
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
		roundrect(13, 198, 462, 352, 37, 37);

		TCHAR gameover1[] = _T("游戏结束");
		TCHAR gameover2[] = _T("你和千亿宝宝一样呆萌");
		settextcolor(RGB(0,0,0));
		setbkmode(TRANSPARENT);
		settextstyle(40, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
		outtextxy(155, 220, gameover1);
		outtextxy(35, 290, gameover2);
		end_the_game();
		closegraph();
		exit(0);
	}
}

void fill_in()
{
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			if (board[i][j])
			{
				int xx1 = (i - 1) / 3, xx2 = (i - 1) % 3, yy1 = (j - 1) / 3, yy2 = (j - 1) % 3;
				settextcolor(RGB(0,0,0)); //数字颜色
				if (!answer[i][j])
					settextcolor(RGB(117, 0, 179));
				settextstyle(25, 21, _T("楷体"), 0, 0, 0, 0, 0, 0);
				setbkmode(TRANSPARENT);
				outtextxy(115 * xx1 + 67 + xx2 * 37, 115 * yy1 + 37 * yy2 + 105, board[i][j] + 48);
			}
		}
	}
}

bool inMap(int x, int y)
{
	if (x > 9 || x < 1)
		return false;
	if (y > 9 || y < 1)
		return false;
	return true;
}

bool obey_the_rule(int x, int y, int n)
{
	for (int i = 1; i <= 9; i++)
		if ((answer[i][y] == n && i != x) || (answer[x][i] == n && i != y))
			return false;

	for (int i = ((x - 1) / 3) * 3 + 1; i <= ((x - 1) / 3 + 1) * 3; i++)
		for (int j = ((y - 1) / 3) * 3 + 1; j <= ((y - 1) / 3 + 1) * 3; j++)
			if (answer[i][j] == n && (i != x || j != y))
				return false;
	return true;
}

void answer_sodu(int s)
{
	if (s == 82)
	{
		for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++)
				key[i][j] = answer[i][j];
		return;
	}

	int x = (s - 1) / 9 + 1, y = s - 9 * (x - 1);

	if (board[x][y])
		answer_sodu(s + 1);
	else
		for (int ans = 1; ans <= 9; ans++)
		{
			if (!obey_the_rule(x, y, ans))
				continue;
			answer[x][y] = ans;
			answer_sodu(s + 1);
			answer[x][y] = 0;
		}
}

void end_the_game()
{
	MOUSEMSG mm, mm0;
	while (true)
	{
		mm = GetMouseMsg();
		if (mm.mkLButton)
		{
			while (true)
			{
				mm0 = GetMouseMsg();
				if (mm0.mkLButton)
					break;
			}
			break;
		}
	}
}

void play_game()
{
	int s_griz = 0;
	int sx = 0, sy = 0;
	for (int cycle = 1; cycle <= 81 - total; cycle++)
	{
		MOUSEMSG mouse;
		
		int nn, find_key = 0;
		while (true)
		{
			mouse = GetMouseMsg();
			
			if (mouse.uMsg && mouse.mkLButton)
			{
				DrawTheBoard();
				int x = mouse.x, y = mouse.y;
				if (y > 456 && y < 502 && x > 30 && x < 436)
				{
					nn = (x + 14) / 45;
					if (s_griz && !board[sx][sy] && sx && sy)
					{
						if (nn == key[sx][sy])
						{
							find_key = 1;
							board[sx][sy] = nn;
							num_num[nn]++;
							DrawTheBoard();
							int xx1 = (sx - 1) / 3, xx2 = (sx - 1) % 3, yy1 = (sy - 1) / 3, yy2 = (sy - 1) % 3;
							settextcolor(RGB(117, 0, 179)); //数字颜色
							settextstyle(25, 21, _T("楷体"), 0, 0, 0, 0, 0, 0);
							setbkmode(TRANSPARENT);
//							outtextxy(115 * xx1 + 67 + xx2 * 37, 115 * yy1 + 37 * yy2 + 105, board[sx][sy] + 48);
						}
						else
						{
							life--;
							DrawTheBoard();
						}
					}
					s_griz = 0;
					
					//选中的数字画框
					setlinecolor(RGB(152, 159, 255));
					roundrect(nn * 45 - 11, 460, nn * 45 + 25, 498, 4, 4);
					for (int i = 1; i <= 9; i++)
					{
						for (int j = 1; j <= 9; j++)
						{
							if (board[i][j] == nn)
							{
								int xx1 = (i - 1) / 3, xx2 = (i - 1) % 3, yy1 = (j - 1) / 3, yy2 = (j - 1) % 3;
								//选中的数字在棋盘中颜色加深
								setfillcolor(RGB(152, 159, 255));
								solidroundrect(115 * xx1 + 60 + xx2 * 37, 115 * yy1 + 37 * yy2 + 100, 115 * xx1 + 37 * xx2 + 95, 115 * yy1 + 37 * yy2 + 135, 5, 5);
								fill_in();
							}
						}
					}

					if (find_key)
						break;
				}

				else if (x > 57 && x < 402 && y > 97 && y < 442)
				{
					DrawTheBoard();
					//计算选中了哪个格子
					int i, j, ii, jj;
					i = (x - 58) / 115;		j = (y - 98) / 115;
					ii = (x - 58 - i * 115) / 38;		jj = (y - 98 - j * 115) / 38;
					sx = 3 * i + ii + 1;		sy = 3 * j + jj + 1;

					if (board[3 * i + ii + 1][3 * j + jj + 1] == 0)
						s_griz = 1;


					for (int k1 = 0; k1 <= 2; k1++)
					{
						for (int k2 = 0; k2 <= 2; k2++)
						{
							//所在宫内格子颜色加深
							setfillcolor(RGB(198, 202, 255));
							solidroundrect(115 * i + 60 + k1 * 37, 115 * j + 37 * k2 + 100, 115 * i + 37 * k1 + 95, 115 * j + 37 * k2 + 135, 5, 5);
							if (board[3 * i + k1 + 1][3 * j + k2 + 1])
							{
								settextcolor(RGB(0, 0, 0));
								settextstyle(25, 21, _T("楷体"), 0, 0, 0, 0, 0, 0);
								setbkmode(TRANSPARENT);
								outtextxy(115 * i + 67 + k1 * 37, 115 * j + 37 * k2 + 105, board[3 * i + k1 + 1][3 * j + k2 + 1] + 48);
							}
							// 所在行格子颜色加深
							setfillcolor(RGB(198, 202, 255));
							solidroundrect(115 * i + 60 + ii * 37, 115 * k1 + 37 * k2 + 100, 115 * i + 37 * ii + 95, 115 * k1 + 37 * k2 + 135, 5, 5);
							if (board[3 * i + ii + 1][3 * k1 + k2 + 1])
							{
								settextcolor(RGB(0, 0, 0));
								settextstyle(25, 21, _T("楷体"), 0, 0, 0, 0, 0, 0);
								setbkmode(TRANSPARENT);
								outtextxy(115 * i + 67 + ii * 37, 115 * k1 + 37 * k2 + 105, board[3 * i + ii + 1][3 * k1 + k2 + 1] + 48);
							}
							// 所在列格子颜色加深
							setfillcolor(RGB(198, 202, 255));
							solidroundrect(115 * k1 + 60 + k2 * 37, 115 * j + 37 * jj + 100, 115 * k1 + 37 * k2 + 95, 115 * j + 37 * jj + 135, 5, 5);
							if (board[3 * k1 + k2 + 1][3 * j + jj + 1])
							{
								settextcolor(RGB(0, 0, 0));
								settextstyle(25, 21, _T("楷体"), 0, 0, 0, 0, 0, 0);
								setbkmode(TRANSPARENT);
								outtextxy(115 * k1 + 67 + k2 * 37, 115 * j + 37 * jj + 105, board[3 * k1 + k2 + 1][3 * j + jj + 1] + 48);
							}
						}
					}

					for (int kx = 1; kx <= 3; kx++)
					{
						for (int ky = 1; ky <= 3; ky++)
						{
							for (int kxx = 1; kxx <= 3; kxx++)
							{
								for (int kyy = 1; kyy <= 3; kyy++)
								{
									if (board[3 * kx + kxx - 3][3 * ky + kyy - 3] == board[3 * i + ii + 1][3 * j + jj + 1] && board[3 * i + ii + 1][3 * j + jj + 1])
									{
										setfillcolor(RGB(163, 170, 255));
										solidroundrect(115 * (kx - 1) + 60 + (kxx - 1) * 37, 115 * (ky - 1) + 37 * (kyy - 1) + 100, 115 * (kx - 1) + 37 * (kxx - 1) + 95, 115 * (ky - 1) + 37 * (kyy - 1) + 135, 5, 5);
										settextcolor(RGB(0, 0, 0));
										settextstyle(25, 21, _T("楷体"), 0, 0, 0, 0, 0, 0);
										setbkmode(TRANSPARENT);
										outtextxy(115 * (kx - 1) + 67 + (kxx - 1) * 37, 115 * (ky - 1) + 37 * (kyy - 1) + 105, board[3 * i + ii + 1][3 * j + jj + 1] + 48);
									}
								}
							}
						}
					}

					// 选中格子颜色加深
					setfillcolor(RGB(152, 159, 255));
					solidroundrect(115 * i + 60 + ii * 37, 115 * j + 37 * jj + 100, 115 * i + 37 * ii + 95, 115 * j + 37 * jj + 135, 5, 5);
					if (board[3 * i + ii + 1][3 * j + jj + 1])
					{
						settextcolor(RGB(0, 0, 0));
						settextstyle(25, 21, _T("楷体"), 0, 0, 0, 0, 0, 0);
						setbkmode(TRANSPARENT);
						outtextxy(115 * i + 67 + ii * 37, 115 * j + 37 * jj + 105, board[3 * i + ii + 1][3 * j + jj + 1] + 48);
					}
				}

				else if (x >= 429 && x <= 481 && y >= 29 && y <= 51)
				{
					cleardevice();
					TCHAR the_last[] = _T("单击一次退出程序");
					settextcolor(RGB(58, 67, 200));
					setbkmode(TRANSPARENT);
					settextstyle(28, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
					outtextxy(130, 180, the_last);

					end_the_game();
					closegraph();
					exit(0);
				}
				
				fill_in();
				//_getch();
			}
		}

	}

	setfillcolor(RGB(227, 228, 255));
	solidroundrect(20, 205, 455, 345, 30, 30);
	setlinecolor(RGB(255, 255, 255));
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
	roundrect(20, 205, 455, 345, 30, 30);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
	roundrect(13, 198, 462, 352, 37, 37);

	TCHAR gameover1[] = _T("恭喜获胜");
	TCHAR gameover2[] = _T("你和思哲宝宝一样聪明");
	settextcolor(RGB(0, 0, 0));
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
	outtextxy(155, 220, gameover1);
	outtextxy(35, 290, gameover2);
	
	end_the_game();
	closegraph();
	exit(0);
}

int main()
{
	initgraph(500, 550);
	setbkcolor(RGB(238, 239, 255)); //背景颜色
	cleardevice();

	//开始界面
	TCHAR start[] = _T("九宫数独");
	settextcolor(RGB(58, 67, 200));
	setbkmode(TRANSPARENT);
	settextstyle(52, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
	outtextxy(135, 150, start);

	setfillcolor(RGB(227, 228, 255));
	solidroundrect(180, 360, 320, 420, 10, 10);

	TCHAR start2[] = _T("进入游戏");
	settextcolor(RGB(58, 67, 200));
	setbkmode(TRANSPARENT);
	settextstyle(28, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
	outtextxy(195, 375, start2);

	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg();
		if (mouse.mkLButton && mouse.x >= 180 && mouse.x <= 320 && mouse.y <= 420 && mouse.y >= 360)
			break;
	}

	//难度选择界面
	cleardevice();
	TCHAR choose[] = _T("请选择难度");
	settextcolor(RGB(58, 67, 200));
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
	outtextxy(150, 120, choose);

	//难度选择按钮
	setfillcolor(RGB(227, 228, 255));
	fillroundrect(190, 200, 310, 250, 5, 5);
	fillroundrect(190, 270, 310, 320, 5, 5);
	fillroundrect(190, 340, 310, 390, 5, 5);
	fillroundrect(190, 410, 310, 460, 5, 5);

	//难度选择文字
	TCHAR select1[] = _T("简单");
	TCHAR select2[] = _T("中等");
	TCHAR select3[] = _T("困难");
	TCHAR select4[] = _T("专家");
	settextcolor(RGB(58, 67, 200));
	setbkmode(TRANSPARENT);
	settextstyle(28, 0, _T("楷体"), 0, 0, 0, 0, 0, 0);
	outtextxy(223, 212, select1);
	outtextxy(223, 282, select2);
	outtextxy(223, 352, select3);
	outtextxy(223, 422, select4);

	mouse = GetMouseMsg();
	mouse = GetMouseMsg();
	srand(time(0));
	int choice = rand() % 10 + 1;

	while (true)
	{
		mouse = GetMouseMsg();
		if (mouse.mkLButton)
		{
			if (mouse.x >= 190 && mouse.x <= 310 && mouse.y >= 200 && mouse.y <= 250)
			{
				ifstream fin("question_1.txt");
				int read;
				while (fin >> read)
				{
					if (read == choice + 100)
						break;
				}
				for (int i = 1; i <= 9; i++)
					for (int j = 1; j <= 9; j++)
					{
						fin >> board[i][j];
						answer[i][j] = board[i][j];
						if (board[i][j])
						{
							total++;
							num_num[board[i][j]]++;
						}
					}
				fin.close();
			}
			if (mouse.x >= 190 && mouse.x <= 310 && mouse.y >= 270 && mouse.y <= 320)
			{
				ifstream fin("question_2.txt");
				int read;
				while (fin >> read)
				{
					if (read == choice + 200)
						break;
				}
				for (int i = 1; i <= 9; i++)
					for (int j = 1; j <= 9; j++)
					{
						fin >> board[i][j];
						answer[i][j] = board[i][j];
						if (board[i][j])
						{
							total++;
							num_num[board[i][j]]++;
						}
					}
				fin.close();
			}
			if (mouse.x >= 190 && mouse.x <= 310 && mouse.y >= 340 && mouse.y <= 390)
			{
				ifstream fin("question_3.txt");
				int read;
				while (fin >> read)
				{
					if (read == choice + 300)
						break;
				}
				for (int i = 1; i <= 9; i++)
					for (int j = 1; j <= 9; j++)
					{
						fin >> board[i][j];
						answer[i][j] = board[i][j];
						if (board[i][j])
						{
							total++;
							num_num[board[i][j]]++;
						}
					}
				fin.close();
			}
			if (mouse.x >= 190 && mouse.x <= 310 && mouse.y >= 410 && mouse.y <= 460)
			{
				ifstream fin("question_4.txt");
				int read;
				while (fin >> read)
				{
					if (read == choice + 400)
						break;
				}
				for (int i = 1; i <= 9; i++)
					for (int j = 1; j <= 9; j++)
					{
						fin >> board[i][j];
						answer[i][j] = board[i][j];
						if (board[i][j])
						{
							total++;
							num_num[board[i][j]]++;
						}
					}
				fin.close();
			}
			break;
		}
	}

	DrawTheBoard();
	answer_sodu(1);
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			answer[i][j] = board[i][j];
	play_game();
	return 0;
}