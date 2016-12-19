#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <mysql.h>
#include <errmsg.h>
#include <mysql_version.h>
#include "config_mysql.h"
#include <iostream>
#include <time.h>
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


//find db

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

//select db to use

int select_db(MYSQL *mysql,char * db_name)
{
	if(!mysql_select_db(mysql,db_name))
		return 1;
	else
		return 0;
}

//find table to use

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

// read the table

int read_table(MYSQL *mysql,char *table_name)
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
				while(i<4)
				{
					cout<<row[i]<<"-";
					i++;
				}
				cout<<row[4];
				cout<<endl;
			}
		}
	}
	return 0;
}

// find one table

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
	return num;
}


//add where to from and table
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




// find the ip and pro line

//....................................................................................................


int find_ip_pro_line(MYSQL *mysql,string table,string project,string path)
{

	int res,res_s;
	int judge_client = 0 , server_ju = 0;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	int res_c,count_ip = 0;//ip counts;
	MYSQL_ROW row_c = NULL;
    MYSQL_RES *res_mysql_c = NULL;
	int sta_cli_num = 0;
	MYSQL_ROW row_s = NULL;
	MYSQL_RES *res_mysql_s = NULL;
	int values = 0;
	int values_into = 0;
	//select ip from client  where pro = 'values'
	string client_ip[100][4];//[0] = ipaddress ; [1] = id_phone ; [2] = status_phone

	//项目相关
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	string buff_c = "select ip_address,id_phone,status_phone from client where (project=\'"+project+"\')";
	string buff_s;
	string ip_add_sta[100];

	cout<<"|-- debug : iam in the client select ip id sp"<<endl;
	cout<<"|-- "<<buff_c<<endl;
	res_c = mysql_query(mysql,buff_c.c_str());
	cout<<"<-- " + res_c;
	if(!res_c)
	{
		res_mysql_c = mysql_store_result(mysql);
		if(mysql_num_rows(res_mysql_c)==0)
		{
			cout<<"|-- do not find the line , insert it"<<endl;
			cout<<"|-- error !"<<endl;
		}
		else
		{
			if(res_mysql_c)
			{
				
			//	cout<<mysql_num_rows(res_mysql)<<endl;
				cout<<"|-- find the ips : ";
				while(row_c = mysql_fetch_row(res_mysql_c))
				{
					client_ip[count_ip][0] = row_c[0];
					client_ip[count_ip][1] = row_c[1];
					client_ip[count_ip][2] = row_c[2];
					count_ip++;
				}
			}
		}
	}
	else
	{
		cout<<"|-- error "<<res<<endl;
	}
	//ip相关
	/////////////////////////////////////////////////////.......................................................................
	cout<<"|-- debug : iam in the client select ip count_ip =  "<< count_ip-1<<endl;
	for(int i=0;i<count_ip ;i++)
	{
		buff_s = "select status_phone from client where (ip_address = \'"+client_ip[i][0] +"\')";
		cout<<"|-- "+buff_s<<endl;
		res_s = mysql_query(mysql,buff_s.c_str());
		int j = 0;
		if(!res_s)
		{
			res_mysql_s = mysql_store_result(mysql);
			sta_cli_num = mysql_num_rows(res_mysql_s);
			if(res_mysql_s)
			{
				while(row_s = mysql_fetch_row(res_mysql_s))
				{
					cout<<"<-- debug : row-s = "<<row_s[0]<<endl;
					string temp = row_s[0];
					if(temp == "BUSY")
					{
						j=1;
						break;
					}
				}
			}
		}
		else
			cout<<"|-- error"<<endl;
		cout<<"|-- debug j = "<<j<<endl;
		if(j==0 && values_into==0)
		{
			client_ip[i][3] = "NULL";
			values_into ++ ;
		}
		else
			client_ip[i][3] = "BUSY";
		cout<<"|-- debug : client - ip = " << client_ip[i][3]<<endl;
	}
	//.........................................................................................................................
	cout<<"|-- debug : iam in the client select  insert into ip and pro"<<endl;
	for(int i =0;i<count_ip;i++)
	{
		string buff = "select * from ";
		string find_value[100];
		buff = buff + table;
		find_value[0] = client_ip[i][0];
		find_value[1] = project;
		find_value[2] = client_ip[i][1];
		find_value[3] = client_ip[i][2];
		find_value[4] = client_ip[i][3];
		find_value[5] = path;
		
		if(values == 0 && client_ip[i][3] =="NULL")
		{
			find_value[4] =="NULL";
			values++;
		}

		buff = buff + " where (ip_address =\'"+client_ip[i][0]+"\') and (project=\'"+project+"\')";
		cout<<"|-- "<<buff <<"--|"<<endl;
		res = mysql_query(mysql,buff.c_str());
		if(!res)
		{
			res_mysql = mysql_store_result(mysql);
			if(mysql_num_rows(res_mysql)==0)
			{

				cout<<"|-- do not find the line , insert it"<<endl;
				insert_into_table(mysql,table,find_value,6);
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
						while(i<5)
						{
							cout<<row[i]<<"-";
							i++;
						}
						cout<<row[5];
						cout<<endl;
					}
					cout<<"|-- update the line !"<<endl;
					update_table_one_line(mysql,table,find_value);

				}
			}
		}
		else
		{
			cout<<"|-- error "<<res<<endl;
		}
		values ++;
	}
		return 0;
}
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

int update_table_one_line(MYSQL *mysql,string table,string find_value[100])
{
	int res;
	MYSQL_ROW row = NULL;
    MYSQL_RES *res_mysql = NULL;
	string buff = "update ";
	buff = buff + table;
	buff = buff + " set id_phone =\'"+find_value[2] +"\',status_phone=\'"+find_value[3]+"\',status_pc=\'"+find_value[4]+"\',path_version=\'"+find_value[5]+"\' where (ip_address=\'"+find_value[0]+"\' and project=\'"+find_value[1]+"\')" ;
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