#include "myitemmodel.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QtDebug>

MyItemModel::MyItemModel(QObject* parent): QStandardItemModel(parent)
{
    setHorizontalHeaderLabels(QStringList() << "序号" << "名称" << "描述" << "中文描述");
}

bool MyItemModel::InitXml(const QString& xmlPath)
{
    QFile file(xmlPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // 以只读模式打开文件
        return false;
    }
    this->clear();
    QXmlStreamReader reader(&file);

    QStandardItem* parent = this->invisibleRootItem();
    // 解析 XML，直到结束
    while(!reader.atEnd()) {
        // 读取下一个元素
        QXmlStreamReader::TokenType nType = reader.readNext();
        switch(nType) {
        case QXmlStreamReader::NoToken:
            break;
        case QXmlStreamReader::Invalid:
            break;
        case QXmlStreamReader::StartDocument:   // 开始文档
            break;
        case QXmlStreamReader::EndDocument:   // 结束文档
            break;
        case QXmlStreamReader::StartElement: {  // 开始元素
            parent = InitTypeXml(reader, parent);
            break;
        }
        case QXmlStreamReader::EndElement:
            if(parent->parent()) {
                parent = parent->parent();
            }
            break;
        case QXmlStreamReader::Characters:
            break;
        case QXmlStreamReader::Comment:   // 注释
            break;
        case QXmlStreamReader::DTD:    // DTD
            break;
        case QXmlStreamReader::EntityReference:
            break;
        case QXmlStreamReader::ProcessingInstruction:   // 处理指令
            break;
        default:
            break;
        }
    }

    if(reader.hasError()) {   // 解析出错
        qDebug() << QString("错误信息：%1  行号：%2  列号：%3  字符位移：%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
    }

    file.close();  // 关闭文件
    return true;
}

QStandardItem* MyItemModel::InitTypeXml(QXmlStreamReader& reader, QStandardItem* parent)
{
    QString strElementName = reader.name().toString();
    if(QString::compare(strElementName, "游戏") == 0) {
        QXmlStreamAttributes attributes = reader.attributes();
        if(attributes.hasAttribute("类型")) {
            QString strName = attributes.value("类型").toString();
            QStandardItem* item = new QStandardItem;
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));

            MyItemModel* tmpModel = new MyItemModel(this);
            QVariant v;
            v.setValue(tmpModel);
            item->setData(v);

            parent->appendRow(item);
            parent = item;
        }
    }
    if(QString::compare(strElementName, "条目") == 0) {
        MyItemModel* model = parent->data().value<MyItemModel*>();
        if(model) {

        }
    }
    return parent;
}

