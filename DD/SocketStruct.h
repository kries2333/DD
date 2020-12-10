#pragma once
#include "pch.h"

#define SOCKET_LINK 10 //连接服务端消息
#define SOCKET_USERINFO 11 //客户端->服务端 发送角色信息
#define SOCEKT_LOGIN_INFO 16 //登录信息
#define SOCKET_LOGIN_ACTION 18 //登录游戏命令
#define SOCKET_GAME_INFO	19 //游戏信息
#define SOCKET_GAME_SCRIPT_INFO	20 //执行游戏脚本
#define SOCKET_GAME_PAUSE_SCRIPT 22 //暂定当前脚本
#define SOCKET_GAME_LOGIN_INI_OK 23 //游戏通知到了账号输入界面
#define SOCKET_GAME_START_SCRIPT 24 //继续当前脚本
#define SOCKET_GAME_VALIDATE 25 //验证码
#define SOCKET_GAME_VALIDATE_RESULT 26 //验证码结果
#define SOCKET_GAME_SECURITY 27 //密保
#define SOCKET_LINK_重连 28 //连接服务端消息
#define SOCKET_GAME_STOP_SCRIPT 29 //停止脚本

#define SOCKET_MACHINE_INFO 100 //发送机器信息
#define SOCKET_UPDATA_SCRIPT_INFO	101//更新脚本


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
	bool   is_header;				//当前数据是否是包头
	int    length;					//当前需要数据长度
	DWORD  dwpacketID;				//数据ID

	TPkgInfo(bool header = true, int nID = 0, int len = sizeof(TPkgHeader)) : is_header(header), dwpacketID(nID), length(len) {}
	void Reset() { is_header = true, dwpacketID = 0, length = sizeof(TPkgHeader); }
	~TPkgInfo() {}
};

/*
*连接成功后，发送来的用户名和密码
*/
struct SocketRunInfo
{
	char tGameName[30];			//账号
	char tGamePWD[30];			//密码
	char tGameServerName[15];	//小区(服务器)名字
	char tRoleName[20];			//角色名
	char tGameScript[100];		//默认脚本名
	char tMenPai[20];			//门派
	char tState[100];			//状态信息
	char tGameWnd[10];			//窗口信息
	unsigned int tRoleLv;		//等级
	unsigned int tIndex;		//对应的游戏窗口下标
};

//多开信息
struct SocketMultiInfo
{
	int tMultiCount;
	SocketRunInfo tRunInfo[2];
};

//服务端发送信息
struct SocketFileHead {
	DWORD tPacketID;
	DWORD tFileSize;
};

//文件尾信息
struct SocketFileTail {
	char tFileName[128];
};