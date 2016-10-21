#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <mysql.h>
#include <errmsg.h>
#include <mysql_version.h>
#include "config_mysql.h"
#include <iostream>
#include "config.h"
using namespace std;
string result_find_tab_line[1000];


int init_db(MYSQL *mysql)
{
	int err = 0;
	if(!mysql_init(mysql))
	{
		perror("|-- mysql init: ......");
		exit(1);
	}

	if(!mysql_real_connect(mysql,SERVER_HOST,USER,PASS,NULL,0,NULL,0))
	{
		perror("|-- error : mysql_real_connect");
		exit(1);
	}
	printf("|-- connectting now ...... \n");
	return 0;
}
int colse_db(MYSQL *mysql)
{
	mysql_close(mysql);
}

int check_db(MYSQL *mysql,char *db_name)
{
	MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;
	res = mysql_list_dbs(mysql,NULL);
    if(res)
	{
        while((row=mysql_fetch_row(res))!=NULL)
		{
			//printf("db is %s\n",row[0]);
			if(strcmp(row[0],db_name)==0)
			{
				cout<< "|-- find db [ "<<db_name<<" ]"<<endl;
				break;
			}
		}
			//mysql_list_dbs会分配内存，需要使用mysql_free_result释放  
		mysql_free_result(res);
	}
	if(!row)//没有这个数据库，则建立  
	{
		char buf[128]={0};
		strcpy(buf,"|-- CREATE DATABASE ");
		strcat(buf,db_name);
#ifdef DEBUG
		printf("|-- %s\n",buf);
#endif
		if(mysql_query(mysql,buf)){
			//fprintf(stderr,"Query failed (%s)\n",mysql_error(mysql));
		exit(1);
		}
	}
	return 0;
}

int find_db(MYSQL *mysql,char * db_name)
{
	MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;
    res=mysql_list_dbs(mysql,NULL);
	int xxx = 0;
	if(res)
	{
        while((row=mysql_fetch_row(res))!=NULL)
		{
			//printf("db is %s\n",row[0]);
			if(strcmp(row[0],db_name)==0)
			{
				cout<<"|-- find db [ "<<db_name<<" ]"<<endl;
				xxx = 1;
				string buff = "use ";
				buff = buff + db_name;
				mysql_query(mysql,buff.c_str());
				break;
			}
		}
			//mysql_list_dbs会分配内存，需要使用mysql_free_result释放  
		mysql_free_result(res);
	}
	if(xxx == 0)
	{
		cout<<"|-- do not find the db! "<<endl;
		return 0;
	}
	else
		return 1;
}
int select_db(MYSQL *mysql,char * db_name)
{
	if(!mysql_select_db(mysql,db_name))
		return 1;
	else
		return 0;
}
int find_table(MYSQL *mysql,char * table_name)
{
	MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;
    res=mysql_list_tables(mysql,NULL);
	int xxx = 0;
	if(res)
	{
        while((row=mysql_fetch_row(res))!=NULL)
		{
			//printf("table is %s\n",row[0]);
			if(strcmp(row[0],table_name)==0)
			{
				cout<<"|-- find table [ "<<table_name<<" ]"<<endl;
				xxx =1 ;
				break;
			}
		}
			//mysql_list_dbs会分配内存，需要使用mysql_free_result释放  
		mysql_free_result(res);
	}
	if(xxx ==0)
	{
	cout<<"|-- do not find the table! "<<endl;
	return 0;
	}
	else
		return 1;
}

int read_table(MYSQL *mysql,char *table_name,int number)
{
	int res;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	char buff[128] = "select * from ";
	strcat(buff,table_name);
	cout<<"|-- TABLE　"<<table_name;
	res = mysql_query(mysql,buff);
	if(res)
	{
		cout<<"|-- error"<<endl;
	}
	else
	{
		res_mysql = mysql_store_result(mysql);
		if(res_mysql)
		{
		
			cout<<" lines : "<<mysql_num_rows(res_mysql)<<endl;
			int j = 0;
			while(row = mysql_fetch_row(res_mysql))
			{
				int i=0;
				cout<<"|--   "<<j+1<<"  ";
				j++;
				while(i<number-1)
				{
					cout<<row[i]<<"-";
					i++;
				}
				cout<<row[number-1];
				cout<<endl;
			}
		}
	}
	return 0;
}

