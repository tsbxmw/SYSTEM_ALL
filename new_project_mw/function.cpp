
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "config.h"

using namespace std;

void refresh_configname()//更新每个filename文件
{
	cout<<"update all filename"<<endl;
	system("dir /b /o .\\configfile_all > filename_all.txt");
	system("dir /b /o .\\config_not_read > filename_not_read.txt");
	system("dir /b /o .\\config_read > filename_read.txt");
	system("dir /b /o .\\config_not_test > filename_not_test.txt");
}

void refresh_read_not_read()//此处只是更新notread和read和nottest的文件夹内容
{
	system("dir /b /o .\\config_not_read > filename_not_read.txt");
	system("dir /b /o .\\config_read > filename_read.txt");
	system("dir /b /o .\\config_not_test > filename_not_test.txt");
}

char * removepath(char x[10000],int length)//移除前面的 PATH=，获得绝对路径并返回（根据实际的前缀进行更改）
{
	length=length+12;//去除path=ftp://10.63.220.2/transfer/.length().
	for(int i=0;i<3000;i++)
	{
		x[i]=x[i+length];
		if(x[i]=='\n')//此处移除最后的回车，变为标准结束
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