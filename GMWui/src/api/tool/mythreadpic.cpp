#include "mythreadpic.h"

MyThreadPic::MyThreadPic()
{

}


void MyThreadPic::run()
{
	QMap<QString,QFileInfo>::iterator it1 = m_map1.begin();
	QMap<QString,QFileInfo>::iterator it2 = m_map2.begin();
	QFileInfo fi;
	QFile file;
	float rate = 100.0/m_map1.count();
	float current = 0;
	while (it1 != m_map1.end())
	{
		int ss = QString::compare(it1.key(),it2.key());
		if(ss == 0)
		{	fi = it2.value();
			file.setFileName(fi.absoluteFilePath());

			file.copy(desdir +"/"+desfront+ fi.fileName()+desback);
			it1++;
			it2++;
			current += rate;
		}
		else if(ss >0)
		{
			it2++;
		}
		else
		{
			it1++;
			current += rate;
		}

		emit sendcurrent(current);
		if(it2 == m_map2.end())
		{
			break;
		}
	}
}

