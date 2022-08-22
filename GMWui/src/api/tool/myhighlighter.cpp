#include "myhighlighter.h"

MyHighlighter::MyHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter{parent}
{
    m_enable = true;
    Init();
}

void MyHighlighter::Init()
{
    myformat1.setFontWeight(QFont::Bold);
    myformat1.setForeground(Qt::red);

    myformat2.setFontWeight(QFont::Bold);
    myformat2.setForeground(Qt::blue);
    myformat2.setFontPointSize(14);

    m_patlis.clear();
    m_patlis << " 溢出"
             << " 被闭锁"
             << " 被取代"
             << " 非当前值"
             << " 无效"
             << "否定确认"
             << "试验状态"
             << "未知，无法识别当前的传送原因"
             << "未完成此ASDU剩余报文的解析"
             << "出错！"
             << " 上次读数后计数器被调整"
             << " 在相应的累加周期内计数器溢出"
             << " 被测值无效"
             << "存在后续帧，放入全部报文后解析";
}

void MyHighlighter::Init(const QStringList& patlis)
{
    m_patlis = patlis;
    m_patlis.removeAll("");
    if(m_patlis.isEmpty()) {
        Init();
    }
}

void MyHighlighter::SetEnable(bool isOK)
{
    m_enable = isOK;
}

void MyHighlighter::Customize(const QString& hlStr, const QTextCharFormat& hlFormat, int mode)
{
    if(mode == 0) {
        m_hlStr = hlStr;
    }
    else if(mode == 1) {
        m_hlFormat = hlFormat;
    }
    else {
        m_hlStr = hlStr;
        m_hlFormat = hlFormat;
    }
}

void MyHighlighter::highlightBlock(const QString& text)
{
    if(!m_enable) {
        return;
    }
    foreach(const QString& pattern, m_patlis) {
        if(pattern.isEmpty()) {
            continue;
        }
        int length = pattern.length();
        int index = text.indexOf(pattern);
        while(index >= 0) {
            setFormat(index, length, myformat1);
            index = text.indexOf(pattern, index + length);
        }
    }

    QString pattern1 = "####第";
    int length1 = pattern1.length();
    QString pattern2 = "帧####";
    int length2 = pattern2.length();
    int index1 = text.indexOf(pattern1);
    int index2 = text.indexOf(pattern2, index1);
    while(index1 >= 0 && index2 >= 0 && (index2 - index1) < (length1 + 8)) {
        int length = index2 - index1 + length2;
        setFormat(index1, length, myformat2);
        index1 = text.indexOf(pattern1, index1 + length);
        index2 = text.indexOf(pattern2, index1);
    }

    int length = m_hlStr.length();
    if(length > 0) {
        int index = text.indexOf(m_hlStr);
        while(index >= 0) {
            setFormat(index, length, m_hlFormat);
            index = text.indexOf(m_hlStr, index + length);
        }
    }
}

