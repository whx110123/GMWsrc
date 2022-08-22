#include "setupapp.h"
#include <QApplication>
#include <QFile>
#include <QPalette>
#include <QSettings>
#include "globaldefine.h"

SetupApp* SetupApp::m_instance = 0;


SetupApp::SetupApp(QObject* parent)
    : QObject{parent}
{
    m_configFile = "config.ini";

    /*[Setup]*/
    m_cleanDelete1 = true;
    m_cleanDelete2 = true;
    m_cleanDelete3 = true;
    m_cleanDelete4 = true;
    m_cleanUpper = false;
    m_cleanLower = false;

    InitStyle();
}

SetupApp* SetupApp::GetInstance()
{
    if(!m_instance) {
        m_instance = new SetupApp(qApp);
    }
    return m_instance;
}

void SetupApp::ReadConfig()
{
    QSettings set(m_configFile, QSettings::IniFormat);

    set.beginGroup("Setup");
    m_cleanDelete1 = set.value("CleanDelete1", m_cleanDelete1).toBool();
    m_cleanDelete2 = set.value("CleanDelete2", m_cleanDelete2).toBool();
    m_cleanDelete3 = set.value("CleanDelete3", m_cleanDelete3).toBool();
    m_cleanDelete4 = set.value("CleanDelete4", m_cleanDelete4).toBool();
    m_cleanUpper = set.value("CleanUpper", m_cleanUpper).toBool();
    m_cleanLower = set.value("CleanLower", m_cleanLower).toBool();
    set.endGroup();
}

void SetupApp::WriteConfig()
{
    QSettings set(m_configFile, QSettings::IniFormat);

    set.beginGroup("Setup");
    set.setValue("CleanDelete1", m_cleanDelete1);
    set.setValue("CleanDelete2", m_cleanDelete2);
    set.setValue("CleanDelete3", m_cleanDelete3);
    set.setValue("CleanDelete4", m_cleanDelete4);
    set.setValue("CleanUpper", m_cleanUpper);
    set.setValue("CleanLower", m_cleanLower);
    set.endGroup();

}

void SetupApp::InitStyle()
{
    //加载样式表
    QString qss;
    QFile file(":/qss/flatgray.css");
    if(file.open(QFile::ReadOnly)) {
        qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(paletteColor));
        qApp->setStyleSheet(qss);
        file.close();
    }

    //先从样式表中取出对应的颜色
    QString textColor, panelColor, borderColor, normalColorStart, normalColorEnd, darkColorStart, darkColorEnd, highColor;
    GetQssColor(qss, textColor, panelColor, borderColor, normalColorStart, normalColorEnd, darkColorStart, darkColorEnd, highColor);

    //将对应颜色设置到控件
    this->m_borderColor = highColor;
    this->m_normalBgColor = normalColorStart;
    this->m_darkBgColor = panelColor;
    this->m_normalTextColor = textColor;
    this->m_darkTextColor = m_normalTextColor;
}

void SetupApp::GetQssColor(const QString& qss, const QString& flag, QString& color)
{
    int index = qss.indexOf(flag);
    if(index >= 0) {
        color = qss.mid(index + flag.length(), 7);
    }
}

void SetupApp::GetQssColor(const QString& qss, QString& textColor, QString& panelColor, QString& borderColor, QString& normalColorStart, QString& normalColorEnd, QString& darkColorStart, QString& darkColorEnd, QString& highColor)
{
    GetQssColor(qss, "TextColor:", textColor);
    GetQssColor(qss, "PanelColor:", panelColor);
    GetQssColor(qss, "BorderColor:", borderColor);
    GetQssColor(qss, "NormalColorStart:", normalColorStart);
    GetQssColor(qss, "NormalColorEnd:", normalColorEnd);
    GetQssColor(qss, "DarkColorStart:", darkColorStart);
    GetQssColor(qss, "DarkColorEnd:", darkColorEnd);
    GetQssColor(qss, "HighColor:", highColor);
}
