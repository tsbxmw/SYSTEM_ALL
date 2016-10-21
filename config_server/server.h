#include <iostream>
#include <string>
#include <Windows.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define STR_NUMBER 5

#define FTP_GET true
	


void server_delay_time(int time);

bool info_file_copy_file(string localfile[100]);

bool info_file_del_file(string localfile[100]);

int info_file_read(string localfile[100],string info_line_get[1000][10]);

void system_info_display(string info_line_get[1000][10],int info_line_number);

int system_info_deal(string info_line_get[1000][10],int info_line_number,string project,string path_file);

int pc_info_find(string info_line_get[1000][10],string project_info_of_pc[1000][10],int info_line_number,int info_line_pc_number,char project[30],string path_file);

int write_client_status(string info_line_get[1000][10],string project_info_of_pc[1000][10],int pc_status[1000],char project[30],int temp,int info_line_number,string path_file);

void rewrite_info(int line_number,string info_line_get[1000][10],int info_line_number,string project,string project_info_of_pc);

void create_new_client_info(string info_line_get[1000][10],int info_line_number);

void refresh_pc_info(string localfile[100]);