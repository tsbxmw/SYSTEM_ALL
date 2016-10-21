////main.cpp
//#include <stdio.h>
//#include <pthread.h>
//#include <assert.h>
//#include <iostream>
//using namespace std;
//#pragma comment(lib,"pthreadVC2.lib")
//void * Function_t(void* Param)
//{
//	printf("是线程1\n");
//	pthread_t myid=pthread_self();
//	printf("线程id =%d",myid);
//	return NULL;
//}
//void * Function_t1(void* Param)
//{
//	printf("是线程2\n");
//	pthread_t myid=pthread_self();
//	printf("线程id =%d",myid);
//	return NULL;
//}
//int main()
//{
//	pthread_t pid;
//	pthread_attr_t attr;
//	pthread_attr_init(&attr);
//	pthread_attr_setscope(&attr,PTHREAD_SCOPE_PROCESS);
//	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
//	while(1)
//	{
//		pthread_create(&pid,&attr,Function_t, NULL);
//		
//	
//
//	pthread_create(&pid,&attr,Function_t1,NULL);
//	printf("========================================\n");
//	getchar();
//	cout<<pthread_attr_destroy(&attr)<<endl;
//	}
//	return 0;
//}

//
//#include <pthread.h>
//#include <stdio.h>
//#include <iostream>
//using namespace std;
//#pragma comment(lib,"pthreadVC2.lib")
//#define NUM_THREADS 55
//
//void *printhello(void *threadid)
//{
//	int tid;
//	tid = (int) threadid;
//	cout<<"this is hello : id = "<<tid<<endl;
//	pthread_exit(NULL);
//	return NULL;
//}
//int main()
//{
//	pthread_t threads[NUM_THREADS];
//	int rc,t;
//	for(t=0;t<NUM_THREADS;t++)
//	{
//		cout<<"in main:creating thread \n"<<t<<endl;
//		rc= pthread_create(&threads[t],NULL,printhello,(void *)t);
//		if(rc)
//		{
//			cout<<"error:"<<rc<<endl;
//			exit(-1);
//		}
//	}
//	pthread_exit(NULL);
//}
#include <iostream>
#include <pthread.h>//按规矩不能少
#pragma comment(lib,"pthreadVC2.lib")

using namespace std;

#define NUM_THREADS 10

int sum = 0;//定义个全局变量，让所有线程进行访问，这样就会出现同时写的情况，势必会需要锁机制；
pthread_mutex_t sum_mutex;
pthread_cond_t tasks_cond;
void* say_hello(void* args)
{
	while(1)
	{
		cout << "hello in thread " << *((int *)args) << endl;
		pthread_mutex_lock (&sum_mutex);//修改sum就先加锁，锁被占用就阻塞，直到拿到锁再修改sum；
		if(sum<20)
		{
			
			cout << "before sum is " << sum << " in thread " << *((int *)args) << endl;
			sum += *((int *)args);
			cout << "after sum is " << sum << " in thread " << *((int *)args) << endl;
		}
		else if(1)
		{
			
		}
		pthread_mutex_unlock (&sum_mutex);//完事后解锁，释放给其他线程使用;
		pthread_exit(0);//退出随便扔个状态码
		
		
	}
}
void* say_hello2(void *args)
{
	while(1)
	{
		if(sum<20)
		{
			cout<<sum<<endl;
		}
	}
}

int main()
{
    pthread_t tids[NUM_THREADS];
    int indexes[NUM_THREADS];
    //下三句是设置线程参数没啥可说的
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init (&sum_mutex, NULL);//这句是对锁进行初始化，必须的；

    for(int i = 0; i < NUM_THREADS; ++i)
    {
        indexes[i] = i;
        int ret = pthread_create( &tids[i], &attr, say_hello, (void *)&(indexes[i]) );//5个进程去你们去修改sum吧哈哈；
        if (ret != 0)
        {
           cout << "pthread_create error: error_code=" << ret << endl;
        }
    }

    pthread_attr_destroy(&attr);//删除参数变量

    void *status;
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int ret = pthread_join(tids[i], &status);
        if (ret != 0)
        {
            cout << "pthread_join error: error_code=" << ret << endl;
        }
    }

    cout << "finally sum is " << sum << endl;

    pthread_mutex_destroy(&sum_mutex);//注销锁，可以看出使用pthread内置变量神马的都对应了销毁函数，估计是内存泄露相关的吧；
}
//#include <iostream>
//#include <stdlib.h>
//#include <string>
//using namespace std;
//int main()
//{
//	string project_info_of_pc[1000][10];
//	char  get_project_name[100];
//	string project = "PROJECT\\P809V50";
//	int length = project.length()-8,temp=0;
//	cout<<length<<endl;
//
//
//	for(temp=0;temp<length;temp++)
//	{
//		get_project_name[temp]=project[temp+8];
//		cout<<project[temp+8];
//	}
//	get_project_name[temp]='\0';
//	cout<<get_project_name<<endl;
//	cout<<project<<endl;
//	//int j=0;
//	//for(int i=0;i<info_line_number;i++)
//	//{
//	//	if(info_line_get[i][1]==get_project_name)
//	//	{
//	//		if(info_line_get[i][3]=="NULL")
//	//		{
//	//			for(int k=0;k<STR_NUMBER;k++)
//	//			{
//	//				if(k==0 || k==3)
//	//					project_info_of_pc[j][k/2]=info_line_get[i][k];
//	//			}
//	//			j++;
//	//		}
//	//	}
//	//}
//	return 0;
//}