
/*
version  :    2.0
author   :    MW10192582
function :    build-function,send mail
date     :    2016.3.23
COR      :    ZTE
new      :	  mysql client to deal with the config file 
			 upload by sql cotains a lot of new thing in it
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "config.h"
#include "config_mysql.h"
using namespace std;

int config_ftp_mail(string localfile[100],MYSQL *mysql)
{
	cout<<"[1]-- client start ! --[1]"<<endl;
	int have_new_config=0;			//have new config or not
					//判断服务器上有没有新的config文件                
	string temp,						//the internal string which used to save the temp string like hello or world em...
		   PATH;						//to save the path string int the config file
	string path_file_test;
	string result_status_pc;
	string info_line_get[1000][10];
	int info_line_number = 0;

	fstream config_all,					//input or output file to open the configfile to read the internal
			config_not_read,
			config_read,
			config_internal,
			config_not_test;

	bool ip_status_local;



	open_config_ini(localfile);			//open the config_ini ,to read the config
	find_ip_pro_line_config(mysql,TABLE_CON,localfile);

	mkdir_project_onserver(localfile,mysql);


	result_status_pc = find_ip_pro_line_status(mysql,TABLE_SER,localfile);


	refresh_configname();
	cout<<"|-- debug : status_on_pc is :"<<result_status_pc<<endl;
	if( result_status_pc != "NULL" )
	{

			string PATH = result_status_pc;
			system("echo copy_start_time=%date:~0,10% %time% >>..\\config.config");
			system("cd ..\\Config_upload");
			system("call upload.bat");
			system("cd ..\\01VersionDown");

			string newpath="echo get "+PATH+" "+localfile[6]+">>autoftp.cfg";
			cout << "|-- "<<newpath <<endl;
			system(("echo open "+localfile[8]+"> autoftp.cfg").c_str());
			system(("echo "+localfile[9]+">> autoftp.cfg").c_str());
			system(("echo "+localfile[10]+">> autoftp.cfg").c_str());
			system((newpath).c_str());
			system("echo bye>> autoftp.cfg");
			system("ftp -s:autoftp.cfg");

			system("echo copy_end_time=%date:~0,10% %time% >>..\\config.config");

			system("call SuccessEmail.bat");
			cout<<"<-- debug : i am read the path and into the next step! -->"<<endl;

			return 1;
	}
	else
	{
		while(update_table_one_line(mysql,TABLE_CLI,"status_phone","NULL","ip_address",localfile[17],localfile[15]))
		{
			Sleep(1000);
		}
		while(update_table_one_line(mysql,TABLE_CLI,"phone_ison","ON","ip_address",localfile[17],localfile[15]))
		{
			Sleep(1000);
		}
		cout<< "<-- the pc is busy ,please wait for null -->" <<endl;
		return 0;
	}
	
}

