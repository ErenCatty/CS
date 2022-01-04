#include "stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"


SRRdtSender::SRRdtSender() :base(0), expectSequenceNumberSend(0), waitingState(false)
{
	for (int i = 0; i < SEQLENGTH; i++) {
		ACKFlags[i] = false;
	}

}


SRRdtSender::~SRRdtSender()
{
}



bool SRRdtSender::getWaitingState() {
	return waitingState;
}




bool SRRdtSender::send(const Message& message) {
	if (this->waitingState) { //���ͷ����ڵȴ�ȷ��״̬
		return false;
	}

	if (expectSequenceNumberSend < base + N) {

		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].acknum = -1; //���Ը��ֶ�
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].seqnum = this->expectSequenceNumberSend;
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].checksum = 0;
		memcpy(this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);
		ACKFlags[expectSequenceNumberSend % SEQLENGTH] = false;

		pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);

		cout << "����" << expectSequenceNumberSend << "���ͷ�������ʱ��" << endl;
		pns->startTimer(SENDER, Configuration::TIME_OUT, expectSequenceNumberSend);			//�������ͻ����з���ʱ��

		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
		expectSequenceNumberSend++;

		cout << "�˱��ķ��ͺ�expectSequenceNumberSendΪ" << expectSequenceNumberSend << endl;
		if (expectSequenceNumberSend == base + N) {
			this->waitingState = true;//����ȴ�״̬
		}
	}
	return true;
}

void SRRdtSender::receive(const Packet& ackPkt) {

	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (checkSum == ackPkt.checksum) {
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		for (int i = base + N; i < base + 8; i++) {

			packetWaitingAck[i % SEQLENGTH].seqnum = -1;
		}
		cout << "���ͷ�������������: ";
		for (int i = base; i < base + N; i++) {
			if (packetWaitingAck[i % SEQLENGTH].seqnum == -1) {
				cout << 'X' << ' ';
			}
			else {
				cout << packetWaitingAck[i % SEQLENGTH].seqnum << ' ';
			}
		}
		cout << endl;
		if (ackPkt.acknum == base) {
			cout << "��ȷ��ACK���Ϊ" << ackPkt.acknum << "��ACK" << endl;
			pns->stopTimer(SENDER, ackPkt.acknum);
			ACKFlags[base % SEQLENGTH] = true;
			while (ACKFlags[base % SEQLENGTH]) {
				ACKFlags[base++ % SEQLENGTH] = false;
			}
			waitingState = false;
		}
		else if (ackPkt.acknum > base && !ACKFlags[ackPkt.acknum % SEQLENGTH]) {
			cout << "��ȷ��ACK���Ϊ" << ackPkt.acknum << "��ACK" << endl;
			pns->stopTimer(SENDER, ackPkt.acknum);
			ACKFlags[ackPkt.acknum % SEQLENGTH] = true;
		}
		else
		{
			cout << "�յ�����Ҫ�����е�ACK,�����ȴ�" << endl;
		}

	}
	else cout << "���ͷ��յ���ACK��" << endl;

}

void SRRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	cout << "���ͳ�ʱ" << endl;
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	cout << "�ط�" << seqNum << "�ű���" << endl;
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط�����", this->packetWaitingAck[seqNum % SEQLENGTH]);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum % SEQLENGTH]);			//���·������ݰ�

}

