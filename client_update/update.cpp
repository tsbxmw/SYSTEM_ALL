        
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;



void delay_time(int time)
{
	cout<<"|--  ";
	for(int i=0;i<=time;i++)
	{
		Sleep(1000);

		int j=i%60;
		int mins = i/60;
		cout<<"¡ö";
	}
	cout<<"       --|"<<endl;
}
int  success_fail()
{
	fstream client;
	char client_str[30];
	string client_local;
	system("dir /o /b .\\ > client.ini");
	client.open("client.ini");
	while(client.getline(client_str,30,'\n'))
	{
		client_local = client_str;
		if(client_local == "config_client.exe")
		{	
			return 1;
		}
	}
	return 0;
}
void main()
{
	
	fstream update;
	char update_new[30];
	string version ,newversion;
	cout<< "[_________________________]" <<endl;
	cout<< "|-- check for update !  --|" <<endl;

	//\\10.63.220.2\every_build\SOURCE\client_update\update.ini
	update.open("\\\\10.63.220.2\\every_build\\SOURCE\\client_update\\update.ini");
	while(update.getline(update_new,30,'\n'))
	{
		version = strtok(update_new,"_");
		newversion = strtok(NULL,"_");
		if(newversion == "new")
		{
			cout<<"|-- new version: "+version+"    --|"<<endl;
			cout<<"|-- download now !      --|"<<endl;
			delay_time(5);
			system("@echo Y | copy  \\\\10.63.220.2\\every_build\\SOURCE\\client_update\\config_client.exe .\\");
			if(success_fail)
			{
				cout<<"|-- update success!     --|"<<endl;

			}
			else
			{
				cout<<"|-- update failed !     --|"<<endl;
			}
			cout<< "[_________________________]" <<endl;
			cout<<endl;
			break;
		}
	}

}