
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "config.h"

using namespace std;

void refresh_configname()//����ÿ��filename�ļ�
{
	cout<<"update all filename"<<endl;
	system("dir /b /o .\\configfile_all > filename_all.txt");
	system("dir /b /o .\\config_not_read > filename_not_read.txt");
	system("dir /b /o .\\config_read > filename_read.txt");
	system("dir /b /o .\\config_not_test > filename_not_test.txt");
}

void refresh_read_not_read()//�˴�ֻ�Ǹ���notread��read��nottest���ļ�������
{
	system("dir /b /o .\\config_not_read > filename_not_read.txt");
	system("dir /b /o .\\config_read > filename_read.txt");
	system("dir /b /o .\\config_not_test > filename_not_test.txt");
}

char * removepath(char x[10000],int length)//�Ƴ�ǰ��� PATH=����þ���·�������أ�����ʵ�ʵ�ǰ׺���и��ģ�
{
	length=length+12;//ȥ��path=ftp://10.63.220.2/transfer/.length().
	for(int i=0;i<3000;i++)
	{
		x[i]=x[i+length];
		if(x[i]=='\n')//�˴��Ƴ����Ļس�����Ϊ��׼����
		{
			x[i]='\0';
		}
	}
	return x;
}

void open_config_ini()
{
	
}

void config_init()
{
	
}


void create_getconfig_cfg()
{

}