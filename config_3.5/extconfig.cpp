#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int new_config_get[10000],count_of_new=0,have_new_config=0,ini_line=0,length;//判断服务器上有没有新的config文件
	char  local_all[10000],local_not_read[10000],local_read[10000],local_internal[10000],local_not_test[10000],command[10000],local_ini[10000];
	string temp,PATH;
	fstream config_all,config_not_read,config_read,config_internal,config_not_test;
	fstream config_ini;
	string localfile[100];
	