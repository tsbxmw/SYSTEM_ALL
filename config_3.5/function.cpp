
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "config.h"

using namespace std;

/**********************************************************************************************************/
/*
	*更新每个filename文件
*/
void refresh_configname()
{
	cout<<"update all filename"<<endl;
	system("dir /b /o .\\configfile_all > filename_all.txt");
	system("dir /b /o .\\config_not_read > filename_not_read.txt");
	system("dir /b /o .\\config_read > filename_read.txt");
	system("dir /b /o .\\config_not_test > filename_not_test.txt");
}

/************************************************************************************************************/
/*
	*此处只是更新notread和read和nottest的文件夹内容-相应的txt文件中去。
*/
void refresh_read_not_read()
{
	system("dir /b /o .\\config_not_read > filename_not_read.txt");
	system("dir /b /o .\\config_read > filename_read.txt");
	system("dir /b /o .\\config_not_test > filename_not_test.txt");
}

/************************************************************************************************************/
/*
	*移除前面的 PATH=，获得绝对路径并返回（根据实际的前缀进行更改）
	*removepath(char *x,int y);
*/
char * removepath(char x[10000],int length)
{
	length=length+12;//去除 path=ftp://10.63.220.2/transfer/  .length().
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

/************************************************************************************************************/
/*
	// open the config_ini file to setup and create the new cfg file to 
	// download the version file from the ftpserver
*/
void open_config_ini(string localfile[100]) 
{
	char local_ini[1000];
	int ini_line=0;
	fstream config_ini;
	config_ini.open("config_ini.ini");//read the config file

	while(config_ini.getline(local_ini,300,'\n'))
	{
		cout<<"local_ini opened "<<endl;
		if(!(local_ini[0]==':' && local_ini[1]==':' &&local_ini[2]=='-'))
		{
			switch(ini_line){
			case 0:
				localfile[6]=local_ini;//本地版本存放路径及名称
				break;
			case 1:
				localfile[8]=local_ini;//ftp ip address
				break;
			case 2:
				localfile[9]=local_ini;//user_name
				break;
			case 3:
				localfile[10]=local_ini;//password
				break;
			case 4:
				localfile[11]=local_ini;//config_upload_path
				break;
			case 5:
				localfile[13]=local_ini;//ftp servers config_files path
				break;
			case 6:
				localfile[14]=local_ini;//config file pre name
				break;
			}

			ini_line++;
		}
	}
	config_ini.close();

	//cout<<localfile[10]<<endl;

}

/************************************************************************************************************/
void config_init()
{
	
}

/************************************************************************************************************/
void create_getconfig_cfg(string localfile[100])
{
	system(("@echo open "+localfile[8]+"> getconfig.cfg").c_str());
	system(("@echo "+localfile[9]+">> getconfig.cfg").c_str());
	system(("@echo "+localfile[10]+">> getconfig.cfg").c_str());
	system(("@echo cd "+localfile[13]+">> getconfig.cfg").c_str());
	system("@echo lcd configfile_all >> getconfig.cfg");
	system("@echo prompt off >> getconfig.cfg");
	system(("@echo mget "+localfile[14]+">> getconfig.cfg").c_str());
	system("@echo bye>> getconfig.cfg");
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

/************************************************************************************************************/
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


