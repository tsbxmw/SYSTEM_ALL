        
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
	system("dir /b /o .\\config_not_read > filename_not_read.txt");
	system("dir /b /o .\\config_read > filename_read.txt");
}

/************************************************************************************************************/
/*
	*移除前面的 PATH=，获得绝对路径并返回（根据实际的前缀进行更改）
	*removepath(char *x,int y);
*/
char * removepath(char x[1000],int length)
{
//	length=length+11;//去除 path=ftp://10.63.220.2/transfer/  .length().
	for(int i=0;i<1000;i++)
	{
		//cout<<x[i]<<endl;
		x[i]=x[i+1];
		if(i==0)
		{

		}
		else if(x[i]=='\n')//此处移除最后的回车，变为标准结束
		{
			x[i]='\0';
			break;
		}
	}
	return x;
}

string getconfigname(char local_internal[1000])
{
	string xxx="/";
	strtok(local_internal,xxx.c_str());
	strtok(NULL,xxx.c_str());
	strtok(NULL,xxx.c_str());
	char  *name;
	name = strtok(NULL,xxx.c_str());
	cout <<name <<endl;
	name = strtok(name,".");
	string newname =".config";
	newname = name + newname;
	cout <<newname<<endl;
	return newname;

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
			case 7:
				localfile[15]=local_ini;
				break;
			case 8:
				localfile[16]=local_ini;
				break;
			case 9:
				localfile[17]=local_ini;
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
		Sleep(1000);

		cout<<"-_- :"<<"["<<5-i<<"]"<<endl;;
	}
	cout<<"-_-"<<endl;
}

void mkdir_project_onserver(string localfile[100])
{
	//\\192.168.0.101\project\P809A50\pc_status\P809A50_10.63.220.7_client_read.info

	//it is client file path
	string mkdir_client_not_read = "mkdir config_not_read";
	string mkdir_client_read = "mkdir config_read";
	string mkdir_client_download = "mkdir D:\\version\\"+localfile[15];

	//it is server file path
	string mkdir_project = "mkdir \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15];
	string mkdir_not_read = "mkdir \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15]+"\\config_not_read";
	string mkdir_read = "mkdir \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15]+"\\config_read";
	string mkdir_all = "mkdir \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15]+"\\configfile_all";
	string mkdir_not_test = "mkdir \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15]+"\\config_not_test";
	string mkdir_client_status = "mkdir \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15]+"\\client_status";
	string mkdir_server_status = "mkdir \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15]+"\\server_status";
	string command = localfile[0] + localfile[1]+"config_ini.ini"+" \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15] +"\\" ;
	cout <<"<-- "<<mkdir_client_not_read<<" -->"<<endl;
	cout <<"<-- "<<mkdir_client_read<<" -->"<<endl;
	cout <<"<-- "<<mkdir_client_download<<" -->"<<endl;
	cout <<"<-- "<<mkdir_project <<" -->"<<endl;
	cout <<"<-- "<<mkdir_not_read <<" -->"<<endl;
	cout <<"<-- "<<mkdir_read <<" -->"<<endl;
	cout <<"<-- "<<mkdir_all <<" -->"<<endl;
	cout <<"<-- "<<mkdir_client_status <<" -->"<<endl;
	cout <<"<-- "<<mkdir_server_status <<" -->"<<endl;
	cout <<"<-- "<<command<<" -->"<<endl;

	string project_is_only;
	char temp[30];
	fstream open_project_info;
	bool isonly = true;
	system(("dir /o /b \\\\" + localfile[16] + "\\PROJECT\\" +" > project_first.info").c_str());
	open_project_info.open("project_first.info");
	while(open_project_info.getline(temp,30,'\n'))
	{
		project_is_only = temp;
		if(project_is_only == localfile[15])
		{
			isonly = false;
			break;
		}
	}
	if(isonly)
	{


		system(mkdir_project.c_str());
		system(mkdir_not_read.c_str());
		system(mkdir_read.c_str());
		system(mkdir_all.c_str());
		system(mkdir_not_test.c_str());
		system(mkdir_client_status.c_str());
		system(mkdir_server_status.c_str());
		
	}
	system(mkdir_client_not_read.c_str());
	system(mkdir_client_read.c_str());
	system(mkdir_client_download.c_str());
	system(command.c_str());

}

void get_pc_status_from_server(string localfile[100])
{
	//\\192.168.0.101\project\P809A50\pc_status\P809A50_10.63.220.7_client_read.info
	string command = localfile[0] + localfile[1]+" \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15] +"\\server_status\\" + localfile[15] +"_"+localfile[17]+"_server_read.info" + " .\\config_not_read\\";
	cout <<"<-- "<<command<<" -->"<<endl;
	system(command.c_str());
}

void del_pc_status_on_server(string localfile[100])
{
	//\\10.63.220.2\every_build\PROJECT\P809A50\pc_status\P809A50_10.63.220.7_client_read.info
	string command = "echo BUSY > \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15] +"\\client_status\\" + localfile[15] +"_"+localfile[17]+"_client_read.info";
	cout <<"<-- "<<command<<" -->"<<endl;
	system(command.c_str());
}

void set_server_status_null(string localfile[100])
{
	//\\10.63.220.2\every_build\PROJECT\P809A50\pc_status\P809A50_10.63.220.7_client_read.info
	string command = "echo NULL> \\\\" + localfile[16] + "\\PROJECT\\" + localfile[15] +"\\client_status\\" + localfile[15] +"_"+localfile[17]+"_client_read.info";
	cout <<"<-- "<<command<<" -->"<<endl;
	system(command.c_str());
}

void make_new_info(string lcoalfile[100])
{

	//system();
}

bool read_server_status(string localfile[100])
{
	string info_ip;
	fstream open_local_status;
	char local_status[100];
	open_local_status.open(".\\config_not_read\\" +localfile[15] +"_"+localfile[17]+"_server_read.info");
	open_local_status.getline(local_status,100,'\n');
	info_ip = local_status;
	open_local_status.close();
	cout<<"<-- iam in the read server status ! -->"<<endl;
	cout<<"<-- info : "<<info_ip<<"-->"<<endl;
	local_status[4]='\0';
	if( !strcmp(local_status,"NULL"))
		return true;
	else 
		return false;
}


void upload_status_toserver()
{

}