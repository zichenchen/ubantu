#include <iostream>
#include "MyTcpListener.h"
#include"CommonUtil.h"
#include "Dao.h"
using namespace std;
MyTcpListener* Client=MyTcpListener::getInstance();

int main()
{
	Dao* db=Dao::getInstance();
	db->initDB("localhost", "root", "zi666666", "gateway_phcx");

	////开始连接到服务器
	if (Client->startClient())
	{	
		do
		{
			if (Client->getStatus()== SS_STOPPING|| Client->getStatus() == SS_STOPPED) {
				break;
			}
		} while (true);
	}
	else
	{
		cout << "连接服务器失败!" << endl;
	}
	system("pause");
	
	return 0;
}