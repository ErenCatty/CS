// Rdt.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "TCPSender.h"
#include "TCPReceiver.h"
#include "GBNRdtSender.h"
#include "GBNRdtReceiver.h"
#include "SRRdtSender.h"
#include "SRRdtReceiver.h"


int main(int argc, char* argv[])
{
	/*int ch;
	RdtSender* ps;
	RdtReceiver* pr;
	cout << "GBN��1" << endl;
	cout << "S R: 2" << endl;
	cout << "TCP: 3" << endl;
	cout << "Ҫѡ���Э�飺";
	cin >> ch;
	if (ch == 1) {
		ps = new GBNRdtSender();
		pr = new GBNRdtReceiver();
	}
	else if (ch == 2) {
		ps = new SRRdtSender();
		pr = new SRRdtReceiver();
	}
	else {
		ps = new TCPRdtSender();
	    pr = new TCPRdteceiver();
	}*/
	RdtSender* ps = new TCPRdtSender();
	RdtReceiver* pr=new TCPRdtReceiver();
//	pns->setRunMode(0);  //VERBOSģʽ
	pns->setRunMode(1);  //����ģʽ
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("D:\\VS project\\Rdt\\Debug\\input.txt");
	pns->setOutputFile("D:\\VS project\\Rdt\\Debug\\output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
	delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete
	
	return 0;
}

