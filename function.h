#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<string.h>


#define maps_num 35//�ܹ��Ĺؿ�����

//����ǰ������

void init();
/*
��飺
	��ʼ������
������
����ֵ��
*/

void mainloop();
/*
��飺
	������ѭ��
������
����ֵ��
*/

int gameloop(int level);
/*
��飺
	��Ϸѭ��
������
	level:��ǰ��Ϸ���еĹؿ�
����ֵ��
	reValue:��ѭ���ĳ���
*/

void LoadMap(int level, char *(map)[50]);
/*
��飺
	��ȡ��Ϸ��ͼ
������
	level:Ҫ��ȡ�Ĺؿ�
	map_hight:�洢�ؿ��ĸ߶�
	map:�洢�ؿ��Ķ�ά����
����ֵ��
*/

//�����ASCIIֵ
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

