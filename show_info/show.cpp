#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;
#define STR_NUMBER 5
bool info_file_copy_file(string localfile[100])
{

	string command = localfile[0] + localfile[1] + localfile[15] + " " + localfile[16];
	int erronum = system(command.c_str());
	cout<<erronum<<endl;
	if(erronum)
		return true;
	else
		return false;
}

bool info_file_del_file(string localfile[100])
{
	string command = localfile[0] + localfile[12] + " " + localfile[16];
	int erronum = system(command.c_str());
	//cout<<erronum<<endl;
	if(erronum)
		return true;
	else
		return false;
}

void system_info_display(string info_line_get[1000][10],int info_line_number)
{
	cout<<"________________________________________________________________________________"<<endl;
	cout<<"||......ip......||....project....||.....id.....||...sta...||...pc...||"<<endl;
	//cout<<" ------------------------------------------------------------------------------- "<<endl;
	for(int i=0;i<info_line_number;i++)
	{
		for(int j=0;j<STR_NUMBER;j++)
		{
			cout<<"|";
			switch(j){
			case 0:
				for(int k=0;k<(15-info_line_get[i][j].length());k++)
				{

					cout<<" ";
				}
				cout<<info_line_get[i][j];
				break;
			case 1:
				for(int k=0;k<(14-info_line_get[i][j].length());k++)
				{

					cout<<" ";
				}
				cout<<info_line_get[i][j];
				break;
			case 2:
				for(int k=0;k<(13-info_line_get[i][j].length());k++)
				{

					cout<<" ";
				}
				cout<<info_line_get[i][j];
				break;
			case 3:
				for(int k=0;k<(9-info_line_get[i][j].length());k++)
				{

					cout<<" ";
				}
				cout<<info_line_get[i][j];
				break;
			case 4:
				for(int k=0;k<(9-info_line_get[i][j].length());k++)
				{

					cout<<" ";
				}
				cout<<info_line_get[i][j];
				break;
			}
			cout<<"|";
		}
		
		cout<<endl;
	}
	cout<<"________________________________________________________________________________"<<endl;
	cout<<endl;
}
//read the info file to get the new status
int info_file_read(string localfile[100],string info_line_get[1000][10])
{
	fstream info_file_open;
	char info_read[300];
	int info_line_str_number,info_line_number = 0;
	
	info_file_open.open(localfile[16]);
	while(info_file_open.getline(info_read,300,'\n'))//读取文件中的每一行
	{
		//cout<<info_read<<endl;
		info_line_str_number = 0;
		info_line_get[info_line_number][0]=strtok(info_read,localfile[17].c_str());
		for(int i=1;i<STR_NUMBER;i++)
		{
			info_line_get[info_line_number][i]=strtok(NULL,localfile[17].c_str());
			//cout<<info_line_get[info_line_number][i]<<endl;
		}
		info_line_number++;
	}
	info_file_open.close();

	//create_new_client_info(info_line_get,info_line_number);

	return info_line_number;
}
void delay_time(int time)
{
	for(int i=0;i<=time;i++)
	{
		int j=0;
		while(j<1000*10000)
			j++;

		
		cout<<"["<<i<<"]";
		
	}
	cout<<endl;
}

int main()
{
	string localfile[100],project,pathfile;
	string info_read[1000][10];
	int linenumber;

	localfile[0]="echo Y | ";
	localfile[1]="copy  ";//拷贝命令
	localfile[2]=" "+project+"\\configfile_all\\";//all_config dir
	localfile[3]=" "+project+"\\config_not_read\\";//config not read dir
	localfile[4]=" "+project+"\\config_read\\";//config already read dir
	localfile[5]="move  ";//移动命令
	localfile[6]="E:\\version\\P809V50\\P809V50.zip";//本地版本存放文件夹(默认)
	localfile[7]=" "+project+"\\config_not_test\\";//未测试的版本路径
	localfile[8]="10.63.220.2";
	localfile[9]="mw1101";
	localfile[10]="mw1101";
	localfile[11]="..\\Config_upload\\";
	localfile[12]="del ";
	localfile[13]="\\CI_version\\config_files";
	localfile[14]="M_P809V50*";
	localfile[15]="infofile.info";
	localfile[16]="infofile_read.info";
	localfile[17]="-";
	
	while(1)
	{
		
		char x;
		
		cout<<"|--------- Refresh the infomation ? (y/n) ---------|"<<endl;
		cout<<"|--------->";
		cin >> x;
		if(x == 'y' || x == 'Y')
		{
			cout<<"|--------- This is the new information ! ---------|"<<endl;
			info_file_copy_file(localfile);
			linenumber = info_file_read(localfile,info_read);
			system_info_display(info_read,linenumber);
			info_file_del_file(localfile);
		}
		else
		{
			cout<<"|--------- Do not update ! --------|"<<endl;
		}
		delay_time(10);
	}
	return 0;
}