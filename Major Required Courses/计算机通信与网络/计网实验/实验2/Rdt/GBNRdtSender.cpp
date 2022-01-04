#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"


GBNRdtSender::GBNRdtSender() :base(0), expectSequenceNumberSend(0), waitingState(false)
{
}


GBNRdtSender::~GBNRdtSender()
{
}



bool GBNRdtSender::getWaitingState() {
	return waitingState;
}




bool GBNRdtSender::send(const Message& message) {
	if (this->waitingState) { //���ͷ����ڵȴ�ȷ��״̬
		return false;
	}
	
	if (flag == 1)
	{
		for (int i = 0; i < SEQLENGTH; i++)
		{
			this->packetWaitingAck[i].seqnum = -1;
		}
		flag = 0;
	}

	if (expectSequenceNumberSend < base + N)
	{
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].acknum = -1;//���Ը��ֶ�
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].seqnum = this->expectSequenceNumberSend;
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].checksum = 0;
		memcpy(this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);

		pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);
		if (base == expectSequenceNumberSend)
		{
			cout << "�������ͷ���ʱ��" << endl;
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);			//�������ͷ���ʱ��
		}

		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
		expectSequenceNumberSend++;
		//cout << "expectSequenceNumberSend�����" << expectSequenceNumberSend << endl;
		if (expectSequenceNumberSend == base + N)
			this->waitingState = true;										//����ȴ�״̬
	}
	return true;
}

void GBNRdtSender::receive(const Packet& ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (checkSum == ackPkt.checksum && ackPkt.acknum >=base) {
		int old_base = base;
		
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		base = ackPkt.acknum + 1;
		for (int i = base + N; i < base + SEQLENGTH; i++)
			packetWaitingAck[i % SEQLENGTH].seqnum = -1;
		cout << "���ͷ��������ڣ�";
		for (int i = base; i < base + N; i++) {
			if (packetWaitingAck[i % SEQLENGTH].seqnum == -1)
				cout << 'X' << ' ';
			else
				cout << packetWaitingAck[i % SEQLENGTH].seqnum << ' ';
		}
		cout << ' ' << endl;
		if (base == expectSequenceNumberSend) {
			cout << "������ȫ����ȷ���ͣ��رռ�ʱ����" << endl;
			this->waitingState = false;
			pns->stopTimer(SENDER, old_base);		//�رն�ʱ��
		}
		else {
			pns->stopTimer(SENDER, old_base);									//���ȹرն�ʱ��
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);			//�����������ͷ���ʱ��
		}
	}
	else {
		if (checkSum != ackPkt.checksum)
			cout << "���ͷ�δ�յ���ȷACK�������ȴ�..." << endl;
		else
			cout << "���ͷ�δ�յ��ڴ���ACK�������ȴ�..." << endl;
	}
}

void GBNRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	cout << "���ͳ�ʱ������N������" << endl;
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ��
	int i = base;
	do {
		cout << "�����·���" << i << "�ű���" << endl;
		pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط�����", this->packetWaitingAck[i% SEQLENGTH]);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[i % SEQLENGTH]);			//���·������ݰ�
		i++;
	} while (i != expectSequenceNumberSend);
}
