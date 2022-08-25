#ifndef MYITEMMODEL_H
#define MYITEMMODEL_H

#include <QStandardItemModel>
#include <QXmlStreamReader>

class MyItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    MyItemModel(QObject* parent = nullptr);
    bool InitXml(const QString& xmlPath);

    bool ImportXml(const QString& xmlPath);

    void MakeTypeXml(QXmlStreamWriter& writer);
    void MakeTypeItemXml(QXmlStreamWriter& writer, QStandardItem* parent);

    void MakeGameXml(QXmlStreamWriter& writer);
    void MakeGameItemXml(QXmlStreamWriter& writer, QStandardItem* parent, const QStringList& qualifiedLst);

    void AddOneRow(const QStringList& itemLst, QStandardItem* parent);
private:

    void ParseGameElement(QXmlStreamReader& reader);
    void ParseMachineElement(QXmlStreamReader& reader);

public:
    QString m_lastError;
};

#endif // MYITEMMODEL_H
