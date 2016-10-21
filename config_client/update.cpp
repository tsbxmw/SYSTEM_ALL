        
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

void main()
{
	
	fstream update;
	char update_new[30];
	string version ,newversion;
	cout<< "[][]-- check for update ! --[][]" <<endl;
	//\\10.63.220.2\every_build\SOURCE\client_update\update.ini
	update.open("\\\\10.63.220.2\\every_build\\SOURCE\\client_update\\update.ini");
	while(update.getline(update_new,30,'\n')
	{
		version = strtok(update_new,"_");
		newversion = strtok(NULL,"_");
		if(newversion == "new")
		{
			cout<<"[][]-- there has new version on server , download now ! --[][]"<<endl;
			system("copy \\\\10.63.220.2\\every_build\\SOURCE\\client_update\\config_client.exe .\\");
			break;
		}
	}

}