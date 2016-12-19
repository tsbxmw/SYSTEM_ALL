 /* the new delay function to use mysql
  * something new for cpu time delay
  */



#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "config_mysql.h"
using namespace std;

#define Into_Mail_or_Nomail 0
#define DELAY_TIME 1200


int config_ftp_mail(string localfile[100],MYSQL *mysql);                                   
//defined in the config_ftp_mail.cpp

int config_ftp_nomail(string localfile[100]);                                
//defined in the config_ftp_nomail.cpp

void refresh_configname();													  
//defined in the function.app

void refresh_read_not_read();												  
//used by the config_ftp_mail() and config_ftp_nomail()

void open_config_ini(string localfile[100]);								  
//refresh the config_ini

void create_getconfig_cfg(string localfile[100]);	
//create the getconfig.cfg

void config_init();															  
//init config_file

void delay_time(int time);

char * removepath(char x[10000],int length);								  
//see the resources.

void make_new_info(string loaclfile[100]);
//add new info 

bool read_server_status(string localfile[100]);
// read the server status from mysql

void upload_status_toserver();
//upload local status to the mysql

void get_pc_status_from_server(string localfile[100]);
//get the status from the mysql

void set_server_status_null(string localfile[100]);
//set the local pc is free to the mysql


void del_pc_status_on_server(string localfile[100]);
// delete the pc status on the mysql

void mkdir_project_onserver(string localfile[100],MYSQL *mysql);
//make a dir of the project on the server

string getconfigname(char local_internal[1000]);
//get local config of the configini

void  mysql_test(MYSQL *mysql);