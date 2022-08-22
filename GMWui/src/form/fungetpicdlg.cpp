#include "fungetpicdlg.h"
#include "ui_fungetpicdlg.h"




FunGetPicDlg::FunGetPicDlg(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FunGetPicDlg)
{
	ui->setupUi(this);
	initform();
}

FunGetPicDlg::~FunGetPicDlg()
{
	delete ui;
}

void FunGetPicDlg::initform()
{

	connect(&thread,SIGNAL(sendcurrent(int )),this,SLOT(pressShow(int )));
	connect(&thread,SIGNAL(finished()),this,SLOT(threadStop()));
}

bool FunGetPicDlg::listrefresh()
{
	if(dir_rom.isEmpty())
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("未选择rom目录！    "));
		return false;
	}
	QDir dir(dir_rom);
	flist_rom = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	if(flist_rom.empty())
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("rom目录为空      "));
		return false;
	}
	map_rom.clear();
	for (int i = 0;i <flist_rom.size();i++)
	{
		QString newname = ui->LE4_rom1->text()+flist_rom.at(i).baseName()+ui->LE4_rom2->text();
		map_rom.insert(newname,flist_rom.at(i));
	}

	if(dir_srcpic.isEmpty())
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("未选择原始图片目录！    "));
		return false;
	}
	dir.cd(dir_srcpic);
	flist_srcpic = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	if(flist_srcpic.empty())
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("原始图片目录为空      "));
		return false;
	}
	map_srcpic.clear();
	for (int i = 0;i <flist_srcpic.size();i++)
	{
		QString newname = ui->LE5_srcpic1->text()+flist_srcpic.at(i).baseName()+ui->LE5_srcpic2->text();
		map_srcpic.insert(newname,flist_srcpic.at(i));
	}

	return true;
}

bool FunGetPicDlg::subclear(QString path)
{
	if (path.isEmpty())
	{
		return false;
	}

	QDir dir(path);
	if(!dir.exists())
	{
		return true;
	}

	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
	QFileInfoList fileList = dir.entryInfoList();
	foreach (QFileInfo fi, fileList)
	{
		if (fi.isFile())
		{
			fi.dir().remove(fi.fileName());
		}
		else
		{
			subclear(fi.absoluteFilePath());
		}
	}
	return dir.rmpath(dir.absolutePath());
}

void FunGetPicDlg::pressShow(int value)
{
	ui->PB_progress->setValue(value);
}

void FunGetPicDlg::threadStop()
{
	if(thread.isRunning())
	{
		thread.quit();
		thread.wait();
	}
	ui->PB_progress->setValue(0);
	QMessageBox::information(this, tr("对话框"),tr("导出完成      "),tr("确定"));
}

void FunGetPicDlg::on_PB1_rom_clicked()
{
	QString dirold = ui->LE1_rom->text().left(ui->LE1_rom->text().lastIndexOf('/')+1);
	dir_rom = QFileDialog::getExistingDirectory(this,tr("文件对话框"),dirold);
	if(!dir_rom.isEmpty())
	{
		ui->LE1_rom->setText(dir_rom);
	}
}

void FunGetPicDlg::on_PB2_srcpic_clicked()
{
	QString dirold = ui->LE2_srcpic->text().left(ui->LE2_srcpic->text().lastIndexOf('/')+1);
	dir_srcpic = QFileDialog::getExistingDirectory(this,tr("文件对话框"),dirold);
	if(!dir_srcpic.isEmpty())
	{
		ui->LE2_srcpic->setText(dir_srcpic);
	}
}

void FunGetPicDlg::on_PB3_despic_clicked()
{
	QString dirold = ui->LE3_despic->text().left(ui->LE3_despic->text().lastIndexOf('/')+1);
	dir_despic = QFileDialog::getExistingDirectory(this,tr("文件对话框"),dirold);
	if(!dir_despic.isEmpty())
	{
		ui->LE3_despic->setText(dir_despic);
	}
}

void FunGetPicDlg::on_PB4_out_clicked()
{
	if(!listrefresh())
	{
		return;
	}
	if(dir_despic.isEmpty())
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("未选择目标图片目录！    "));
		return;
	}
	QDir dir(dir_despic);
	if(!dir.exists())
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("目标图片目录打开失败      "));
		return ;
	}
	QFile file;
	QFileInfo fi;
//	for (QMap<QString,QFileInfo>::iterator it1 = map_rom.begin();it1 != map_rom.end();it1++)
//	{
//		qDebug()<< it1.key() <<it1.value();
//		for (QMap<QString,QFileInfo>::iterator it2 = map_srcpic.begin();it2 != map_srcpic.end();it2++)
//		{
//			int ss = QString::compare(it1.key(),it2.key());
//			if(ss == 0)
//			{
//				file.setFileName(it2.value().absoluteFilePath());
//				file.copy(dir_despic +"/"+fi.fileName());
//				break;
//			}
//		}

//	}


	thread.m_map1 = map_rom;
	thread.m_map2 = map_srcpic;
	thread.desdir = dir_despic;
	thread.desfront = ui->LE6_despic1->text();
	thread.desback = ui->LE6_despic2->text();

	thread.start();
//	QMap<QString,QFileInfo>::iterator it1 = map_rom.begin();
//	QMap<QString,QFileInfo>::iterator it2 = map_srcpic.begin();

//	float rate = 100.0/map_rom.count();
//	float current = 0;
//	while (it1 != map_rom.end())
//	{
//		int ss = QString::compare(it1.key(),it2.key());
//		if(ss == 0)
//		{	fi = it2.value();
//			file.setFileName(fi.absoluteFilePath());
//			file.copy(dir_despic +"/"+fi.fileName());
//			it1++;
//			it2++;
//			current += rate;
//		}
//		else if(ss >0)
//		{
//			it2++;
//		}
//		else
//		{
//			it1++;
//			current += rate;
//		}

//		ui->PB_progress->setValue(current);
//		if(it2 == map_srcpic.end())
//		{
//			break;
//		}
//	}

//	 QMessageBox::information(this, tr("对话框"),tr("导出完成      "),tr("确定"));
//	for (int i = 0;i<list_rom.size();i++)
//	{
//		for (int j = 0;j <list_srcpic.size();j++)
//		{
//			if(list_rom.at(i) == list_srcpic.at(j))
//			{
//				fi = flist_srcpic.at(j);
//				if(fi.isFile())
//				{
//					file.setFileName(fi.absoluteFilePath());
//					file.copy(dir_despic +"/"+fi.fileName());
//					list_srcpic.removeAt(j);
//					flist_srcpic.removeAt(j);
//					break;
//				}
//			}
//		}

//	}


}