int  find_one_tab(MYSQL *mysql,string table,string line_name)
{
	int res;
	int num;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string buff = "select distinct "+ line_name;
	buff = buff + " from ";
	buff = buff + table;
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	if(!res)
	{
		res_mysql = mysql_store_result(mysql);
		int num = (int)mysql_num_rows(res_mysql);
		cout<<"|-- project numer is "<<num<<endl;
		if((int)num==0)
		{
			cout<<"|-- do not find the line "<<endl;
		}
		else
		{
			if(res_mysql)
			{
				int i=0;

			//	cout<<mysql_num_rows(res_mysql)<<endl;
				cout<<"|-- find the tab line : ";

				while(row = mysql_fetch_row(res_mysql))
				{
					cout<<row[0]<<" ";
					result_find_tab_line[i]=row[0];
					i++;
				}
				cout<<endl;
				return num;
			}

		}
	}
	else
	{
		cout<<"|-- error "<<res<<endl;
		return num;
	}

}
//....................................................................................................................
int  find_one_tab_form_where(MYSQL *mysql,string table,string line_name,string from,string f_where)
{
	int res;
	int num;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string buff = "select distinct "+ line_name;
	buff = buff + " from ";
	buff = buff + table + " where "  + from + "=\'"+f_where+"\'";
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	if(!res)
	{
		res_mysql = mysql_store_result(mysql);
		int num = (int)mysql_num_rows(res_mysql);
		cout<<"|-- result numer is "<<num<<endl;
		if((int)num==0)
		{
			cout<<"|-- do not find the line "<<endl;
		}
		else
		{
			if(res_mysql)
			{
				int i=0;

			//	cout<<mysql_num_rows(res_mysql)<<endl;
				cout<<"|-- find the tab line : ";

				while(row = mysql_fetch_row(res_mysql))
				{
					cout<<row[0]<<" ";
					result_find_tab_line[i]=row[0];
					i++;
				}
				cout<<endl;
				return num;
			}

		}
	}
	else
	{
		cout<<"|-- error "<<res<<endl;
		return num;
	}

}
//...................................................................................................................




int find_ip_pro_line(MYSQL *mysql,string table,string insert_values[100])
{
	int res;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string insert_into[100];
	insert_into[0] = insert_values[17];
	insert_into[1] = insert_values[15];
	insert_into[2] = "12345678";
	insert_into[3] = "NULL";
	insert_into[4] = "ON";
	string buff = "select * from ";
	buff = buff + table;
	buff = buff + " where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
	//buff = buff + " where (ip_address =\'10.63.220.2\')";
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	cout<<"<-- debug : "<<res<<endl;
	if(!res )
	{
		res_mysql = mysql_store_result(mysql);
		cout<<"<-- debug : "<<mysql_num_rows(res_mysql)<<endl;
		if(mysql_num_rows(res_mysql)==0)
		{
			cout<<"|-- do not find the line , insert it"<<endl;
			

			insert_into_table(mysql,table,insert_into,5);
		}
		else
		{
			if(res_mysql)
			{
		
			//	cout<<mysql_num_rows(res_mysql)<<endl;
				cout<<"|-- find the line : ";
				while(row = mysql_fetch_row(res_mysql))
				{
					int i=0;
					while(i<4)
					{
						cout<<row[i]<<"-";
						i++;
					}
					cout<<row[4];
					cout<<endl;
				}
			}
			while(update_table_one_line(mysql,TABLE_CLI,"status_phone","NULL","ip_address",insert_into[0],insert_into[1]))
			{
				Sleep(1000);
			}
			while(update_table_one_line(mysql,TABLE_CLI,"phone_ison","ON","ip_address",insert_into[0],insert_into[1]))
			{
				Sleep(1000);
			}
		}
	}
	else
	{
		cout<<"|-- error "<<res<<endl;
	}
	return res;
}

