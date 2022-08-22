#include "mydelegate.h"

#include <QComboBox>
#include <appdata.h>
#include "setupapp.h"

MyDelegate::MyDelegate(QObject* parent) : QStyledItemDelegate(parent)
{

}

QWidget* MyDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.data(Qt::UserRole + 1).toString() == "localIP") {
        QComboBox* cobBox = new QComboBox(parent);
        AppData::loadIP(cobBox);
        cobBox->insertItem(0, "默认");
        return cobBox;
    }
    if(index.column() == 1) {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
    return 0;
}

void MyDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QLineEdit* lE = qobject_cast<QLineEdit* >(editor);
    QComboBox* cobBox = qobject_cast<QComboBox*>(editor);

    QString userRole = index.data(Qt::UserRole + 1).toString();
    if(userRole == "localIP") {
        if(cobBox) {
            g_setup->m_localIP = cobBox->currentText();
        }
    }
    else if(userRole == "IEC104Station_IP") {
        if(lE) {
            g_setup->m_IEC104Station_IP = lE->text();
        }
    }
    else if(userRole == "IEC104Station_Port") {
        if(lE) {
            g_setup->m_IEC104Station_Port = lE->text();
        }
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(size.height() + 10);
    return size;
}
