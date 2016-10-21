/*
 * config.h
 * inlude all functions used in the main or others
 * new functions should be clear here
 * the new file should be update 
 * reduce the crash times.
 * the new delay function to use 
 * something new for cpu time delay
*/



#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;

#define Into_Mail_or_Nomail 0
#define DELAY_TIME 10


int config_ftp_mail(string localfile[100],string project,string path_file);                                   
//defined in the config_ftp_mail.cpp

int config_ftp_nomail(string localfile[100]);                                
//defined in the config_ftp_nomail.cpp

void refresh_configname(string project);													  
//defined in the function.app

void refresh_read_not_read(string project);												  
//used by the config_ftp_mail() and config_ftp_nomail()

void update_project_ini();
//update the project_info.ini file in the PROJECT dir

void open_config_ini(string localfile[100],string project);								  
//refresh the config_ini

void create_getconfig_cfg(string localfile[100],string project);	
//create the getconfig.cfg

void config_init();															  
//init config_file

void delay_time(int time);

char * removepath(char x[10000],int length);								  
//see the resources.

int open_project_config_ini(string localfile[100]);

