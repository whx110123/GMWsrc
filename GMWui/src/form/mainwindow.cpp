#include "fungetpicdlg.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QInputDialog>
#include <QSettings>
#include <myitemmodel.h>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitForm();
    InitModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitForm()
{
    getpic = new FunGetPicDlg(this);
    ReadSettings();
}

void MainWindow::InitConfig()
{

}

void MainWindow::InitModel()
{
    m_currentModel = nullptr;
    m_emptyModel = new MyItemModel(this);
    QHeaderView* header = ui->treeView_list->header();
    header->setStretchLastSection(true);

    m_typeModel = new MyItemModel(this);
    m_typeModel->clear();
    ui->treeView_type->setModel(m_typeModel);
    ui->treeView_type->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeView_type->setHeaderHidden(true);

    connect(ui->treeView_type->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::SelectionChanged);
}

int MainWindow::MaybeSave()
{
    return QMessageBox::question(this, "问题对话框", "是否保存窗口状态", "保存", "不保存", "取消");
}

void MainWindow::ReadSettings()
{
    QString name = qApp->applicationName() + ".ini";
    QSettings settings(name, QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    settings.endGroup();
}

void MainWindow::WriteSettings()
{
    QString name = qApp->applicationName() + ".ini";
    QSettings settings(name, QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.endGroup();
}

void MainWindow::ExpandItem(QStandardItem* item)
{
    if(!item) {
        return;
    }
    if(item->hasChildren()) {
        ui->treeView_type->expand(item->index());
        for(int i = 0; i < item->rowCount() ; i++) {
            QStandardItem* childitem = item->child(i);
            ExpandItem(childitem);
        }
    }
}

void MainWindow::CollapseItem(QStandardItem* item)
{
    if(!item) {
        return;
    }
    if(item->hasChildren()) {
        for(int i = 0; i < item->rowCount() ; i++) {
            QStandardItem* childitem = item->child(i);
            CollapseItem(childitem);
        }
        ui->treeView_type->collapse(item->index());
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    WriteSettings();		//保存界面状态
    event->accept();
}

void MainWindow::SelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    QStandardItem* item = m_typeModel->itemFromIndex(selected.indexes().at(0));
    m_currentModel = item->data().value<MyItemModel*>();
    if(m_currentModel) {
        ui->treeView_list->setModel(m_currentModel);
    }
    else {
        ui->treeView_list->setModel(m_emptyModel);
    }
}

void MainWindow::on_actGetPng_triggered()
{
    getpic->show();
}

void MainWindow::on_treeView_type_customContextMenuRequested(const QPoint& pos)
{
    Q_UNUSED(pos)
    MyItemModel* model = qobject_cast<MyItemModel*>(ui->treeView_type->model());
    if(!model) {
        return;
    }

    QMenu menu;
    QAction* add_item = nullptr;
    QAction* add_subitem = nullptr;
    QAction* delete_item = nullptr;
    QAction* rename_item = nullptr;
    QAction* import_file = nullptr;
    QAction* expand_subtrees = nullptr;
    QAction* collapse_subtrees = nullptr;
    QModelIndex index = ui->treeView_type->currentIndex();
    QStandardItem* item = model->itemFromIndex(index);
    add_item = menu.addAction("添加");
    if(item) {
        add_subitem = menu.addAction("添加子条目");
        delete_item = menu.addAction("删除");
        rename_item = menu.addAction("重命名");
        import_file = menu.addAction("导入Dat..");
        if(item->hasChildren()) {
            expand_subtrees = menu.addAction("展开所有子树");
            collapse_subtrees = menu.addAction("折叠所有子树");
        }
    }
    QAction* expand_all = menu.addAction("全部展开");
    QAction* collapse_all = menu.addAction("全部折叠");

    QAction* ret = menu.exec(QCursor::pos());
    if(!ret) {
        return;
    }

    if(ret == add_item) {
        QString str = QInputDialog::getText(this, "输入游戏类型", "");
        if(str.isEmpty()) {
            return;
        }
        model->AddOneRow(QStringList() << str);
    }
    else if(ret == add_subitem) {
        QString str = QInputDialog::getText(this, "输入游戏类型", "");
        if(str.isEmpty()) {
            return;
        }
        model->AddOneRow(QStringList() << str, item);
    }
    else if(ret == delete_item) {
        if(item->parent()) {
            item->parent()->removeRow(index.row());
        }
        else {
            model->removeRow(index.row());
        }
    }
    else if(ret == rename_item) {
        QString str = QInputDialog::getText(this, "输入游戏类型", "");
        if(str.isEmpty()) {
            return;
        }
        item->setData(str, Qt::EditRole);
    }
    else if(ret == import_file) {
        QString xmlPath = QFileDialog::getOpenFileName(this, "导入Dat", "..");
        if(xmlPath.isEmpty()) {
            return;
        }
        m_currentModel = item->data().value<MyItemModel*>();
        if(m_currentModel) {
            delete m_currentModel;
            m_currentModel = nullptr;
        }
        item->setData(0);

        m_currentModel = new MyItemModel(this);
        ui->treeView_list->setModel(m_currentModel);
        m_currentModel->SetXmlPath(xmlPath);
        if(m_currentModel->InitXml()) {
            QVariant v;
            v.setValue(m_currentModel);
            item->setData(v);
        }
        else {
            delete m_currentModel;
            m_currentModel = nullptr;
        }
    }
    else if(ret == expand_subtrees) {
        ExpandItem(item);
    }
    else if(ret == collapse_subtrees) {
        CollapseItem(item);
    }
    else if(ret == expand_all) {
        ui->treeView_type->expandAll();
    }
    else if(ret == collapse_all) {
        ui->treeView_type->collapseAll();
    }
}

void MainWindow::on_actSave_triggered()
{
    if(!m_typeModel) {
        return;
    }
    QFile file("demo.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    for(int i = 0; i < m_typeModel->rowCount(); i++) {
        QStandardItem* item = m_typeModel->item(i, 0);
        m_currentModel = item->data().value<MyItemModel*>();
        if(m_currentModel) {
            m_currentModel->MakeXml(stream);
        }
    }
    stream.writeEndDocument();
    file.close();
}
