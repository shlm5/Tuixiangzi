#include"function.h"
char map[50][50] = { 0 };//������Ϸ��ͼ
void init()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���ھ��
	CONSOLE_CURSOR_INFO cci;//ʵ�л�һ������̨�����Ϣ��
	GetConsoleCursorInfo(hOut, &cci);//��ȡ�����Ϣ
	cci.bVisible = FALSE;//���ع��
	SetConsoleCursorInfo(hOut, &cci);//���ù����Ϣ

	system("title ������?"); //��������
	system("mode con cols=120 lines=30");//���ڴ�С
}

void mainloop() {
	int scenes;//����
	int key;//��������
	int level;//��ǰ�ؿ�
	int level_option;//ѡ��ùؿ�
	int isEnd;//�˳������

	scenes = 0;//��ʼ������Ϊ������
	isEnd = 0;//�˳������
	level = 0;//�ӵ�һ�ؿ�ʼ��level��Χ0-35��
	level_option = 1;//��1����

	//������
	char main_interface[50][50] = {
		"\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t ������",
		"\t\t\t\t\t\t   ��~~~~~~~~~~~~~~~��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��    ��ʼ(S)    ��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��   �˳�(ESC)   ��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��~~~~~~~~~~~~~~~��",
	};

	//����2
	char interface2[50][50] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t ������\n",
		"\t\t\t\t\t\t   ��~~~~~~~~~~~~~~~��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��   ��ͷ��ʼ(A) ��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��    ѡ��(X)    ��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��    ����(R)    ��",
		"\t\t\t\t\t\t   ��               ��",
		"\t\t\t\t\t\t   ��~~~~~~~~~~~~~~~��"
	};



	//�������
	while (1) {

		//��ӡ����
		system("cls");//����������˸
		switch (scenes) {
		case 0://��ʼΪ������
			for (int i = 0;i < 11;i++)
				puts(main_interface[i]);
			break;
		case 1:
			//��ӡ����2
			for (int i = 0; i < 11; i++)
				puts(interface2[i]);
			break;
		case 2:
			//��ӡѡ�ؽ���
			printf("\n\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t");
			printf("��ѡ��ؿ�(1-%d):%d\n", maps_num, level_option);
			printf("\t\t\t\t\t\t\n");
			printf("\t\t\t\t\t  ");
			printf("���밴�ո��س������Ӧ�ؿ���");
			break;
		default:
			break;
		}

		//��������
		if (scenes < 3) {
			key = getch();//��ȡ��������
			key = tolower(key);//ͳһΪСд
		}

		//�����ж�
		//ÿ�����������ʹ�÷���
		switch (scenes) {
		case 0:
			if (key == 's')//���롮s���ͽ������2
				scenes = 1;
			else if (key == 27)//����27��ESC�����˳�
				isEnd = 1;
			break;
		case 1:
			if (key == 'a')//�����һ��
				scenes = 3;
			else if (key == 'x')//����ѡ�ؽ���
				scenes = 2;
			else if (key == 'r')//�������˵�
				scenes = 0;
			break;
		case 2:/*ѡ�ؽ���
			   level_option�÷�ΧΪ0-35
			   ע�ⲻ��Խ��*/
			if (key == 'a'&&level_option > 1)//���롮a��������С
				level_option--;
			else if (key == 'd' && level_option < maps_num)//���롮d����������
				level_option++;
			else if (key == 13 || key == 32)//����13���ո񣩻� 32���س���������ѡ�ؿ�
			{
				level = level_option - 1;//�滻��ǰ�ؿ�Ϊ��ѡ�ؿ�
				scenes = 4;
			}
			break;
		case 3:
			level = 0;//�����һ��
			scenes = gameloop(level);
			break;
		case 4:
			scenes = gameloop(level);//������ѡ�ؿ�
			break;
		case 5://������һ��
			level++;
			scenes = 4;
			break;
		case 6://ͨ����������
			scenes = 0;
			level;
			break;
		default:
			break;
		}
		if (isEnd)//�ж��Ƿ��˳�
			break;
	}
}




