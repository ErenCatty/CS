#include "stdafx.h"
#include "Global.h"
#include "TCPSender.h"


TCPRdtSender::TCPRdtSender() :base(0), expectSequenceNumberSend(0), waitingState(false)
{
}


TCPRdtSender::~TCPRdtSender()
{
}



bool TCPRdtSender::getWaitingState() {
	return waitingState;
}




bool TCPRdtSender::send(const Message& message) {
	if (this->waitingState) { //发送方处于等待确认状态
		return false;
	}
	if (init_flag == 1) {
		for (int i = 0; i < SEQLENGTH; i++) {
			this->packetWaitingAck[i].seqnum = -1;
		}
		init_flag = 0;
	}
	if (expectSequenceNumberSend < base + N) {

		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].acknum = -1; //忽略该字段
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].seqnum = this->expectSequenceNumberSend;
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].checksum = 0;
		memcpy(this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);

		pUtils->printPacket("发送方发送报文", this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);
		if (base == expectSequenceNumberSend) {
			cout << "发送方启动计时器" << endl;
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);			//启动发送基序列方定时器
		}
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[expectSequenceNumberSend % SEQLENGTH]);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
		expectSequenceNumberSend++;
		cout << "此报文发送后，expectSequenceNumberSend为" << expectSequenceNumberSend << endl;
		if (expectSequenceNumberSend == base + N) {
			this->waitingState = true;//进入等待状态
		}
	}
	return true;
}

void TCPRdtSender::receive(const Packet& ackPkt) {

	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确，并且确认序号=发送方已发送并等待确认的数据包序号
	if (checkSum == ackPkt.checksum && ackPkt.acknum >= base) {

		int old_base = base;

		pUtils->printPacket("发送方正确收到确认", ackPkt);
		base = ackPkt.acknum + 1;
		for (int i = base + N; i < base + 8; i++) {
			int a = i % SEQLENGTH;
			packetWaitingAck[i % SEQLENGTH].seqnum = -1;
		}
		cout << "发送方滑动窗口内容为 ";
		for (int i = base; i < base + N; i++) {
			if (packetWaitingAck[i % SEQLENGTH].seqnum == -1) {
				cout << 'X' << ' ';
			}
			else {
				cout << packetWaitingAck[i % SEQLENGTH].seqnum << ' ';
			}
		}
		cout << endl;
		if (base == expectSequenceNumberSend)
		{
			cout << "已发送分组已全部接送，关闭计时器" << endl;
			this->waitingState = false;
			pns->stopTimer(SENDER, old_base);	//关闭定时器
		}
		else {
			pns->stopTimer(SENDER, old_base);//还没接收完，继续等待
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
			this->waitingState = false;
		}

	}
	else {

		if (ackPkt.acknum == lastack) {
			ACK_count++;
			if (ACK_count == 4) {
				cout << "接收了三个冗余的ACK，快速重传序号" << ackPkt.acknum + 1 << endl;
				pns->stopTimer(SENDER, ackPkt.acknum + 1);
				pns->startTimer(SENDER, Configuration::TIME_OUT, ackPkt.acknum + 1);
				pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[base % SEQLENGTH]);
			}
		}
		else {
			lastack = ackPkt.acknum;
			ACK_count = 1;
		}
		if (checkSum != ackPkt.checksum) {
			cout << "发送方收到的ACK损坏" << endl;
		}
		else {
			cout << "发送方没有收到正确的序号，继续等待" << endl;
		}
	}
	//}	
}

void TCPRdtSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	cout << "发送超时" << endl;
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	cout << "重发" << seqNum << "号报文" << endl;
	pUtils->printPacket("发送方定时器时间到，重发报文", this->packetWaitingAck[seqNum % SEQLENGTH]);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum % SEQLENGTH]);			//重新发送数据包



}
