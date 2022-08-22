#ifndef MYTHREADPIC_H
#define MYTHREADPIC_H

#include <QFileInfo>
#include <QMap>
#include <QThread>



class MyThreadPic : public QThread
{
	Q_OBJECT
public:
	MyThreadPic();

	QMap<QString,QFileInfo> m_map1;
	QMap<QString,QFileInfo> m_map2;
	QString desdir;
	QString desfront;
	QString desback;

protected:
	void run() override;

signals:
	void sendcurrent(int value);
};

#endif // MYTHREADPIC_H
