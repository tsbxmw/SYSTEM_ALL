
/*
version  :    2.0
author   :    MW10192582
function :    build-function,send mail
date     :    2016.1.12
COR      :    ZTE
new      :    ������û���µ�config�ļ�ʱ�Ĵ���������
new      :    �����˶Եݹ�������ջ�Ĵ������Ƴ��ݹ���ã�����β�ݹ�ʹ�ã���ֹ����Ӧ������crash��
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;
#include "config.h"
#include "server.h"

extern string path_test;
extern string command_to_create_null;
extern string command_to_create_busy;

int config_ftp_mail(string localfile[100],string project,string path_file)
{
	cout<<"[1]----##---- This is the Success-Mail function ----##----[1]"<<endl;

	int new_config_get[1000],			//if have one is 1,that is have new config on the server
		count_of_new=0,					//all newconfig count number
		have_new_config=0,				//have new config or not
		length;							//�жϷ���������û���µ�config�ļ�

	char local_all[1000],				//the char * to save the string in the file txt.
		 local_not_read[1000],
		 local_read[1000],
		 local_internal[1000],
		 local_not_test[1000];                   

	string temp,						//the internal string which used to save the temp string like hello or world em...
		   PATH;						//to save the path string int the config file
	string path_file_test;

	string info_line_get[1000][10],info_line_get_after[1000][10];
	int info_line_number = 0;

	fstream config_all,					//input or output file to open the configfile to read the internal
			config_not_read,
			config_read,
			config_internal,
			config_not_test;

	
	open_config_ini(localfile,project);			//open the config_ini ,to read the config

	for(int i=0;i<1000;i++)
		new_config_get[i]=0;//��ʼ������Ϊ0

	create_getconfig_cfg(localfile,project);	//use the config to create the cfg file

	//cout<<localfile[10]<<endl;

#ifdef FTP_GET
	system("ftp -s:getconfig.cfg");
#endif
	//create a new getconfig.cfg


	refresh_configname(project);


	config_all.open(project+"\\filename_all.txt");

	while(config_all.getline(local_all,300,'\n'))//��ȡ�ļ��е�ÿһ��
	{
		
		cout<<local_all<<endl<<"<-- file";
		refresh_read_not_read(project);
		config_not_read.open(project+"\\filename_not_read.txt");
		config_read.open(project+"\\filename_read.txt");
		config_not_test.open(project+"\\filename_not_test.txt");

		int xxx=0,yyy=0,zzz=0;

		
		while(config_not_read.getline(local_not_read,300,'\n'))
		{
			
		//	cout<<(local_not_read == local_all)<<endl;
			if(!strcmp(local_not_read,local_all))
			{
				cout<<" �� is not read -->"<<endl;
				xxx=1;
				new_config_get[count_of_new]=0;
				break;
			}
				
		}
		
		while(config_not_test.getline(local_not_test,300,'\n'))
		{
			
		//	cout<<(local_not_read == local_all)<<endl;
			if(!strcmp(local_not_test,local_all))
			{
				cout<<" �� is not need test -->"<<endl;
				zzz=1;
				new_config_get[count_of_new]=1;
				break;
			}
			
		}

		while(config_read.getline(local_read,300,'\n'))
		{
			
		//	cout<<(local_read==local_all)<<endl;
			if(!strcmp(local_read,local_all))
			{
				cout<<" �� had readed -->"<<endl;
				yyy=1;
				new_config_get[count_of_new]=1;
				break;
			}
				
		}

		if(xxx==0 && yyy==0 && zzz==0)//�����������µ�config
		{
			cout<<" is the new config �� Downloading the file to the config_not_read dir() -->"<<endl;
			
			string filename=local_all;
			system((localfile[0]+localfile[1]+localfile[2]+filename+localfile[3]).c_str());//δ���ļ���config_all������config_not_read
			//config_not_read no !!!!!!!!!!!!!
		}
		
		count_of_new++;

		config_read.close();
		config_not_read.close();
		config_not_test.close();

		refresh_read_not_read(project);
	}

	config_all.close();

	cout<<"<-- All file counts  : "<<count_of_new<<" -->"<<endl;

	for(int i=0;i<count_of_new;i++)
	{
		if(new_config_get[i]==0)
		{
			have_new_config=1;//ֻҪ����
			break;
		}
	}

	if(have_new_config == 0) //��������û���µ�config
	{
		cout<<"<-- Not find the new config on the server ! -->"<<endl <<"<-- Waitting for upload ! -->"<<endl;
	
		cout<<"<-- Send Email ... -->"<<endl;
		system("call FailEmail.bat");
		//delay_time(DELAY_TIME);//delay func!

		//system("@for /L %j in (1,1,100) do   @ping -n 18 127.0.0.1 > null & @echo ============ %%j  ============ ");
		//system("call GetNewConfig.bat");
		//system("ftp_config_nomail.exe");

		/*-------*///while(config_ftp_nomail(localfile));
		//��ֹ����Ӧ�ñ������ڴ洦��

		//if while(0) return 0;
		//else if while(1) then while(1) until while(0);

		return 0;
	}
	else 
	{
		

		cout<< "<-- debug : before to display -->"<<endl;
		info_file_copy_file(localfile);
		int info_line_number_after = info_file_read(localfile,info_line_get_after);
		info_file_del_file(localfile);
		system_info_display(info_line_get_after,info_line_number_after);


		refresh_pc_info(localfile);

		info_file_copy_file(localfile);
		info_line_number = info_file_read(localfile,info_line_get);
		info_file_del_file(localfile);
		system_info_display(info_line_get,info_line_number);
	


		if(system_info_deal(info_line_get,info_line_number,project,path_file))
		{

			cout<< "<-- debug : after to display -->"<<endl;
			info_file_copy_file(localfile);
		    info_line_number_after = info_file_read(localfile,info_line_get_after);
			info_file_del_file(localfile);
			system_info_display(info_line_get_after,info_line_number_after);
		

			server_delay_time(10);

			refresh_read_not_read(project);

			config_not_read.open(project+"\\filename_not_read.txt");
	
			int n=0;
			while(config_not_read.getline(local_not_read,300,'\n'))
			{
				n++;
			}
			config_not_read.close();
			n=n-1;
			config_not_read.open(project+"\\filename_not_read.txt");
			while(n--)
			{
				config_not_read.getline(local_not_read,300,'\n');
				//     echo Y | move config_not_read\temp config_not_test\temp
				cout<<"<-- move the config "<<local_not_read<< " to the dir(config_not_test) -->"<<endl;
				//system("dir /o /b config_not_read");
				temp=local_not_read;
	
				system((localfile[0]+localfile[5]+localfile[3]+temp+localfile[7]+temp).c_str());

				system(("echo \"Didn't test!\" >>"+project+"\\config_not_test\\"+temp).c_str());

			}


			if(config_not_read.getline(local_not_read,300,'\n'))//��ȡconfig_not_read name�����1�У�Ȼ������ж�Ӧ��config�ļ���
			{                                                                                                                                                                                                                                
					config_not_read.close();
					refresh_read_not_read(project);
					temp=local_not_read;
					cout<<temp<<endl;
					length = localfile[8].length();
					cout<<"length="<<length<<endl;
					system((localfile[0]+localfile[5]+localfile[3]+temp+localfile[4]+temp).c_str());
					system((localfile[0]+localfile[1]+localfile[4]+temp+" "+localfile[11]+temp).c_str());
					//����config��������config_read�ļ���

					config_internal.open(project+"\\config_read\\"+temp);//�򿪶�Ӧ��config�ļ�
					config_internal.getline(local_internal,300,' ');//���ļ���һ��
				
					system("echo copy_begin_time=%date:~0,10% %time% >..\\config.config");

					PATH = removepath(local_internal,length);//��þ���·��PATH
					cout<<"<-- the path is : "<<PATH<<" -->"<<endl;
					cout<<"<-- the pathfile is in : " << path_file<<"-->"<<endl;
					cout<<"<-- the pathfile is in : " << path_test<<"-->"<<endl;
					system(command_to_create_null.c_str());
					system(("echo "+ PATH +" >> "+path_test).c_str());


					delay_time(20);

					system(command_to_create_busy.c_str());
					

					return 0;


					//��������õ���copy�����ȡconfig�ļ�������
					//system((localfile[0]+localfile[1]+PATH+localfile[6]).c_str());
					//�ӷ�������copy�ļ�������,�˴�ʹ��ftp
					system((localfile[12]+localfile[6]).c_str());
					//�� ɾ������֮ǰ�������ļ��汾��
					system("cd ..\\Config_upload");
					system("call upload.bat");
					system("cd ..\\01VersionDown");

					string newpath=PATH+" "+localfile[6]+">>autoftp.cfg";
					system(("echo open "+localfile[8]+"> autoftp.cfg").c_str());
					system(("echo "+localfile[9]+">> autoftp.cfg").c_str());
					system(("echo "+localfile[10]+">> autoftp.cfg").c_str());
					system(("echo get "+newpath).c_str());
					system("echo bye>> autoftp.cfg");
					system("ftp -s:autoftp.cfg");

					system("echo copy_end_time=%date:~0,10% %time% >>..\\config.config");

					system("call SuccessEmail.bat");

					//��SuccessEmail.bat : ������ѹ���غ���ļ�
			
			}
			else
			{
				cout<<"<-- Wrong config file ! -->"<<endl;
			}

			return 0;
			}
		return 0;
		}
}