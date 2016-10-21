/*
 * config.h
 * inlude all functions used in the main or others
 * new functions should be clear here
*/



#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;







int config_ftp_mail();                                   //defined in the config_ftp_mail.cpp
int config_ftp_nomail();                                 //defined in the config_ftp_nomail.cpp
void refresh_configname();                               //defined in the function.app
void refresh_read_not_read();                            //used by the config_ftp_mail() and config_ftp_nomail()
void open_config_ini();									 //refresh the config_ini
void create_getconfig_cfg();							 //create the getconfig.cfg
void config_init();										 //init config_file
char * removepath(char x[10000],int length);             //see the resources.

