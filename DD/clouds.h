#pragma once
#pragma comment( lib, "Clouds.lib")

extern "C" BOOL	WINAPI CloudS_DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);//Ʈ��LIB�ļ���ʼ��,������ǰ�����һ��
extern "C" int WINAPI Initialization(int cs_1,int i_1,char* cs_2,char* cs_3,int i_2);	//����������ʼ��
extern "C" int WINAPI Reg(char* cs_1);										//��������ע��
extern "C" int WINAPI Trial();								     	        //������������
extern "C" int WINAPI Discount(char* cs_1,int i_1);						    //���������۵�
extern "C" int WINAPI Tie(char* cs_1);										//�����������
extern "C" int WINAPI ISreg();									            //���������Ƿ�ע��
extern "C" char* WINAPI Tips();									    	    //��������ȡ������ʾ��Ϣ
extern "C" char* WINAPI QTime();									        //��������ȡ����ʱ��
extern "C" char* WINAPI JData();									        //��������ȡ��̬����
extern "C" int WINAPI Checktime();									        //��������ʱ��Ч��
extern "C" int WINAPI Timingbox(char* cs_1,int i_1);						//����������ʱ��Ϣ��
extern "C" char* WINAPI GetInfo(int i_1);									//��������ȡ�����Ϣ
extern "C" char* WINAPI Inquiry(char* cs_1,int i_1);							//���������Ʋ�ѯ
extern "C" int WINAPI Areg(int cs_1,char* cs_2,char* cs_3,char* cs_4,int i_1);	     	//���������Զ�ע��
extern "C" int WINAPI SetServer(int cs_1);	     	//���������л���������·