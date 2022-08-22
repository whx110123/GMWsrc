#ifndef TOOLAPI_H
#define TOOLAPI_H

#include <QObject>

class ToolApi : public QObject
{
    Q_OBJECT
public:
    explicit ToolApi(QObject* parent = nullptr);
    static ToolApi* GetInstance();

    //16进制字符串与字节数组互转
    static char HexStrToChar(char data);
    static QByteArray HexStrToByteArray(const QString& data);
};

template <typename T> T ByteArrayToNumber(const QByteArray& data, bool bigEndian = false)
{
    T val;
    int sz = sizeof(T);
    QByteArray buf = data;
    buf.resize(sz);
    if(!bigEndian) {
        memcpy(&val, buf.data(), sz);
    }
    else {
        char* p = (char*)&val;
        for(int i = 0; i < sz; i++) {
            p[sz - i - 1] = buf[i];
        }
    }
    return val;
}

template <typename T> QByteArray NumberToByteArray(const T& val, bool bigEndian = false)
{
    QByteArray data;
    if(!bigEndian) {
        data.append((char*)&val, sizeof(val));
    }
    else {
        T tmp = val;
        int sz = sizeof(T);
        char* p = (char*)&tmp;
        for(int i = sz - 1; i >= 0; i--) {
            data.append(p[i]);
        }
    }
    return data;
}

#endif // TOOLAPI_H
