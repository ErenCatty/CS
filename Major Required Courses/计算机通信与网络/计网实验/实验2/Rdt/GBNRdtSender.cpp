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
	if (this->waitingState) { //发送方处于等待确认状态
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
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].acknum = -1;//忽略该字段
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].seqnum = this->expectSequenceNumberSend;
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].checksum = 0;
		memcpy(this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);

		pUtils->printPacket("发送方发送报文", this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);
		if (base == expectSequenceNumberSend)
		{
			cout << "启动发送方定时器" << endl;
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);			//启动发送方定时器
		}

		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
		expectSequenceNumberSend++;
		//cout << "expectSequenceNumberSend变更：" << expectSequenceNumberSend << endl;
		if (expectSequenceNumberSend == base + N)
			this->waitingState = true;										//进入等待状态
	}
	return true;
}

void GBNRdtSender::receive(const Packet& ackPkt) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确，并且确认序号=发送方已发送并等待确认的数据包序号
	if (checkSum == ackPkt.checksum && ackPkt.acknum >=base) {
		int old_base = base;
		
		pUtils->printPacket("发送方正确收到确认", ackPkt);
		base = ackPkt.acknum + 1;
		for (int i = base + N; i < base + SEQLENGTH; i++)
			packetWaitingAck[i % SEQLENGTH].seqnum = -1;
		cout << "发送方滑动窗口：";
		for (int i = base; i < base + N; i++) {
			if (packetWaitingAck[i % SEQLENGTH].seqnum == -1)
				cout << 'X' << ' ';
			else
				cout << packetWaitingAck[i % SEQLENGTH].seqnum << ' ';
		}
		cout << ' ' << endl;
		if (base == expectSequenceNumberSend) {
			cout << "分组已全部正确发送，关闭计时器。" << endl;
			this->waitingState = false;
			pns->stopTimer(SENDER, old_base);		//关闭定时器
		}
		else {
			pns->stopTimer(SENDER, old_base);									//首先关闭定时器
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);			//重新启动发送方定时器
		}
	}
	else {
		if (checkSum != ackPkt.checksum)
			cout << "发送方未收到正确ACK，继续等待..." << endl;
		else
			cout << "发送方未收到期待的ACK，继续等待..." << endl;
	}
}

void GBNRdtSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	cout << "发送超时，回溯N个包。" << endl;
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//重新启动发送方定时器
	int i = base;
	do {
		cout << "将重新发送" << i << "号报文" << endl;
		pUtils->printPacket("发送方定时器时间到，重发报文", this->packetWaitingAck[i% SEQLENGTH]);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[i % SEQLENGTH]);			//重新发送数据包
		i++;
	} while (i != expectSequenceNumberSend);
}
