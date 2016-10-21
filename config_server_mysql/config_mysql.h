#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <mysql.h>
#include <errmsg.h>
#include <mysql_version.h>
#include <iostream>
using namespace std;

#define DBUG
#define SERVER_HOST "10.63.220.2"
#define USER "mengwei_root"
#define PASS "mengwei"

#define DB_NAME "config"
#define TABLE_SER "server"
#define TABLE_CLI "client"
#define VIEW_SER "server_status"
#define VIEW_CLI "client_status"

int init_db(MYSQL *mysql);
int check_tbl(MYSQL *mysql,char *name);
int check_db(MYSQL *mysql,char *db_name);
int select_db(MYSQL *mysql,char *db_bane);
int find_db(MYSQL *mysql,char *db_name);
int find_table(MYSQL *mysql,char *table_name);
int read_table(MYSQL *mysql,char *table_name);

//int find_ip_pro_line(MYSQL *mysql,string table,string valuse[100]);

int insert_into_table(MYSQL *mysql,string table_name,string values_insert[100],int count);
int find_one_tab(MYSQL *mysql,string table,string line_name);
string find_ip_pro_line_status(MYSQL *mysql,string table,string insert_values[100]);
//int find_ip_pro_line(MYSQL *mysql,string table,string insert_values[100],int num,string path);
int  find_one_tab_form_where(MYSQL *mysql,string table,string line_name,string from,string f_where);


int find_ip_pro_line(MYSQL *mysql,string table,string project,string path);

int update_table_one_line(MYSQL *mysql,string table,string find_value[100]);