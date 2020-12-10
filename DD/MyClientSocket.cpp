#include "pch.h"
#include "MyClientSocket.h"
#include "SocketStruct.h"

const USHORT MyClientSocket::PORT = 12138;


MyClientSocket::MyClientSocket() :m_Client(this)
{

}

MyClientSocket::~MyClientSocket()
{
	MyStop();
}

bool MyClientSocket::MyStart()
{
	if (m_Client->Start(ADDRESS, PORT))
	{
		TRACE("发起连接成功\n");
		m_Client->SetSocketBufferSize(1024 * 4096);
		return true;
	}      
	else {
		return false;
	}
}

void MyClientSocket::MyStop()
{
	m_Client->Stop();
}

bool MyClientSocket::MyConnect()
{
	return false;
}

void MyClientSocket::MyDisconnect()
{
}

void MyClientSocket::MySendPackets(DWORD dwpacketID, int body_len, char* Socketbody)
{
	TPkgHeader header;
	header.dwpacketID = dwpacketID;
	header.body_len = body_len;

	WSABUF bufs[2];
	bufs[0].len = sizeof(TPkgHeader);
	bufs[0].buf = (char*)&header;
	bufs[1].len = body_len;
	bufs[1].buf = Socketbody;
	m_Client->SendPackets(bufs, 2);
}

bool MyClientSocket::MyIsConnected()
{
	return m_Client->IsConnected();
}

void MyClientSocket::HandlePacket(CONNID dwConnID, DWORD dwPacketID, CBufferPtr pbuffer)
{
	CString Text;
	switch (dwPacketID)
	{
	//////////////////////////////////////////////////////////////////////////
	case SOCKET_UPDATA_SCRIPT_INFO:
	{
		//更新文件
		
		TPkgHeader *FileHead;
		SocketFileTail *FileTail;
		int size = pbuffer.Size();
		char* bufs;
		bufs = (char*)pbuffer.Ptr();
		FileHead = (TPkgHeader*)bufs;
		FileTail = (SocketFileTail*)(bufs + FileHead->body_len + sizeof(TPkgHeader));
		TRACE("文件大小:%d 文件名字:%s\n", FileHead->body_len, FileTail->tFileName);
		CString FilePath = "C:\\";
		CFile fp;
		char* file = (char*)pbuffer.Ptr() + sizeof(TPkgHeader);
		//memcpy(file, pbuffer.Ptr() + sizeof(TPkgHeader), size);
		fp.Open(FilePath + FileTail->tFileName, CFile::modeWrite| CFile::modeCreate);
		fp.Write(file, FileHead->body_len);
		fp.Close();
		//delete file;
	}
	break;
	//////////////////////////////////////////////////////////////////////////
	case SOCKET_USERINFO:
	{
		//游戏的角色属性信息

	}
	default:
		break;
	}
}

EnServiceState MyClientSocket::MyGetState()
{
	return m_Client->GetState();
}

EnHandleResult MyClientSocket::OnPrepareConnect(ITcpClient* pSender, CONNID dwConnID, SOCKET socket)
{
	TRACE("正在连接中控\n");
	return EnHandleResult();
}

EnHandleResult MyClientSocket::OnConnect(ITcpClient* pSender, CONNID dwConnID)
{
	TRACE("可以发送数据了\n");
	return EnHandleResult();
}

EnHandleResult MyClientSocket::OnHandShake(ITcpClient* pSender, CONNID dwConnID)
{
	TRACE("连接中控成功\n");
	SocketMachineInfo MachineInfo = { 0 };
	strcpy(MachineInfo.tMachineName, m_MachineName.GetBuffer());
	MySendPackets(SOCKET_MACHINE_INFO, sizeof(SocketMachineInfo), (char*)&MachineInfo);
	return EnHandleResult();
}

EnHandleResult MyClientSocket::OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength)
{
	TRACE("收到中控通知\n");
	int required = m_pkgInfo.length;
	int remain = iLength;
	m_pkgInfo.Reset();
	while (remain >= required)
	{
		//remain -= required;
		CBufferPtr buffer(required);
		EnFetchResult result = m_Client->Peek(buffer, (int)buffer.Size());
		if (result == FR_OK)
		{
			if (m_pkgInfo.is_header)
			{
				TPkgHeader* pHeader = (TPkgHeader*)buffer.Ptr();
				m_pkgInfo.dwpacketID = pHeader->dwpacketID;
				if (pHeader->dwpacketID == SOCKET_UPDATA_SCRIPT_INFO) {
					required = pHeader->body_len + m_pkgInfo.length + sizeof(m_pkgFileTail);
				}
				else {
					required = pHeader->body_len + m_pkgInfo.length;
				}
				//接收到只有单纯的包ID这种类型的包
				if (required == 0)
				{
					required = sizeof(TPkgHeader);
					m_pkgInfo.is_header = false;
					HandlePacket(dwConnID, m_pkgInfo.dwpacketID, (CBufferPtr)NULL);
				}
				TRACE("包体大小%d\n", pHeader->body_len);
				if (iLength < pHeader->body_len) {
					m_pkgFileHead.tFileSize = pHeader->body_len;
					break;
				}
				else {
					TRACE("接收到完整包\n");
				}
			}
			else
			{
				remain -= required;
				result = m_Client->Fetch(buffer, (int)buffer.Size());
				if (result == FR_OK) {
					HandlePacket(dwConnID, m_pkgInfo.dwpacketID, buffer);
					required = sizeof(TPkgHeader);
					m_pkgInfo.dwpacketID = NULL;
				}
			}
			m_pkgInfo.is_header = !m_pkgInfo.is_header;
			m_pkgInfo.length = required;
		}
	}

	return EnHandleResult();
}

EnHandleResult MyClientSocket::OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return EnHandleResult();
}

EnHandleResult MyClientSocket::OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	return EnHandleResult();
}
