#ifndef SETUPAPP_H
#define SETUPAPP_H

#include <QObject>

class SetupApp : public QObject
{
    Q_OBJECT
public:
    explicit SetupApp(QObject* parent = nullptr);
    static SetupApp* GetInstance();

    //读写配置参数
    void ReadConfig();           //读取配置参数
    void WriteConfig();          //写入配置参数
private:
    void InitStyle();
    void GetQssColor(const QString& qss, const QString& flag, QString& color);
    void GetQssColor(const QString& qss, QString& textColor,
                     QString& panelColor, QString& borderColor,
                     QString& normalColorStart, QString& normalColorEnd,
                     QString& darkColorStart, QString& darkColorEnd,
                     QString& highColor);
public:
    QString m_configFile;          //配置文件路径
    //根据QSS样式获取对应颜色值
    QString m_borderColor;
    QString m_normalBgColor;
    QString m_darkBgColor;
    QString m_normalTextColor;
    QString m_darkTextColor;

    QStringList m_protocolLst;     //规约表
    QStringList m_transferLst;     //通信方式表
    QStringList m_crcLst;          //校验方式
    QStringList m_transferMode;    //数字与16进制转换方式


    //设置选项
    bool m_cleanDelete1;           //删除空白行
    bool m_cleanDelete2;           //删除每行首尾空白
    bool m_cleanDelete3;           //删除非报文开头的行
    bool m_cleanDelete4;           //删除报文中的0x前缀
    bool m_cleanUpper;				//字母大写
    bool m_cleanLower;				//字母小写


    QString m_localIP;
    QString m_IEC104Station_IP;
    QString m_IEC104Station_Port;

private:
    static SetupApp* m_instance;
};

#define g_setup SetupApp::GetInstance()
#endif // SETUPAPP_H
