#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"

class SRRdtReceiver :public RdtReceiver
{
private:
	int base;       //�����
	int NextSeqNum;	// �ڴ��յ�����һ���������
	Packet lastAckPkt;				//�ϴη��͵�ȷ�ϱ���
	Packet ReceivedPacket[SEQLENGTH];		//�ѷ��Ͳ��ȴ�Ack�����ݰ�
	bool packetWaitingFlags[SEQLENGTH];
public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:

	void receive(const Packet& packet);	//���ձ��ģ�����NetworkService����
};

#endif

