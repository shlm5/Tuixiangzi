18级-软件工程-2班-林明
项目名称：推箱子
===============


基本功能：选关、暂停、重玩

添加功能：按方向键也能进行“上下左右”操作


###  添加功能的实现：方向键操作

’‘’

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

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

‘’‘
#### 插入链接
[游戏界面：]（https://github.com/shlm5/Tuixiangzi）
		