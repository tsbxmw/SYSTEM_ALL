/* 

*client and server do the double check on the ftp server.
*server will do the commander
*client to check the new file and start test
*author : mw10192582


*/

#include "config.h"
#include "config_mysql.h"
extern string result_find_tab_line[1000];
int  main()
{

	string localfile[100],project;
	string temp = "PROJECT\\";
	string path_file;
	string value_mysql[100];
	int pro_num=18;
	int control;
	MYSQL mysql ;
	test_mysql(&mysql);
	localfile[0]="echo Y | ";
	localfile[1]="copy  ";//¿½±´ÃüÁî
	localfile[2]=" "+project+"\\configfile_all\\";//all_config dir
	localfile[3]=" "+project+"\\config_not_read\\";//config not read dir
	localfile[4]=" "+project+"\\config_read\\";//config already read dir
	localfile[5]="move  ";//ÒÆ¶¯ÃüÁî
	localfile[6]="E:\\version\\P809V50\\P809V50.zip";//±¾µØ°æ±¾´æ·ÅÎÄ¼þ¼Ð(Ä¬ÈÏ)
	localfile[7]=" "+project+"\\config_not_test\\";//Î´²âÊÔµÄ°æ±¾Â·¾¶
	localfile[8]="10.63.220.2";
	localfile[9]="mw1101";
	localfile[10]="mw1101";
	localfile[11]="..\\Config_upload\\";
	localfile[12]="del ";
	localfile[13]="\\CI_version\\config_files";
	localfile[14]="M_P809V50*";
	localfile[15]="infofile.info";
	localfile[16]="infofile_open.info";
	localfile[17]="-";



	//while(1)
	//{

	//	control = open_project_config_ini(localfile);

	//	pro_num=18;
	//	while(control >= 0)
	//	{//if has the project name
	//		cout<<endl<<"<-- This is the "+localfile[pro_num]+" Project !"<<endl;
	//		project = temp + localfile[pro_num];
	//		localfile[2]=" "+project+"\\configfile_all\\";//all_config dir
	//		localfile[3]=" "+project+"\\config_not_read\\";//config not read dir
	//		localfile[4]=" "+project+"\\config_read\\";//config already read dir
	//		localfile[7]=" "+project+"\\config_not_test\\";//Î´²âÊÔµÄ°æ±¾Â·¾¶
	//		config_ftp_mail(localfile,project,path_file,&mysql);
	//		pro_num ++;
	//		delay_time(20);
	//		control --;
	//	}
	//	
	//	cout<<endl<<"<-- In the NEXT-100s , you can add the new project ! -->"<<endl;
	//	delay_time(DELAY_TIME);
	//	
	//}
	//return 0;
	
	while(1)
	{
		int num_project = find_one_tab(&mysql,TABLE_CLI,"project");
		//control = open_project_config_ini(localfile);

		pro_num=18;
		int i = 0;
		while(num_project > 0)
		{//if has the project name
			cout<<endl<<"<-- This is the "+result_find_tab_line[i]+" Project !"<<endl;
			project = temp + result_find_tab_line[i];
			localfile[2]=" "+project+"\\configfile_all\\";//all_config dir
			localfile[3]=" "+project+"\\config_not_read\\";//config not read dir
			localfile[4]=" "+project+"\\config_read\\";//config already read dir
			localfile[7]=" "+project+"\\config_not_test\\";//Î´²âÊÔµÄ°æ±¾Â·¾¶
			config_ftp_mail(localfile,project,path_file,&mysql);
			i ++;
			num_project --;
			delay_time(5);
		}
		
		cout<<endl<<"<-- In the NEXT-100s , you can add the new project ! -->"<<endl;
		delay_time(DELAY_TIME);
		
	}
	return 0;
}

