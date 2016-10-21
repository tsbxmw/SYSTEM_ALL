/*
 * author    : mw10192582
 * function  : to find the strs in the txt or other types file 
 * date      : 20160125
 * version   : v2.0
 * contect   : 
*/



#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;


int main()

{
	char temp[1000];
	char ls[10][7];
	string ctest[10];
	int j=0;
	system("adb devices > devices.txt");
	fstream out;
	out.open("devices.txt");

	while(out.getline(temp,100,'\n'))
	{
		int i=0,xxx=0;
		while( i<7)
		{

			if(temp[i]<'f')
			{
				cout<<temp[i]<<endl;
				ls[j][i]=temp[i];
				i++;
				
			}
			else 
			{
				xxx=1;
				break;
			}
			if(xxx==0 && i==7)
			{
				j++;
			}
		}

	}
	out.close();
	cout<<ls[0];
	ctest[0]=ls[0];
	system(("echo "+ctest[j]+" >devices.txt").c_str());

}