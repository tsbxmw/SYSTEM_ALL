
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "config.h"

using namespace std;

/**********************************************************************************************************/
/*
	*����ÿ��filename�ļ�
*/
void refresh_configname(string project)
{
	cout<<"update all filename"<<endl;
	system(("dir /b /o "+project+"\\configfile_all > "+project+"\\filename_all.txt").c_str());
	system(("dir /b /o "+project+"\\config_not_read > "+project+"\\filename_not_read.txt").c_str());
	system(("dir /b /o "+project+"\\config_read > "+project+"\\filename_read.txt").c_str());
	system(("dir /b /o "+project+"\\config_not_test > "+project+"\\filename_not_test.txt").c_str());

}

/************************************************************************************************************/
/*
	*�˴�ֻ�Ǹ���notread��read��nottest���ļ�������-��Ӧ��txt�ļ���ȥ��
*/
void refresh_read_not_read(string project)
{
	system(("dir /b /o "+project+"\\config_not_read > "+project+"\\filename_not_read.txt").c_str());
	system(("dir /b /o "+project+"\\config_read > "+project+"\\filename_read.txt").c_str());
	system(("dir /b /o "+project+"\\config_not_test > "+project+"\\filename_not_test.txt").c_str());

}

/************************************************************************************************************/
/*
	*�Ƴ�ǰ��� PATH=����þ���·�������أ�����ʵ�ʵ�ǰ׺���и��ģ�
	*removepath(char *x,int y);
*/
char * removepath(char x[10000],int length)
{
	length=length+12;//ȥ�� path=ftp://10.63.220.2/transfer/  .length().
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

/************************************************************************************************************/
/*
	// open the config_ini file to setup and create the new cfg file to 
	// download the version file from the ftpserver
*/
void open_config_ini(string localfile[100],string project) 
{
	char local_ini[1000];
	int ini_line=0;
	fstream config_ini;
	//cout<<project<<endl;
	config_ini.open(project+"\\config_ini.ini");//read the config file

	while(config_ini.getline(local_ini,300,'\n'))
	{
		cout<<"<-- local_ini opened : " << local_ini << " -->"<<endl;
		if(!(local_ini[0]==':' && local_ini[1]==':' &&local_ini[2]=='-'))
		{
			switch(ini_line){
			case 0:
				localfile[6]=local_ini;//���ذ汾���·��������
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
			default:
				break;
			}

			ini_line++;
		}
	}
	config_ini.close();

	//cout<<localfile[10]<<endl;

}
void open_config_sql(string localfile[100],string project,MYSQL *mysql) 
{
	int res;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string buff = "select * from ";
	buff = buff + "config";
	buff = buff + " where project =\'"+project+"\'" ;
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	if(res)
	{
		cout<<"|-- error "<<endl;

	}
	else
	{
		res_mysql = mysql_store_result(mysql);
		if(mysql_num_rows(res_mysql)==0)
		{

			cout<<"|-- wrong with the result !!!! error "<<endl;
		}
		else
		{
			if(res_mysql)
			{
		
			//	cout<<mysql_num_rows(res_mysql)<<endl;
				cout<<"|-- find the line : ";
				while(row = mysql_fetch_row(res_mysql))
				{
					localfile[6] = row[2];
					localfile[8] = row[3];
					localfile[9] = row[4];
					localfile[10] = row[5];
					localfile[11] = row[6];
					localfile[13] = row[7];
					localfile[14] = row[8];
					for(int i =0;i<12;i++)
					{
						cout<<row[i]<<"-";

					}
					cout <<endl;
					cout<<localfile[6]<<localfile[8]<<localfile[9]<<localfile[10]<<localfile[11]<<localfile[13]<<localfile[14]<<endl;
				}
			}
		}
		cout<<"|-- get the config info  ok "<<endl;
	}
	



	//cout<<localfile[10]<<endl;

}

/************************************************************************************************************/
void update_project_ini()
{
	system("dir /ad /b /o PROJECT > PROJECT\\project_info.ini");
}

int open_project_config_ini(string localfile[100]) 
{
	update_project_ini();
	char local_ini[1000];
	int ini_line=0;
	fstream config_ini;
	//cout<<project<<endl;
	config_ini.open("PROJECT\\project_info.ini");//read the config file

	while(config_ini.getline(local_ini,300,'\n'))
	{
		cout<<"<-- project_ini opened " << local_ini<<" -->"<<endl;
		if(!(local_ini[0]==':' && local_ini[1]==':' &&local_ini[2]=='-'))
		{
			localfile[18+ini_line] =local_ini;

			//switch(ini_line){
			//case 0:
			//	localfile[18]=local_ini;//���ذ汾���·��������
			//	break;
			//case 1:
			//	localfile[19]=local_ini;//ftp ip address
			//	break;
			//case 2:
			//	localfile[20]=local_ini;//user_name
			//	break;
			//case 3:
			//	localfile[21]=local_ini;//password
			//	break;
			//case 4:
			//	localfile[22]=local_ini;//config_upload_path
			//	break;
			//case 5:
			//	localfile[23]=local_ini;//ftp servers config_files path
			//	break;
			//case 6:
			//	localfile[24]=local_ini;//config file pre name
			//	break;
			//case 7:
			//	localfile[25]=local_ini;//config file pre name
			//	break;
			//case 8:
			//	localfile[26]=local_ini;//config file pre name
			//	break;
			//case 9:
			//	localfile[27]=local_ini;//config file pre name
			//	break;
			//default:
			//	break;
			
			ini_line++;
		

		}


	}

	
	config_ini.close();

	return ini_line - 1 ;
	//cout<<localfile[10]<<endl;

}




/************************************************************************************************************/









/************************************************************************************************************/
void config_init()
{
	
}

/************************************************************************************************************/
void create_getconfig_cfg(string localfile[100],string project)
{
	system(("@echo open "+localfile[8]+"> getconfig.cfg").c_str());
	system(("@echo "+localfile[9]+">> getconfig.cfg").c_str());
	system(("@echo "+localfile[10]+">> getconfig.cfg").c_str());
	system(("@echo cd "+localfile[13]+">> getconfig.cfg").c_str());
	system(("@echo lcd "+project+"\\configfile_all >> getconfig.cfg").c_str());
	system(("@echo prompt off >> getconfig.cfg"));
	system(("@echo mget "+localfile[14]+">> getconfig.cfg").c_str());
	system(("@echo bye>> getconfig.cfg"));
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

		int j=i%60;
		int mins = i/60;
		if(j==0)
		{
			cout<<endl<<"<-- WAIT TIME : minute : "<<mins<<endl;
		}
		if(j==59)
			cout<<j<<"-_-";
		else
			cout<<j<<endl;;

	}
}


