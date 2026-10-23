#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void createWall(); // 创建迷宫外墙
void createMaze(); // 创建随机迷宫
int visit(int row2, int col2);
void printMaze(); // 打印迷宫
void printLegend(); // 打印图例

int startI = 1, startJ = 1; // 入口起点
int endI = NULL, endJ = NULL; // 出口终点（待定）
bool success = false;

// 迷宫矩阵，2代表墙壁，0代表通道
int maze[100][100];
int row = 0;
int col = 0;

// ===== 显示用符号：每个格子占 2 个字符宽，这样迷宫看起来才是正方形的 =====
const char* const SYM_WALL = "██"; // 墙壁
const char* const SYM_EMPTY = "  "; // 通道
const char* const SYM_PATH = "▓▓"; // 已搜索到的路径
const char* const SYM_START = "起"; // 起点
const char* const SYM_END = "终"; // 终点

// ===== 显示用颜色：Windows 控制台前景色，可用 | 叠加 =====
const WORD COLOR_DEFAULT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // 灰白色（控制台默认色）
const WORD COLOR_WALL = FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 亮蓝色
const WORD COLOR_PATH = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 亮黄色
const WORD COLOR_START = FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 亮绿色
const WORD COLOR_END = FOREGROUND_RED | FOREGROUND_INTENSITY; // 亮红色

// 创建迷宫外墙
void createWall()
{
	// 第一行、第一列、最后一行、最后一列均为墙壁
	for (int i = 0; i < col; i++) // 第一行
		maze[0][i] = 2;
	for (int i = 1; i < row; i++) // 第一列
		maze[i][0] = 2;
	for (int i = 1; i < col; i++) // 最后一行
		maze[row - 1][i] = 2;
	for (int i = 1; i < row; i++) // 最后一列
		maze[i][col - 1] = 2;
}

// 创建随机迷宫
void createMaze()
{
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < col - 1; j++)
		{
			if ((rand() % 100 + 1) % 4 == 0)
				maze[i][j] = 2;
			else
				maze[i][j] = 0;
		}
	}
	maze[1][1] = 0;
	maze[row - 2][col - 2] = 0;
}

int visit(int row2, int col2)
{
	int endI = row - 2, endJ = col - 2; // 出口
	// 该点走过，标记为1
	maze[row2][col2] = 1;

	// 走到终点，成功
	if (row2 == endI && col2 == endJ)
		success = true;

	// 向四个方向递归调用函数visit()
	if (!success && maze[row2][col2 + 1] == 0)
		visit(row2, col2 + 1);
	if (!success && maze[row2 + 1][col2] == 0)
		visit(row2 + 1, col2);
	if (!success && maze[row2][col2 - 1] == 0)
		visit(row2, col2 - 1);
	if (!success && maze[row2 - 1][col2] == 0)
		visit(row2 - 1, col2);

	// 该点走过，但没成功，则该点重新置为0
	if (!success)
		maze[row2][col2] = 0;

	return success;
}

// 设置后续输出所用的文字颜色
void setColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 以指定颜色打印一个格子，打印后恢复默认颜色
void printCell(const char* symbol, WORD color)
{
	setColor(color);
	printf("%s", symbol);
	setColor(COLOR_DEFAULT);
}

// 打印图例，说明各符号的含义
void printLegend()
{
	printf("图例：");
	printCell(SYM_WALL, COLOR_WALL);
	printf("墙壁  ");
	printCell(SYM_PATH, COLOR_PATH);
	printf("路径  ");
	printCell(SYM_START, COLOR_START);
	printf("起点  ");
	printCell(SYM_END, COLOR_END);
	printf("终点\n\n");
}

// 打印迷宫：墙壁、路径、起点、终点分色显示
void printMaze()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == startI && j == startJ)
				printCell(SYM_START, COLOR_START);
			else if (i == row - 2 && j == col - 2)
				printCell(SYM_END, COLOR_END);
			else if (maze[i][j] == 2)
				printCell(SYM_WALL, COLOR_WALL);
			else if (maze[i][j] == 1)
				printCell(SYM_PATH, COLOR_PATH);
			else
				printCell(SYM_EMPTY, COLOR_DEFAULT);
		}
		printf("\n");
	}
}

int main(void)
{
	int seed;

	printf("请输入迷宫行数 row (0<row<100)：");
	scanf_s("%d", &row);
	printf("请输入迷宫列数 col (0<col<100)：");
	scanf_s("%d", &col);
	printf("请输入迷宫随机种子：");
	scanf_s("%d", &seed);

	createWall();
	createMaze();
	srand(seed);

	printf("\n显示迷宫：\n");
	printLegend();
	printMaze();

	if (visit(startI, startJ) == 0)
	{
		printf("\n没有找到出口！\n");
	}
	else
	{
		printf("\n显示路径：\n");
		printMaze();
	}

	system("pause");

	return 0;
}
