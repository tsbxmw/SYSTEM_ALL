#include "config.h"
#include "config_mysql.h"

int  main()
{
	string localfile[100];
	int start_second;
	
	MYSQL mysql ;

	localfile[0]="echo Y | ";
	localfile[1]="copy  ";//��������
	localfile[2]=" configfile_all\\";//all_config dir
	localfile[3]=" config_not_read\\";//config not read dir
	localfile[4]=" config_read\\";//config already read dir
	localfile[5]="move  ";//�ƶ�����
	localfile[6]="E:\\version\\P809V50\\P809V50.zip";//���ذ汾����ļ���(Ĭ��)
	localfile[7]=" config_not_test\\";//δ���Եİ汾·��
	localfile[8]="10.63.220.2";
	localfile[9]="mw1101";
	localfile[10]="mw1101";
	localfile[11]="..\\Config_upload\\";
	localfile[12]="del ";
	localfile[13]="\\CI_version\\config_files";
	localfile[14]="M_P809V50*";
	localfile[15]="P809V50";
	localfile[16]="10.63.202.2";
	localfile[17]="10.63.220.7";
	localfile[18]="";

	while(1)	
	{
			mysql_test(&mysql);
			start_second = config_ftp_mail(localfile,&mysql);
			if(start_second)
				break;
			delay_time(5);
	}
	system("pause");
	return 0;
}
