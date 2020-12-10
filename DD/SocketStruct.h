#pragma once
#include "pch.h"

#define SOCKET_LINK 10 //���ӷ������Ϣ
#define SOCKET_USERINFO 11 //�ͻ���->����� ���ͽ�ɫ��Ϣ
#define SOCEKT_LOGIN_INFO 16 //��¼��Ϣ
#define SOCKET_LOGIN_ACTION 18 //��¼��Ϸ����
#define SOCKET_GAME_INFO	19 //��Ϸ��Ϣ
#define SOCKET_GAME_SCRIPT_INFO	20 //ִ����Ϸ�ű�
#define SOCKET_GAME_PAUSE_SCRIPT 22 //�ݶ���ǰ�ű�
#define SOCKET_GAME_LOGIN_INI_OK 23 //��Ϸ֪ͨ�����˺��������
#define SOCKET_GAME_START_SCRIPT 24 //������ǰ�ű�
#define SOCKET_GAME_VALIDATE 25 //��֤��
#define SOCKET_GAME_VALIDATE_RESULT 26 //��֤����
#define SOCKET_GAME_SECURITY 27 //�ܱ�
#define SOCKET_LINK_���� 28 //���ӷ������Ϣ
#define SOCKET_GAME_STOP_SCRIPT 29 //ֹͣ�ű�

#define SOCKET_MACHINE_INFO 100 //���ͻ�����Ϣ
#define SOCKET_UPDATA_SCRIPT_INFO	101//���½ű�


struct TPkgHeader
{
	DWORD dwpacketID;
	int	  body_len;
};

struct SocketMachineInfo
{
	TCHAR tMachineName[20];
};

struct TPkgInfo
{
	bool   is_header;				//��ǰ�����Ƿ��ǰ�ͷ
	int    length;					//��ǰ��Ҫ���ݳ���
	DWORD  dwpacketID;				//����ID

	TPkgInfo(bool header = true, int nID = 0, int len = sizeof(TPkgHeader)) : is_header(header), dwpacketID(nID), length(len) {}
	void Reset() { is_header = true, dwpacketID = 0, length = sizeof(TPkgHeader); }
	~TPkgInfo() {}
};

/*
*���ӳɹ��󣬷��������û���������
*/
struct SocketRunInfo
{
	char tGameName[30];			//�˺�
	char tGamePWD[30];			//����
	char tGameServerName[15];	//С��(������)����
	char tRoleName[20];			//��ɫ��
	char tGameScript[100];		//Ĭ�Ͻű���
	char tMenPai[20];			//����
	char tState[100];			//״̬��Ϣ
	char tGameWnd[10];			//������Ϣ
	unsigned int tRoleLv;		//�ȼ�
	unsigned int tIndex;		//��Ӧ����Ϸ�����±�
};

//�࿪��Ϣ
struct SocketMultiInfo
{
	int tMultiCount;
	SocketRunInfo tRunInfo[2];
};

//����˷�����Ϣ
struct SocketFileHead {
	DWORD tPacketID;
	DWORD tFileSize;
};

//�ļ�β��Ϣ
struct SocketFileTail {
	char tFileName[128];
};