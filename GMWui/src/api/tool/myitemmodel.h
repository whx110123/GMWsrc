#ifndef MYITEMMODEL_H
#define MYITEMMODEL_H

#include <QStandardItemModel>
#include <QXmlStreamReader>

class MyItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    MyItemModel(QObject* parent = nullptr);

    void SetXmlPath(const QString& xmlPath);
    bool InitXml();
    void MakeXml(QXmlStreamWriter& writer);
    void AddOneRow(const QStringList& itemLst);
    void AddOneRow(const QStringList& itemLst, QStandardItem* parent);
private:
    void ParseGameElement(QXmlStreamReader& reader);
    void ParseMachineElement(QXmlStreamReader& reader);
private:
    QString m_xmlPath;
public:
    QString m_lastError;
};

#endif // MYITEMMODEL_H
