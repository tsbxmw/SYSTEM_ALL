
/*
version  :    2.0
author   :    MW10192582
function :    build-function,send mail
date     :    2016.1.12
COR      :    ZTE
new      :    新增对没有新的config文件时的处理操作。
new      :    增加了对递归调用溢出栈的处理：移除递归调用，进行尾递归使用，防止出现应用意外crash。
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

#include "config.h"

using namespace std;


int config_ftp_mail(string localfile[100])
{
	cout<<"[1]-- client start ! --[1]"<<endl;
	int have_new_config=0,				//have new config or not
		length;							//判断服务器上有没有新的config文件

	char local_not_read[1000],
		 local_internal[1000];                  

	string temp,						//the internal string which used to save the temp string like hello or world em...
		   PATH;						//to save the path string int the config file
	string path_file_test;

	string info_line_get[1000][10];
	int info_line_number = 0;

	fstream config_all,					//input or output file to open the configfile to read the internal
			config_not_read,
			config_read,
			config_internal,
			config_not_test;

	bool ip_status_local;

	
	open_config_ini(localfile);			//open the config_ini ,to read the config

	mkdir_project_onserver(localfile);

	get_pc_status_from_server(localfile);

	ip_status_local = read_server_status(localfile);


	refresh_configname();
	if( ip_status_local)
	{
		config_not_read.open("filename_not_read.txt");
		if(config_not_read.getline(local_not_read,300,'\n'))//读取config_not_read name的最后1行，然后读此行对应的config文件。
		{                 
				config_not_read.close();
				refresh_configname();
				temp=local_not_read;
				cout<<temp<<endl;
				length = localfile[8].length();
				cout<<"length="<<length<<endl;
				system((localfile[0]+localfile[5]+localfile[3]+temp+localfile[4]+temp).c_str());
			//	system((localfile[0]+localfile[1]+localfile[4]+temp+" "+localfile[11]+temp).c_str());

				//读完config后将其移入config_read文件夹
				config_internal.open("config_read\\"+temp);//打开对应的config文件
				config_internal.getline(local_internal,300,' ');

				if(config_internal.getline(local_internal,300,' '))//读文件第2h
				{
					del_pc_status_on_server(localfile);
			
					system("echo copy_begin_time=%date:~0,10% %time% >..\\config.config");

					PATH = removepath(local_internal,11);//获得绝对路径PATH
					
					//PATH = local_internal;
					cout<<"<-- the path is : "<<PATH<<" -->"<<endl;

					
					string config_name = getconfigname(local_internal);
					cout <<config_name <<endl;
					system((localfile[0]+localfile[1]+"\\\\"+localfile[16]+"\\PROJECT\\"+localfile[15]+"\\config_read\\"+config_name+" "+localfile[11]).c_str());

					//下面语句用的是copy命令获取config文件到本地
					//system((localfile[0]+localfile[1]+PATH+localfile[6]).c_str());
					//从服务器上copy文件到本地,此处使用ftp
					//system((localfile[12]+localfile[6]).c_str());
					//↑ 删除本地之前的下载文件版本。

					system("cd ..\\Config_upload");
					system("call upload.bat");
					system("cd ..\\01VersionDown");

					string newpath="echo get "+PATH+" "+localfile[6]+">>autoftp.cfg";
					cout << newpath <<endl;
					system(("echo open "+localfile[8]+"> autoftp.cfg").c_str());
					system(("echo "+localfile[9]+">> autoftp.cfg").c_str());
					system(("echo "+localfile[10]+">> autoftp.cfg").c_str());
					system((newpath).c_str());
					system("echo bye>> autoftp.cfg");
					system("ftp -s:autoftp.cfg");

					system("echo copy_end_time=%date:~0,10% %time% >>..\\config.config");

					system("call SuccessEmail.bat");
					cout<<"<-- debug : i am read the path and into the next step! -->"<<endl;
					//↑SuccessEmail.bat : 用来解压下载后的文件
					return 1;
				}
				else
				{
					set_server_status_null(localfile);
					return 0;

				}
			}
			else
			{
				set_server_status_null(localfile);
				cout<<"<-- Wrong config file ! -->"<<endl;
				return 0;
			}
	}
	else
	{
		set_server_status_null(localfile);
		cout<< "<-- the pc is busy ,please wait for null -->" <<endl;
		return 0;
	}
	
}