int gameloop(int level)
{
	int x, y;//xΪ�����꣬yΪ������
	char key;//������Ϸ����
	int scenes;//��ǰ����
	int wide=0;//��ͼ���
	int isEnd = 0;//��ͣѡ��->������ͣ����
	int reValue;//����ֵ�������泡��

	int step_num = 0;//��¼�����ܲ���
	int backx, backy;//��һ�������λ��
	int back_x, back_y;//��һ�����ӵ�λ��

	//��¼�յ�����
	int aim_x[50] = { 0 }, aim_y[50] = { 0 };
	int a_x = 0, a_y = 0;

	key = NULL;
	scenes = 0;
	reValue = 0;


	//�����ͼ


	LoadMap(level, map);
	wide = strlen(map[0]);//�����ͼ��ȣ���������


	//Ѱ������λ��
	for (int i = 0;i < 19;i++)
		for (int t = 0;map[i][t] != '\0';t++)
			if (map[i][t] == '@')
			{
				x = i;
				y = t;
				i = 19;//�˳�ѭ��
				break;
			}

	//Ѱ���յ�����
	for (int i = 2;i < 18;i++)
		for (int t = 2;map[i][t] != '\0';t++)
		{
			if (map[i][t] == 'Q' || map[i][t] == 'X')//QΪ�����ӣ�XΪδ������
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

	//��Ϸ��ѭ��
	while (1)
	{
		system("cls");//�����Ļ������˸
		switch (scenes)
		{
		case 0:
			//��Ϸ���н���
			printf("\n\n\n\n\t\t\t\t\t\t         ��%d��", level + 1);
			printf("\n\n");
			for (int i = 0;i <= 17;i++)
			{
				for (int t = 0; t < (120 - wide) / 2; t++)
					printf(" ");
				puts(map[i]);//��ӡ��ͼ
			}
			printf("\t\t\t\t\t\t��~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��\n");
			printf("\t\t\t\t\t\t ������%d  ���汾�أ�Q�� �˵�(ESC)\n\n", step_num);
			printf("\t\t\t\t\t\t��~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��\n");
			break;
		case 1:
			//��ͣ����
			printf("\n\n\n\n\n\t\t\t\t\t\t        ����(R)\n");
			if (level == maps_num - 1)//�����ǰ�ؿ�Ϊ���һ�أ�����ʾ"��һ��(N)"
				printf("\n\n\t\t\t\t         ѡ��(X)  ����(Q)  ���˵�(M)  \n");
			else
				printf("\n\n\t\t\t\t         ѡ��(X)  ����(Q)  ��һ��(N)  ���˵�(M)  \n");
			printf("\n\n\n\t\t\t\t\t\t      ����˵��");
			printf("\n\n\t\t\t\t\t        W/��:��  S/��:��  A/��:��  D/��:��");
			printf("\n\n\t\t\t\t\t         @:��  O:����  X:�յ� ");
			break;
		case 2:
			//���ؽ���
			if (level == maps_num - 1)//�����ǰ�ؿ�Ϊ���һ��
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t��ϲͨ�أ�");
			else
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t  ����!");
			printf("\n\n\t\t\t\t\t\t    �����ܼƲ�����%d", step_num);
			if (level == maps_num - 1)
				printf("\n\n\t\t\t\t\t  ѡ��(X)  ����(Q)  ���˵�(M)  \n");
			else
				printf("\n\n\t\t\t\t\t  ѡ��(X)  ����(Q)  ��һ��(N)  ���˵�(M)  \n");
			break;
		default:
			break;
		}

		//�����ж�
		key = getch();
		key = tolower(key);

		switch (key)//���������
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
				if (map[x - 1][y] == ' ' || map[x - 1][y] == 'X')//��ǰ���ǿյػ���Ŀ�ĵ�
				{
					map[x][y] = ' ';//����ԭ��Ϊ�յ�
					x--;
					map[x][y] = '@';//�� ǰ��
					step_num++;
				}
				else if (map[x - 1][y] == 'O'&&map[x - 2][y] == ' ')//��ǰ�������ӣ���ǰ���ǿյ�
				{
					map[x][y] = ' ';//����ԭ��Ϊ�յ�
					x--;
					map[x][y] = '@';//��ǰ��
					map[x - 1][y] = 'O';//����ǰ��
					step_num++;
				}
				else if (map[x - 1][y] == 'O'  && map[x - 2][y] == 'X')//��ǰ�������ӻ��ߴ����ӵ��յ㣬��ǰ���ǿյ�
				{
					map[x][y] = ' ';//����ԭ��Ϊ�յ�
					x--;
					map[x][y] = '@';//��ǰ��
					map[x - 1][y] = 'Q';//����ǰ��
					a_x--;
					step_num++;
				}
				else if (map[x - 1][y] == 'Q'&& map[x - 2][y] == 'X')//��ǰ���Ǵ����ӵ��յ㣬��ǰ���ǿյ�
				{
					map[x][y] = ' ';//����ԭ��Ϊ�յ�
					x--;
					map[x][y] = '@';//��ǰ��
					map[x - 1][y] = 'Q';//����ǰ��
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
				else if (map[x + 1][y] == 'Q'&& map[x + 2][y] == 'X')//��ǰ���Ǵ����ӵ��յ㣬��ǰ���ǿյ�
				{
					map[x][y] = ' ';//����ԭ��Ϊ�յ�
					x++;
					map[x][y] = '@';//��ǰ��
					map[x + 1][y] = 'Q';//����ǰ��
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
				else if (map[x][y - 1] == 'Q'&& map[x][y - 2] == 'X')//��ǰ���Ǵ����ӵ��յ㣬��ǰ���ǿյ�
				{
					map[x][y] = ' ';//����ԭ��Ϊ�յ�
					y--;
					map[x][y] = '@';//��ǰ��
					map[x][y - 1] = 'Q';//����ǰ��
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
			else if (key == 'q')//����
			{
				reValue = 4;
				isEnd = 1;
			}
			else if (key == 27)//������ͣ����
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
		case 2://����
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
		//���ݸ���

		//����յ�������յ����
		for (int i = 0;aim_x[i] != 0;i++)
		{
			if (map[aim_x[i]][aim_y[i]] == 'O')//���յ��������ӣ���Ϊ'Q'
				map[aim_x[i]][aim_y[i]] = 'Q';
			if (map[aim_x[i]][aim_y[i]] == ' ')//���յ��Ϊ�ո������Ϊ'X'
				map[aim_x[i]][aim_y[i]] = 'X';
		}

		//ͨ�������ж�
		int ko = 0;//�����յ��������
		for (int i = 0;aim_x[i] != 0;i++)//����յ�����
		{
			if (map[aim_x[i]] == 'Q')//�յ��������
				ko++;
		}
		if (ko == a_x)//���
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
	}//�쳣����
	for (int i = 0;;i++)
	{
		fgets(map[i], 100, fp);
		map[i][strlen(map[i]) - 1] = '\0';//
		if (map[i][1] == '|')//���һ�еڶ����ַ�Ϊ��|��
		{
			map[i][1] = '=';//�������жϵġ�|����Ϊ��=����ʹ����һ��
			break;
		}
	}

	fclose(fp);
}

