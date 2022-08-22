#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#ifdef websocket
#include <QtWebSockets>
#endif
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
#include <QtCore5Compat>
#endif

#define TIMEMS qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))
#define STRDATETIME qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))

