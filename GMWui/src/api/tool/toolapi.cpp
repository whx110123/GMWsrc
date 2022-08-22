#include "toolapi.h"

ToolApi::ToolApi(QObject* parent)
    : QObject{parent}
{

}

char ToolApi::HexStrToChar(char data)
{
    if((data >= '0') && (data <= '9')) {
        return data - '0';
    }
    else if((data >= 'A') && (data <= 'F')) {
        return data - 'A' + 10;
    }
    else if((data >= 'a') && (data <= 'f')) {
        return data - 'a' + 10;
    }
    else {
        return (-1);
    }
}

QByteArray ToolApi::HexStrToByteArray(const QString& data)
{
    QByteArray senddata;
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = data.length();
    senddata.resize(len / 2);

    for(int i = 0; i < len;) {
        hexdata = HexStrToChar(data.at(i++).toLatin1());
        while(hexdata < 0) {
            if(i >= len) {
                break;
            }
            hexdata = HexStrToChar(data.at(i++).toLatin1());
        }
        if(i >= len) {
            break;
        }

        lowhexdata = HexStrToChar(data.at(i++).toLatin1());
        while(lowhexdata < 0) {
            if(i >= len) {
                break;
            }
            lowhexdata = HexStrToChar(data.at(i++).toLatin1());
        }
        if(lowhexdata < 0) {
            break;
        }

        hexdata = hexdata * 16 + lowhexdata;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }

    senddata.resize(hexdatalen);
    return senddata;
}

