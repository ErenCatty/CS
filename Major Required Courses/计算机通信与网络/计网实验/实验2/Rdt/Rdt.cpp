// Rdt.cpp : 定义控制台应用程序的入口点。
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
	cout << "GBN：1" << endl;
	cout << "S R: 2" << endl;
	cout << "TCP: 3" << endl;
	cout << "要选择的协议：";
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
//	pns->setRunMode(0);  //VERBOS模式
	pns->setRunMode(1);  //安静模式
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("D:\\VS project\\Rdt\\Debug\\input.txt");
	pns->setOutputFile("D:\\VS project\\Rdt\\Debug\\output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//指向唯一的工具类实例，只在main函数结束前delete
	delete pns;										//指向唯一的模拟网络环境类实例，只在main函数结束前delete
	
	return 0;
}

