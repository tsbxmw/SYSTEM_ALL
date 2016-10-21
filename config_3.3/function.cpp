
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

/*
// the delay time function old version
// the new is to show the minutes and seconds ,qulification the display.
void delay_time(int time)
{
	for(int i=1;i<=time;i++)
	{
		system("@ping -n 2 127.0.0.1 > null");
		if(i>60)
		{
			int j=i%60;
			int mins = i/60;
			cout<<"WAIT TIME : "<<mins<<" mins "<<j<<" seconds"<<endl;
		}
		else
		{
			cout<<"WAIT TIME : "<<i<<" seconds"<<endl;
		}
		
	}
}
*/

void delay_time(int time)
{
	for(int i=0;i<=time;i++)
	{
		system("@ping -n 2 127.0.0.1 > null");

		int j=i%60;
		int mins = i/60;
		if(j==0)
		{
			cout<<endl<<"<-- WAIT TIME : minute : "<<mins<<" second : ";
		}
		if(j==59)
			cout<<j<<" -->";
		else
			cout<<j<<"\"";

	}
}