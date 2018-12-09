#include"function.h"
char map[50][50] = { 0 };//定义游戏地图
void init()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取窗口句柄
	CONSOLE_CURSOR_INFO cci;//实列化一个控制台光标信息类
	GetConsoleCursorInfo(hOut, &cci);//获取光标信息
	cci.bVisible = FALSE;//隐藏光标
	SetConsoleCursorInfo(hOut, &cci);//设置光标信息

	system("title 推箱子?"); //窗口名称
	system("mode con cols=120 lines=30");//窗口大小
}

void mainloop() {
	int scenes;//场景
	int key;//操作命令
	int level;//当前关卡
	int level_option;//选择得关卡
	int isEnd;//退出与结束

	scenes = 0;//初始化场景为主界面
	isEnd = 0;//退出与结束
	level = 0;//从第一关开始（level范围0-35）
	level_option = 1;//从1算起

	//主界面
	char main_interface[50][50] = {
		"\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子",
		"\t\t\t\t\t\t   ∮~~~~~~~~~~~~~~~∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮    开始(S)    ∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮   退出(ESC)   ∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮~~~~~~~~~~~~~~~∮",
	};

	//界面2
	char interface2[50][50] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子\n",
		"\t\t\t\t\t\t   ∮~~~~~~~~~~~~~~~∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮   从头开始(A) ∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮    选关(X)    ∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮    返回(R)    ∮",
		"\t\t\t\t\t\t   ∮               ∮",
		"\t\t\t\t\t\t   ∮~~~~~~~~~~~~~~~∮"
	};



	//界面操作
	while (1) {

		//打印界面
		system("cls");//清屏，会闪烁
		switch (scenes) {
		case 0://初始为主界面
			for (int i = 0;i < 11;i++)
				puts(main_interface[i]);
			break;
		case 1:
			//打印界面2
			for (int i = 0; i < 11; i++)
				puts(interface2[i]);
			break;
		case 2:
			//打印选关界面
			printf("\n\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t");
			printf("请选择关卡(1-%d):%d\n", maps_num, level_option);
			printf("\t\t\t\t\t\t\n");
			printf("\t\t\t\t\t  ");
			printf("（请按空格或回车进入对应关卡）");
			break;
		default:
			break;
		}

		//输入命令
		if (scenes < 3) {
			key = getch();//获取键盘输入
			key = tolower(key);//统一为小写
		}

		//操作判定
		//每个界面均可以使用返回
		switch (scenes) {
		case 0:
			if (key == 's')//输入‘s’就进入界面2
				scenes = 1;
			else if (key == 27)//输入27（ESC）就退出
				isEnd = 1;
			break;
		case 1:
			if (key == 'a')//进入第一关
				scenes = 3;
			else if (key == 'x')//进入选关界面
				scenes = 2;
			else if (key == 'r')//进入主菜单
				scenes = 0;
			break;
		case 2:/*选关界面
			   level_option得范围为0-35
			   注意不能越界*/
			if (key == 'a'&&level_option > 1)//输入‘a’关数调小
				level_option--;
			else if (key == 'd' && level_option < maps_num)//输入‘d’关数调大
				level_option++;
			else if (key == 13 || key == 32)//输入13（空格）或 32（回车）进入所选关卡
			{
				level = level_option - 1;//替换当前关卡为所选关卡
				scenes = 4;
			}
			break;
		case 3:
			level = 0;//进入第一关
			scenes = gameloop(level);
			break;
		case 4:
			scenes = gameloop(level);//进入所选关卡
			break;
		case 5://进入下一关
			level++;
			scenes = 4;
			break;
		case 6://通关重置数据
			scenes = 0;
			level;
			break;
		default:
			break;
		}
		if (isEnd)//判断是否退出
			break;
	}
}




