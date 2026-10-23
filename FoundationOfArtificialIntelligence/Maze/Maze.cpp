#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <windows.h>

// 代价函数选择预设
// 1=曼哈顿距离，2=欧几里得距离
#define COST_FUNCTION 1

void createWall(); // 创建迷宫外墙
void createMaze(); // 创建随机迷宫
void printMaze(); // 打印迷宫
void printLegend(); // 打印图例
bool aStar(); // A* 搜索

int startI = 1, startJ = 1; // 入口起点
int endI = 0, endJ = 0; // 出口终点（待定）

// 迷宫矩阵，2代表墙壁，0代表通道
int maze[100][100];
int row = 0;
int col = 0;

// 打印用符号
const char* const SYM_WALL = "█"; // 墙壁
const char* const SYM_EMPTY = " "; // 通道
const char* const SYM_PATH = "+"; // 最终路径
const char* const SYM_OPEN = "O"; // Open 表节点
const char* const SYM_CLOSED = "C"; // Closed 表节点

// 打印用颜色（Windows 控制台属性字：低 4 位为前景的 蓝/绿/红/强度，高 4 位为背景的 蓝/绿/红/强度）
const WORD COLOR_DEFAULT = 0x07; // 灰白色
const WORD COLOR_WALL = 0x09; // 亮蓝色
const WORD COLOR_PATH = 0xE0; // 亮黄底、黑字
const WORD COLOR_OPEN = 0x3F; // 暗青底、亮白字
const WORD COLOR_CLOSED = 0x8F; // 暗灰底、亮白字

// 搜索数据表
int gCost[100][100]; // 从起点到各格子的最小代价 g
int parentI[100][100], parentJ[100][100]; // 各格子在路径上的父节点坐标
bool inOpen[100][100]; // 格子是否在 Open 表中
bool inClosed[100][100]; // 格子是否在 Closed 表中

struct Point
{
	int i, j; // 格子坐标
};
Point openList[100 * 100]; // Open 表
int openCount = 0; // Open 表当前节点数

int closedCount = 0; // 已扩展（放入 Closed 表）的节点数

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

// 估计代价的启发函数
int heuristic(int i, int j)
{
	int di = abs(i - endI), dj = abs(j - endJ);

#if COST_FUNCTION == 1 // 曼哈顿距离
	return di + dj;
#elif COST_FUNCTION == 2
	return (int)(sqrt((double)(di * di + dj * dj)) + 0.5); // 欧几里得距离（取整）
#endif
}

// 返回 Open 表中 f = g + h 最小的节点的下标
int openMinIndex()
{
	int best = 0, bestF = INT_MAX;
	for (int k = 0; k < openCount; k++)
	{
		int i = openList[k].i, j = openList[k].j;
		int f = gCost[i][j] + heuristic(i, j);
		if (f < bestF)
		{
			bestF = f;
			best = k;
		}
	}
	return best;
}

// 把格子加入 Open 表
void addToOpen(int i, int j)
{
	openList[openCount].i = i;
	openList[openCount].j = j;
	openCount++;
	inOpen[i][j] = true;
}

// 从终点沿父节点回溯，把路径上的格子标记为 1
void markPath()
{
	int i = endI, j = endJ;
	while (i >= 0)
	{
		maze[i][j] = 1;
		int pi = parentI[i][j], pj = parentJ[i][j];
		i = pi;
		j = pj;
	}
}

// A* 搜索：找到路径返回 true，否则返回 false
bool aStar()
{
	// 各格子的 g 值初始为无穷大
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			gCost[i][j] = INT_MAX;
			parentI[i][j] = -1;
			parentJ[i][j] = -1;
			inOpen[i][j] = false;
			inClosed[i][j] = false;
		}
	}

	// 起点放入 Open 表
	gCost[startI][startJ] = 0;
	addToOpen(startI, startJ);

	// 四个方向的偏移量
	const int di[4] = { -1, 1, 0, 0 };
	const int dj[4] = { 0, 0, -1, 1 };

	while (openCount > 0)
	{
		// 从 Open 表中取出 f 最小的节点
		int k = openMinIndex();
		int i = openList[k].i, j = openList[k].j;

		// 取出的正是终点，搜索成功
		if (i == endI && j == endJ)
		{
			markPath();
			return true;
		}

		// 从 Open 表中删除被取出的节点
		openList[k] = openList[--openCount];
		inOpen[i][j] = false;

		// 并放入 Closed 表
		inClosed[i][j] = true;
		closedCount++;

		// 扩展相邻节点
		for (int d = 0; d < 4; d++)
		{
			int ni = i + di[d], nj = j + dj[d];
			if (ni < 0 || ni >= row || nj < 0 || nj >= col) // 越界
				continue;
			if (maze[ni][nj] == 2 || inClosed[ni][nj]) // 是墙壁或已被扩展过
				continue;

			int g = gCost[i][j] + 1; // 每走一步的代价为 1
			if (g < gCost[ni][nj]) // 找到了到该邻居更短的路径
			{
				gCost[ni][nj] = g;
				parentI[ni][nj] = i;
				parentJ[ni][nj] = j;
				if (!inOpen[ni][nj])
					addToOpen(ni, nj);
			}
		}
	}

	return false;
}

// 以指定颜色打印单个格子，打印后恢复默认颜色
void printCell(const char* symbol, WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%s", symbol);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_DEFAULT);
}

// 打印整个迷宫
void printMaze()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (maze[i][j] == 1)
				printCell(SYM_PATH, COLOR_PATH);
			else if (maze[i][j] == 2)
				printCell(SYM_WALL, COLOR_WALL);
			else if (inClosed[i][j])
				printCell(SYM_CLOSED, COLOR_CLOSED);
			else if (inOpen[i][j])
				printCell(SYM_OPEN, COLOR_OPEN);
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

	srand(seed);
	createWall();
	createMaze();

	// 出口在迷宫右下角
	endI = row - 2;
	endJ = col - 2;

	// 执行搜索
	if (aStar())
		printf("\nOKAY：找到路径，长度 %d 步，已扩展节点 %d 个\n", gCost[endI][endJ], closedCount);
	else
		printf("\nFAIL：没有找到路径，已扩展节点 %d 个\n", closedCount);

	// 打印迷宫
	printMaze();

	system("pause");
	return 0;
}
