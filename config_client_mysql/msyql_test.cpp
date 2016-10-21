#include "config_mysql.h"
#include <iostream>

using namespace std;
extern string result_find_tab_line[1000];
void mysql_test(MYSQL *mysql)
{
	string insert_values[100];
	if(!init_db(mysql))
	{
		cout<<"|-- connect successful ! "<<endl;
		if(find_db(mysql,DB_NAME) && select_db(mysql,DB_NAME) && find_table(mysql,TABLE_SER)&& find_table(mysql,TABLE_CLI))
		{
			read_table(mysql,TABLE_SER,6);
			read_table(mysql,TABLE_CLI,5);
			read_table(mysql,TABLE_CON,11);
			cout<<"|-- OK£¡ init over £¡"<<endl;
		}
	}
}