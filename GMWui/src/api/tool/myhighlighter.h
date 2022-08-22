#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class MyHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit MyHighlighter(QTextDocument* parent);
    void Init();
    void Init(const QStringList& patlis);
    void SetEnable(bool isOK);
    void Customize(const QString& hlStr, const QTextCharFormat& hlFormat, int mode = 2);
protected:
    void highlightBlock(const QString& text);
public:
private:
    QTextCharFormat myformat1;
    QTextCharFormat myformat2;
    QStringList m_patlis;
    bool m_enable;
    QString m_hlStr;
    QTextCharFormat m_hlFormat;
};

#endif // MYHIGHLIGHTER_H
