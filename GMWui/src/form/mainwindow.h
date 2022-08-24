#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QTreeWidget>
#include <qxmlstream.h>

namespace Ui {
class MainWindow;
}

class FunGetPicDlg;
class MyItemModel;
class QStandardItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void InitForm();
    void InitConfig();
    void InitModel();
    int MaybeSave();
    void ReadSettings();
    void WriteSettings();
    void ExpandItem(QStandardItem* item);
    void CollapseItem(QStandardItem* item);
protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void SelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

    void on_actGetPng_triggered();

    void on_treeView_type_customContextMenuRequested(const QPoint& pos);

    void on_actSave_triggered();

private:
    Ui::MainWindow* ui;
    FunGetPicDlg* getpic;
    MyItemModel* m_emptyModel;
    MyItemModel* m_typeModel;
};

#endif // MAINWINDOW_H
