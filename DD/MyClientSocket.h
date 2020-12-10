#pragma once
#include "HpSocket/HPSocket.h"
#include "HpSocket/bufferptr.h"
#include "SocketStruct.h"
class MyClientSocket : CTcpPullClientListener
{
public:
	MyClientSocket();
	~MyClientSocket();
public:
	bool MyStart();
	void MyStop();
	bool MyConnect();
	void MyDisconnect();
	void MySendPackets(DWORD dwpacketID, int body_len, char* Socketbody);

	bool MyIsConnected();

	void HandlePacket(CONNID dwConnID, DWORD dwPacketID, CBufferPtr pbuffer);
	EnServiceState MyGetState();
private:
	// 5. process network events
	virtual EnHandleResult OnPrepareConnect(ITcpClient* pSender, CONNID dwConnID, SOCKET socket);
	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID);
	virtual EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID);
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength);
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);

public:
	CString m_MachineName;
	CString ADDRESS;
	TPkgInfo m_pkgInfo;
	SocketFileHead m_pkgFileHead;
	SocketFileTail m_pkgFileTail;
private:
	static const USHORT PORT;

	CTcpPullClientPtr m_Client;
	CString m_strAddress;
};

