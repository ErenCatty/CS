#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"

class SRRdtReceiver :public RdtReceiver
{
private:
	int base;       //基序号
	int NextSeqNum;	// 期待收到的下一个报文序号
	Packet lastAckPkt;				//上次发送的确认报文
	Packet ReceivedPacket[SEQLENGTH];		//已发送并等待Ack的数据包
	bool packetWaitingFlags[SEQLENGTH];
public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:

	void receive(const Packet& packet);	//接收报文，将被NetworkService调用
};

#endif

