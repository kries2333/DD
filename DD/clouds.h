#pragma once
#pragma comment( lib, "Clouds.lib")

extern "C" BOOL	WINAPI CloudS_DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);//飘零LIB文件初始化,必须在前面调用一次
extern "C" int WINAPI Initialization(int cs_1,int i_1,char* cs_2,char* cs_3,int i_2);	//中文名：初始化
extern "C" int WINAPI Reg(char* cs_1);										//中文名：注册
extern "C" int WINAPI Trial();								     	        //中文名：试用
extern "C" int WINAPI Discount(char* cs_1,int i_1);						    //中文名：扣点
extern "C" int WINAPI Tie(char* cs_1);										//中文名：解绑
extern "C" int WINAPI ISreg();									            //中文名：是否注册
extern "C" char* WINAPI Tips();									    	    //中文名：取操作提示信息
extern "C" char* WINAPI QTime();									        //中文名：取到期时间
extern "C" char* WINAPI JData();									        //中文名：取静态数据
extern "C" int WINAPI Checktime();									        //中文名：时间效验
extern "C" int WINAPI Timingbox(char* cs_1,int i_1);						//中文名：定时信息框
extern "C" char* WINAPI GetInfo(int i_1);									//中文名：取软件信息
extern "C" char* WINAPI Inquiry(char* cs_1,int i_1);							//中文名：云查询
extern "C" int WINAPI Areg(int cs_1,char* cs_2,char* cs_3,char* cs_4,int i_1);	     	//中文名：自动注册
extern "C" int WINAPI SetServer(int cs_1);	     	//中文名：切换服务器线路