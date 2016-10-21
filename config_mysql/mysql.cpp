#include "config_mysql.h"
#include <iostream>

using namespace std;
extern string result_find_tab_line[1000];
void main()
{
	string insert_values[100];
	
	insert_values[0] = "10.63.220.7";
	insert_values[1] = "P852F52";
	insert_values[2] = "12345678";
	insert_values[3] = "NULL";
	insert_values[4] = "BUSY";
	insert_values[5] = "10.63.220.2";
	insert_values[6] = "P852F52";
	insert_values[7] = "12345678";
	insert_values[8] = "NULL";
	insert_values[9] = "BUSY";
	MYSQL mysql ;
	if(!init_db(&mysql))
	{
		cout<<"|-- connect successful ! "<<endl;
		if(find_db(&mysql,DB_NAME) && select_db(&mysql,DB_NAME) && find_table(&mysql,TABLE_SER)&& find_table(&mysql,TABLE_CLI))
		{
			read_table(&mysql,TABLE_SER);
			read_table(&mysql,TABLE_CLI);
			cout<<"|-- OK！ init over ！"<<endl;
			find_ip_pro_line(&mysql,TABLE_CLI,insert_values);
			int num_project = find_one_tab(&mysql,TABLE_CLI,"project");

			//cout << num_project;
			for(int i=0;i<num_project;i++)
			{
				cout<<"|-- "<<result_find_tab_line[i] <<endl;
			}
			num_project = find_one_tab_form_where(&mysql,TABLE_SER,"status_phone","ip_address",insert_values[0]);
			num_project = find_one_tab_form_where(&mysql,TABLE_SER,"status_phone","ip_address",insert_values[5]);
			//cout << num_project;
			for(int i=0;i<num_project;i++)
			{
				cout<<"|-- "<<result_find_tab_line[i]<<endl;
			}
			update_table_one_line(&mysql,TABLE_SER,"status_phone","BUSY","ip_address",insert_values[5]);
			//insert_into_table(&mysql,TABLE_SER,insert_values,5);
		}
	}
	mysql_close(&mysql);
}