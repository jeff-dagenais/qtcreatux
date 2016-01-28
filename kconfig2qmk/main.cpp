#include <QtCore/QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFileInfo srcFileInfo("./include/generated/autoconf.h");
    QFile qmkFile("./autoconf.qmk");

    qDebug() << "generating" << qmkFile.fileName();
    qDebug() << "from" << srcFileInfo.canonicalFilePath();

    QFile autoconf(srcFileInfo.canonicalFilePath());

    if (!autoconf.open(QIODevice::ReadOnly)) {
       qDebug() << "could not open" << autoconf.fileName();
       return 1;
    }

    QString qmk("DEFINES += \\\n");
    //qDebug() << QString(autoconf.readAll());
    //qDebug() << QString(autoconf.readAll());


    foreach (QString line, QString(autoconf.readAll()).split('\n')) {
       if(!line.startsWith("#define"))
          continue;
       QStringList lineItems = line.split(' ');
       lineItems.takeFirst(); // remove "#define"
       qmk += lineItems.takeFirst();
       if(lineItems.count())
       {
          qmk += "=";
          while(lineItems.count())
             qmk += lineItems.takeFirst();
       }
       qmk += " \\\n";
    }
    qmk += "\n";

    if (!qmkFile.open(QIODevice::WriteOnly)) {
       qDebug() << "could not create" << qmkFile.fileName() << qmkFile.errorString();
       return 3;
    }

    qmkFile.write(qmk.toAscii());

    return 0;
}
