#include "config_mysql.h"
#include <iostream>

using namespace std;
extern string result_find_tab_line[1000];
void test_mysql(MYSQL *mysql)
{
	string insert_values[100];
	
	insert_values[0] = "10.63.220.7";
	insert_values[1] = "P852F52";
	insert_values[2] = "12345678";
	insert_values[3] = "NULL";
	insert_values[4] = "BUSY";
	if(!init_db(mysql))
	{
		cout<<"|-- connect successful ! "<<endl;
		if(find_db(mysql,DB_NAME) && select_db(mysql,DB_NAME) && find_table(mysql,TABLE_SER)&& find_table(mysql,TABLE_CLI))
		{
			read_table(mysql,TABLE_SER);
			read_table(mysql,TABLE_CLI);
			cout<<"|-- OK！ init over ！"<<endl;
		//	find_ip_pro_line(&mysql,TABLE_CLI,insert_values);
			int num_project = find_one_tab(mysql,TABLE_CLI,"project");
			//cout << num_project;
			for(int i=0;i<num_project;i++)
			{
				cout<<"|-- "<<result_find_tab_line[i];
			}

			//insert_into_table(&mysql,TABLE_SER,insert_values,5);
		}
	}
	//mysql_close(mysql);
}