bool MyItemModel::ImportXml(const QString& xmlPath)
{
    QFile file(xmlPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // 以只读模式打开文件
        return false;
    }
    this->clear();
    this->setHorizontalHeaderLabels(QStringList() << "序号" << "名称" << "描述" << "中文描述");
    QXmlStreamReader reader(&file);

    // 解析 XML，直到结束
    while(!reader.atEnd()) {

        // 读取下一个元素
        QXmlStreamReader::TokenType nType = reader.readNext();

        switch(nType) {
        case QXmlStreamReader::NoToken:
            break;
        case QXmlStreamReader::Invalid:
            break;
        case QXmlStreamReader::StartDocument: {  // 开始文档
            qDebug() << QString("********** 开始文档（XML 声明） ********** ");
            // XML 声明
            QString strVersion = reader.documentVersion().toString();
            QString strEncoding = reader.documentEncoding().toString();
            bool bAlone = reader.isStandaloneDocument();
            qDebug() << QString("版本：%1  编码：%2  Standalone：%3")
                     .arg(strVersion).arg(strEncoding).arg(bAlone) << "\r\n";
            break;
        }
        case QXmlStreamReader::EndDocument: {  // 结束文档
            qDebug() << QString("********** 结束文档 ********** ");
            break;
        }
        case QXmlStreamReader::StartElement: {  // 开始元素
            QString strElementName = reader.name().toString();
            if(QString::compare(strElementName, "game") == 0) {
                ParseGameElement(reader);
            }
            else if(QString::compare(strElementName, "machine") == 0) {
                ParseMachineElement(reader);
            }
            break;
        }
        case QXmlStreamReader::EndElement:
            break;
        case QXmlStreamReader::Characters:
            break;
        case QXmlStreamReader::Comment: {  // 注释
//            qDebug() << QString("********** 注释 ********** ");
//            QString strComment = reader.text().toString();
//            qDebug() << strComment << "\r\n";
            break;
        }
        case QXmlStreamReader::DTD: {   // DTD
//            qDebug() << QString("********** DTD ********** ");
//            QString strDTD = reader.text().toString();
//            QXmlStreamNotationDeclarations notationDeclarations = reader.notationDeclarations();  // 符号声明
//            QXmlStreamEntityDeclarations entityDeclarations = reader.entityDeclarations();  // 实体声明
//            QString strDTDName = reader.dtdName().toString();
//            QString strDTDPublicId = reader.dtdPublicId().toString();  // DTD 公开标识符
//            QString strDTDSystemId = reader.dtdSystemId().toString();  // DTD 系统标识符
//            qDebug() << QString("DTD : %1").arg(strDTD);
//            qDebug() << QString("DTD 名称 : %1").arg(strDTDName);
//            qDebug() << QString("DTD 公开标识符 : %1").arg(strDTDPublicId);
//            qDebug() << QString("DTD 系统标识符 : %1").arg(strDTDSystemId);
//            qDebug() << "\r\n";
            break;
        }
        case QXmlStreamReader::EntityReference:
            break;
        case QXmlStreamReader::ProcessingInstruction: {  // 处理指令
//            qDebug() << QString("********** 处理指令 ********** ");
//            QString strProcInstr = reader.processingInstructionData().toString();
//            qDebug() << strProcInstr << "\r\n";
            break;
        }
        default:
            break;
        }
    }

    if(reader.hasError()) {   // 解析出错
        qDebug() << QString("错误信息：%1  行号：%2  列号：%3  字符位移：%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
    }

    file.close();  // 关闭文件
    return true;
}

void MyItemModel::MakeTypeXml(QXmlStreamWriter& writer)
{
    MakeTypeItemXml(writer, this->invisibleRootItem());
}

void MyItemModel::MakeTypeItemXml(QXmlStreamWriter& writer, QStandardItem* parent)
{
    MyItemModel* model;
    for(int i = 0; i < parent->rowCount(); i++) {
        QStandardItem* item = parent->child(i);
        writer.writeStartElement("游戏");
        writer.writeAttribute("类型", item->data(Qt::EditRole).toString());
        model = item->data().value<MyItemModel*>();
        if(model) {
            model->MakeGameXml(writer);
        }

        if(item->hasChildren()) {
            MakeTypeItemXml(writer, item);
        }

        writer.writeEndElement();
    }
}

void MyItemModel::MakeGameXml(QXmlStreamWriter& writer)
{
    QStringList qualifiedLst;
    for(int j = 0; j < this->columnCount(); j++) {
        qualifiedLst << this->horizontalHeaderItem(j)->data(Qt::EditRole).toString();
    }
    MakeGameItemXml(writer, this->invisibleRootItem(), qualifiedLst);

}

void MyItemModel::MakeGameItemXml(QXmlStreamWriter& writer, QStandardItem* parent, const QStringList& qualifiedLst)
{
    for(int i = 0; i < parent->rowCount(); i++) {
        writer.writeStartElement("条目");
        for(int j = 0; j < parent->columnCount(); j++) {
            writer.writeTextElement(qualifiedLst.at(j),
                                    parent->child(i, j)->data(Qt::EditRole).toString());
        }
        QStandardItem* item = parent->child(i, 0);
        if(item->hasChildren()) {
            MakeGameItemXml(writer, item, qualifiedLst);
        }
        writer.writeEndElement();
    }
}

void MyItemModel::AddOneRow(const QStringList& itemLst)
{
    QList<QStandardItem*> items;
    QStandardItem* item = nullptr;
    for(int i = 0; i < itemLst.size(); i++) {
        item = new QStandardItem;
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        item->setData(itemLst.at(i), Qt::EditRole);
        items.append(item);
    }
    this->appendRow(items);
}

void MyItemModel::AddOneRow(const QStringList& itemLst, QStandardItem* parent)
{
    QList<QStandardItem*> items;
    QStandardItem* item = nullptr;
    for(int i = 0; i < itemLst.size(); i++) {
        item = new QStandardItem;
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        item->setData(itemLst.at(i), Qt::EditRole);
        items.append(item);
    }
    parent->appendRow(items);
}

void MyItemModel::ParseGameElement(QXmlStreamReader& reader)
{
    QList<QStandardItem*> items;
    QStandardItem* item = nullptr;
    for(int i = 0; i < this->columnCount(); i++) {
        item = new QStandardItem;
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        items.append(item);
    }
    item = items.at(0);
    item->setData(QVariant(this->rowCount() + 1), Qt::EditRole);

    QXmlStreamAttributes attributes = reader.attributes();
    if(attributes.hasAttribute("name")) {
        QString strName = attributes.value("name").toString();

        item = items.at(1);
        item->setData(strName, Qt::EditRole);
    }

    while(!reader.atEnd()) {
        reader.readNext();
        if(reader.isStartElement()) {   // 开始元素
            QString strElementName = reader.name().toString();
            if(QString::compare(strElementName, "description") == 0) {
                item = items.at(2);
                item->setData(reader.readElementText(), Qt::EditRole);
            }
        }
        else if(reader.isEntityReference()) {     // 实体引用

        }
        else if(reader.isCDATA()) {     // CDATA

        }
        else if(reader.isEndElement()) {     // 结束元素
            QString strElementName = reader.name().toString();
            if(QString::compare(strElementName, "game") == 0) {
                break;  // 跳出循环
            }
        }
    }
    this->appendRow(items);
}

void MyItemModel::ParseMachineElement(QXmlStreamReader& reader)
{
    QList<QStandardItem*> items;
    QStandardItem* item = nullptr;
    for(int i = 0; i < 3; i++) {
        item = new QStandardItem;
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        items.append(item);
    }
    item = items.at(0);
    item->setData(QVariant(this->rowCount() + 1), Qt::EditRole);

    QXmlStreamAttributes attributes = reader.attributes();
    if(attributes.hasAttribute("name")) {
        QString strName = attributes.value("name").toString();

        item = items.at(1);
        item->setData(strName, Qt::EditRole);
    }

    while(!reader.atEnd()) {
        reader.readNext();
        if(reader.isStartElement()) {   // 开始元素
            QString strElementName = reader.name().toString();
            if(QString::compare(strElementName, "description") == 0) {
                item = items.at(2);
                item->setData(reader.readElementText(), Qt::EditRole);
            }
        }
        else if(reader.isEntityReference()) {     // 实体引用

        }
        else if(reader.isCDATA()) {     // CDATA

        }
        else if(reader.isEndElement()) {     // 结束元素
            QString strElementName = reader.name().toString();
            if(QString::compare(strElementName, "machine") == 0) {
                break;  // 跳出循环
            }
        }
    }
    this->appendRow(items);
}