string find_ip_pro_line_status(MYSQL *mysql,string table,string insert_values[100])
{
	int res,res_p;
	string result;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;	
	MYSQL_ROW row_p = NULL;
    MYSQL_RES *res_mysql_p = NULL;
	string insert_into[100];
	string path_version;
	insert_into[0] = insert_values[17];
	insert_into[1] = insert_values[15];
	string buff = "select status_pc from ";
	buff = buff + table;
	buff = buff + " where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
	string buff_p = "select path_version from "+table+" where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
	//buff = buff + " where (ip_address =\'10.63.220.2\')";
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	cout<<"<-- debug : "<<res<<endl;
	if(!res )
	{
		res_mysql = mysql_store_result(mysql);
		cout<<"<-- debug : "<<mysql_num_rows(res_mysql)<<endl;
		if(mysql_num_rows(res_mysql)==0)
		{
			cout<<"|-- do not find the line ! wait for server"<<endl;
		}
		else
		{
			if(res_mysql)
			{
		
			//	cout<<mysql_num_rows(res_mysql)<<endl;
				cout<<"|-- find the line : ";
				while(row = mysql_fetch_row(res_mysql))
				{
					result = row[0];
					cout<<"|-- "<<row[0];
					cout<<endl;
				}
			}
		}
	}
	else
	{
		cout<<"|-- error "<<res<<endl;
	}

	if(result == "NULL")
	{
		cout<<"|-- this is the path "<<endl;
		cout<<"|-- buff_p:"<<buff_p<<endl;
		res_p = mysql_query(mysql,buff_p.c_str());
		cout<<"<-- debug : "<<res_p<<endl;
		if(!res_p )
		{
			res_mysql_p = mysql_store_result(mysql);
			cout<<"<-- debug : "<<mysql_num_rows(res_mysql_p)<<endl;
			if(mysql_num_rows(res_mysql_p)==0)
			{
				cout<<"|-- do not find the line ! wait for server"<<endl;
			}
			else
			{
				if(res_mysql_p)
				{
		
				//	cout<<mysql_num_rows(res_mysql)<<endl;
					cout<<"|-- find the line : ";
					while(row_p = mysql_fetch_row(res_mysql_p))
					{
						path_version = row_p[0];
						cout<<"|-- "<<row_p[0];
						cout<<endl;
					}
					while(update_table_one_line(mysql,TABLE_CLI,"status_phone","BUSY","ip_address",insert_values[17],insert_values[15]))
					{
						Sleep(1000);
					}
					return path_version;
				}
			}
		}
		else
		{
			cout<<"|-- error "<<res<<endl;
		}
	}
	return "NULL";
}
//..................................................................................................
string get_path(MYSQL *mysql,string table,string insert_values[100])
{
	int res;
	string result;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string insert_into[100];
	insert_into[0] = insert_values[17];
	insert_into[1] = insert_values[15];
	insert_into[2] = "12345678";
	insert_into[3] = "NULL";
	insert_into[4] = "ON";
	string buff = "select status_pc from ";
	buff = buff + table;
	buff = buff + " where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
	//buff = buff + " where (ip_address =\'10.63.220.2\')";
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	cout<<"<-- debug : "<<res<<endl;
	if(!res )
	{
		res_mysql = mysql_store_result(mysql);
		cout<<"<-- debug : "<<mysql_num_rows(res_mysql)<<endl;
		if(mysql_num_rows(res_mysql)==0)
		{
			cout<<"|-- do not find the line ! wait for server"<<endl;
		}
		else
		{
			if(res_mysql)
			{
		
			//	cout<<mysql_num_rows(res_mysql)<<endl;
				cout<<"|-- find the line : ";
				while(row = mysql_fetch_row(res_mysql))
				{
					result = row[0];
					cout<<"|-- "<<row[0];
					cout<<endl;
				}
			}
		}
	}
	else
	{
		cout<<"|-- error "<<res<<endl;
	}
	return result;
}
//..................................................................................................
int insert_into_table(MYSQL *mysql,string table_name,string values_insert[100],int count)
{
	int res;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string buff = "insert into ";
	buff = buff + table_name;
	buff = buff + " values(\"" ;
	for(int i=0;i<count-1;i++)
		buff = buff + values_insert[i]+"\",\"";
	buff = buff + values_insert[count-1]+"\")";
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	if(res)
	{
		cout<<"|-- error "<<endl;
		return 1;
	}
	else
	{
		cout<<"|-- insert ok "<<endl;
	}
	
	return 0;
}

