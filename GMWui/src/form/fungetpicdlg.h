#ifndef FUNGETPICDLG_H
#define FUNGETPICDLG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QtDebug>
#include "mythreadpic.h"

namespace Ui {
	class FunGetPicDlg;
}

class FunGetPicDlg : public QDialog
{
	Q_OBJECT

public:
	explicit FunGetPicDlg(QWidget *parent = nullptr);
	~FunGetPicDlg();

	MyThreadPic thread;
	void initform();
private:
	QString dir_rom;
	QString dir_srcpic;
	QString dir_despic;
//	QStringList list_rom;
//	QStringList list_srcpic;
//	QStringList list_despic;
	QMap<QString,QFileInfo> map_rom;
	QMap<QString,QFileInfo> map_srcpic;
	QFileInfoList flist_rom;
	QFileInfoList flist_srcpic;
private slots:
	bool listrefresh();
	bool subclear(QString path);
	void pressShow(int value);
	void threadStop();
	void on_PB1_rom_clicked();
	void on_PB2_srcpic_clicked();
	void on_PB3_despic_clicked();
	void on_PB4_out_clicked();


private:
	Ui::FunGetPicDlg *ui;
};

#endif // FUNGETPICDLG_H