int gameloop(int level)
{
	int x, y;//x为纵坐标，y为横坐标
	char key;//输入游戏操作
	int scenes;//当前场景
	int wide=0;//地图宽度
	int isEnd = 0;//暂停选项->进入暂停界面
	int reValue;//返回值，主界面场景

	int step_num = 0;//记录单局总步数
	int backx, backy;//上一步任务的位置
	int back_x, back_y;//上一步箱子的位置

	//记录终点坐标
	int aim_x[50] = { 0 }, aim_y[50] = { 0 };
	int a_x = 0, a_y = 0;

	key = NULL;
	scenes = 0;
	reValue = 0;


	//读入地图


	LoadMap(level, map);
	wide = strlen(map[0]);//计算地图宽度，用于美化


	//寻找人物位置
	for (int i = 0;i < 19;i++)
		for (int t = 0;map[i][t] != '\0';t++)
			if (map[i][t] == '@')
			{
				x = i;
				y = t;
				i = 19;//退出循环
				break;
			}

	//寻找终点坐标
	for (int i = 2;i < 18;i++)
		for (int t = 2;map[i][t] != '\0';t++)
		{
			if (map[i][t] == 'Q' || map[i][t] == 'X')//Q为有箱子，X为未有箱子
			{
				aim_x[a_x] = i;
				aim_y[a_y] = t;
				a_x++;
				a_y++;
			}
			if (map[i][1] == '|')
			{
				i = 19;
				break;
			}
		}

	//游戏主循环
	while (1)
	{
		system("cls");//清空屏幕，会闪烁
		switch (scenes)
		{
		case 0:
			//游戏进行界面
			printf("\n\n\n\n\t\t\t\t\t\t         第%d关", level + 1);
			printf("\n\n");
			for (int i = 0;i <= 17;i++)
			{
				for (int t = 0; t < (120 - wide) / 2; t++)
					printf(" ");
				puts(map[i]);//打印地图
			}
			printf("\t\t\t\t\t\t∮~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~∮\n");
			printf("\t\t\t\t\t\t 步数：%d  重玩本关（Q） 菜单(ESC)\n\n", step_num);
			printf("\t\t\t\t\t\t∮~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~∮\n");
			break;
		case 1:
			//暂停界面
			printf("\n\n\n\n\n\t\t\t\t\t\t        继续(R)\n");
			if (level == maps_num - 1)//如果当前关卡为最后一关，则不显示"下一关(N)"
				printf("\n\n\t\t\t\t         选关(X)  重玩(Q)  主菜单(M)  \n");
			else
				printf("\n\n\t\t\t\t         选关(X)  重玩(Q)  下一关(N)  主菜单(M)  \n");
			printf("\n\n\n\t\t\t\t\t\t      操作说明");
			printf("\n\n\t\t\t\t\t        W/↑:上  S/↓:下  A/←:左  D/→:右");
			printf("\n\n\t\t\t\t\t         @:人  O:箱子  X:终点 ");
			break;
		case 2:
			//过关界面
			if (level == maps_num - 1)//如果当前关卡为最后一关
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t恭喜通关！");
			else
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t  过关!");
			printf("\n\n\t\t\t\t\t\t    本关总计步数：%d", step_num);
			if (level == maps_num - 1)
				printf("\n\n\t\t\t\t\t  选关(X)  重玩(Q)  主菜单(M)  \n");
			else
				printf("\n\n\t\t\t\t\t  选关(X)  重玩(Q)  下一关(N)  主菜单(M)  \n");
			break;
		default:
			break;
		}

		//操作判定
		key = getch();
		key = tolower(key);

		switch (key)//方向键操作
		{
		case -32:
			switch (key = getch())
			{
			case 72:
				key = 'w';
				break;
			case KEY_DOWN:
				key = 's';
				break;
			case KEY_LEFT:
				key = 'a';
				break;
			case KEY_RIGHT:
				key = 'd';
				break;
			default:
				break;
			}
			break;
		}

		switch (scenes)
		{

		case 0:
			if (key == 'w')
			{
				if (map[x - 1][y] == ' ' || map[x - 1][y] == 'X')//若前方是空地或者目的地
				{
					map[x][y] = ' ';//更新原地为空地
					x--;
					map[x][y] = '@';//人 前进
					step_num++;
				}
				else if (map[x - 1][y] == 'O'&&map[x - 2][y] == ' ')//若前方是箱子，再前方是空地
				{
					map[x][y] = ' ';//更新原地为空地
					x--;
					map[x][y] = '@';//人前进
					map[x - 1][y] = 'O';//箱子前进
					step_num++;
				}
				else if (map[x - 1][y] == 'O'  && map[x - 2][y] == 'X')//若前方是箱子或者带箱子的终点，再前方是空地
				{
					map[x][y] = ' ';//更新原地为空地
					x--;
					map[x][y] = '@';//人前进
					map[x - 1][y] = 'Q';//箱子前进
					a_x--;
					step_num++;
				}
				else if (map[x - 1][y] == 'Q'&& map[x - 2][y] == 'X')//若前方是带箱子的终点，再前方是空地
				{
					map[x][y] = ' ';//更新原地为空地
					x--;
					map[x][y] = '@';//人前进
					map[x - 1][y] = 'Q';//箱子前进
					step_num++;
				}
			}
			else if (key == 's')
			{
				if (map[x + 1][y] == ' ' || map[x + 1][y] == 'X')
				{
					map[x][y] = ' ';
					x++;
					map[x][y] = '@';
					step_num++;
				}
				else if (map[x + 1][y] == 'O'&&map[x + 2][y] == ' ')
				{
					map[x][y] = ' ';
					x++;
					map[x][y] = '@';
					map[x + 1][y] = 'O';
					step_num++;
				}
				else if (map[x + 1][y] == 'O' && map[x + 2][y] == 'X')
				{
					map[x][y] = ' ';
					x++;
					map[x][y] = '@';
					map[x + 1][y] = 'Q';
					a_x--;
					step_num++;
				}
				else if (map[x + 1][y] == 'Q'&& map[x + 2][y] == 'X')//若前方是带箱子的终点，再前方是空地
				{
					map[x][y] = ' ';//更新原地为空地
					x++;
					map[x][y] = '@';//人前进
					map[x + 1][y] = 'Q';//箱子前进
					step_num++;
				}
			}
			else if (key == 'a' || key == 37)
			{
				if (map[x][y - 1] == ' ' || map[x][y - 1] == 'X')
				{
					map[x][y] = ' ';
					y--;
					map[x][y] = '@';
				}
				else if (map[x][y - 1] == 'O'&&map[x][y - 2] == ' ')
				{
					map[x][y] = ' ';
					y--;
					map[x][y] = '@';
					map[x][y - 1] = 'O';
				}
				else if (map[x][y - 1] == 'O' && map[x][y - 2] == 'X')
				{
					map[x][y] = ' ';
					y--;
					map[x][y] = '@';
					map[x][y - 1] = 'Q';
					a_x--;
				}
				else if (map[x][y - 1] == 'Q'&& map[x][y - 2] == 'X')//若前方是带箱子的终点，再前方是空地
				{
					map[x][y] = ' ';//更新原地为空地
					y--;
					map[x][y] = '@';//人前进
					map[x][y - 1] = 'Q';//箱子前进
					step_num++;
				}
			}
			else if (key == 'd' || key == 39)
			{
				if (map[x][y + 1] == ' ' || map[x][y + 1] == 'X')
				{
					map[x][y] = ' ';
					y++;
					map[x][y] = '@';
				}
				else if (map[x][y + 1] == 'O'&&map[x][y + 2] == ' ')
				{
					map[x][y] = ' ';
					y++;
					map[x][y] = '@';
					map[x][y + 1] = 'O';
				}
				else if (map[x][y + 1] == 'O' && map[x][y + 2] == 'X')
				{
					map[x][y] = ' ';
					y++;
					map[x][y] = '@';
					map[x][y + 1] = 'Q';
					a_x--;
				}
				else if (map[x][y + 1] == 'Q'&& map[x][y + 2] == 'X')
				{
					map[x][y] = ' ';
					y++;
					map[x][y] = '@';
					map[x][y + 1] = 'Q';
					step_num++;
				}
			}
			else if (key == 'q')//重玩
			{
				reValue = 4;
				isEnd = 1;
			}
			else if (key == 27)//进入暂停界面
				scenes = 1;
			break;
		case 1:
			if (key == 'r' || key == 27)
				scenes = 0;
			else if (key == 'x')
			{
				reValue = 2;
				isEnd = 1;
			}
			else if (key == 'n'&&level != maps_num - 1)
			{
				reValue = 5;
				isEnd = 1;
			}
			else if (key == 'm')
			{
				reValue = 1;
				isEnd = 1;
			}
			else if (key == 'q')
			{
				reValue = 4;
				isEnd = 1;
			}
			break;
		case 2://更新
			if (key == 'x') {
				reValue = 2;
				isEnd = 1;
			}
			else if (key == 'q') {
				reValue = 4;
				isEnd = 1;
			}
			else if (key == 'n'&&level != maps_num - 1) {
				reValue = 5;
				isEnd = 1;
			}
			else if (key == 'm') {
				reValue = 1;
				isEnd = 1;
			}
			break;
		default:
			break;
		}
		//数据更新

		//检查终点出并将终点更新
		for (int i = 0;aim_x[i] != 0;i++)
		{
			if (map[aim_x[i]][aim_y[i]] == 'O')//若终点上有箱子，则换为'Q'
				map[aim_x[i]][aim_y[i]] = 'Q';
			if (map[aim_x[i]][aim_y[i]] == ' ')//若终点变为空格，则更新为'X'
				map[aim_x[i]][aim_y[i]] = 'X';
		}

		//通关条件判定
		int ko = 0;//到达终点的箱子数
		for (int i = 0;aim_x[i] != 0;i++)//检查终点坐标
		{
			if (map[aim_x[i]] == 'Q')//终点出有箱子
				ko++;
		}
		if (ko == a_x)//如果
			scenes = 2;

		if (isEnd)
			break;
	}

	return reValue;
}

void  LoadMap(int level, char(*map)[50])
{
	FILE *fp;
	char buffer[100];
	sprintf(buffer, "data\\Map\\%d.txt", level + 1);
	if ((fp = fopen(buffer, "r")) == NULL)
	{
		printf("couldn't find the map file!!!");
		_getch();
		exit(1);
	}//异常处理
	for (int i = 0;;i++)
	{
		fgets(map[i], 100, fp);
		map[i][strlen(map[i]) - 1] = '\0';//
		if (map[i][1] == '|')//最后一行第二个字符为‘|’
		{
			map[i][1] = '=';//将用于判断的‘|’改为‘=’，使整体一致
			break;
		}
	}

	fclose(fp);
}