//......................................................................................................................
int update_table_one_line(MYSQL *mysql,string table,string line_name,string line_status,string from,string f_where,string project)
{
	int res;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string buff = "update ";
	buff = buff + table;
	buff = buff + " set " + line_name + "=\""+line_status + "\" where ("+from +"=\'"+f_where+"\' and project=\'"+project+"\')";
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	if(res)
	{
		cout<<"|-- error "<<endl;
	}
	else
	{
		cout<<"|-- update success !"<<endl;
	}
	return res;
}

//.........................................................................................................................................
int  find_ip_pro_line_config(MYSQL *mysql,string table,string insert_values[100])
{
	int res,res_p;
	string result;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;	
	MYSQL_ROW row_p = NULL;
    MYSQL_RES *res_mysql_p = NULL;
	string insert_into[100];
	string path_version;
	insert_into[0] = insert_values[17];
	insert_into[1] = insert_values[15];
	insert_into[2] = insert_values[6];
	insert_into[3] = insert_values[8];
	insert_into[4] = insert_values[9];
	insert_into[5] = insert_values[10];
	insert_into[6] = insert_values[11];
	insert_into[7] = insert_values[13];
	insert_into[8] = insert_values[14];
	insert_into[9] = insert_values[15];
	insert_into[10] = insert_values[16];
	insert_into[11] = insert_values[17];
	string buff = "select * from ";
	buff = buff + table;
	buff = buff + " where (project=\'"+insert_values[15]+"\')";
	//string buff_p = "select path_version from "+table+" where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
	//buff = buff + " where (ip_address =\'10.63.220.2\')";
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	cout<<"<-- debug : "<<res<<endl;
	if(!res )
	{
		res_mysql = mysql_store_result(mysql);
		cout<<"<-- debug : "<<mysql_num_rows(res_mysql)<<endl;
		if(mysql_num_rows(res_mysql)==0)
		{
			cout<<"|-- do not find the line ! insert into lines "<<endl;
			insert_into_table(mysql,table,insert_into,12);
		}
		else
		{
			if(res_mysql)
			{
			//	cout<<mysql_num_rows(res_mysql)<<endl;
				cout<<"|-- find the line : ";
				while(row = mysql_fetch_row(res_mysql))
				{
					cout<<"|-- ";
					for(int i=0;i<11;i++)
						cout<<row[i]<<"-";
					cout<<row[11]<<endl;
				}
				update_table_config(mysql,"config",insert_values);
			}
		}
	}
	else
	{
		cout<<"|-- error "<<res<<endl;
	}

	return 0;
}

int update_table_config(MYSQL *mysql,string table,string find_value[100])
{
	int res;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string buff = "update ";
	buff = buff + table;
	buff = buff + " set lcoal_version_path =\'"+find_value[6] +"\',ftp_ip_address=\'"+find_value[8]+"\',ftp_user=\'"+find_value[9]+"\',ftp_password=\'"+find_value[10]+"\',local_upload_path=\'"+find_value[11]+"\',ftp_config_path=\'"+find_value[13]+"\',config_pre_name=\'"+find_value[14]+"\',project_name_config=\'"+find_value[15]+"\',server_ip_address=\'"+find_value[16]+"\',local_ip_address=\'"+find_value[17]+"\' where (ip_address=\'"+find_value[17]+"\' and project=\'"+find_value[15]+"\')" ;
	cout<<"|-- "<<buff<<endl;
	res = mysql_query(mysql,buff.c_str());
	if(res)
	{
		cout<<"|-- error "<<endl;
	}
	else
	{
		cout<<"|-- update success !"<<endl;
	}
	return res;
}