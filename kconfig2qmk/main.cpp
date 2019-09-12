#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFileInfo hSrcFileInfo("./include/generated/autoconf.h");
    QFileInfo mkSrcFileInfo("./include/autoconf.mk");
    QFile qmkFile("./autoconf.qmk");

    qDebug() << "generating" << qmkFile.fileName();
    qDebug() << "from" << hSrcFileInfo.canonicalFilePath();

    QFile autoconf_h(hSrcFileInfo.canonicalFilePath());

    if (!autoconf_h.open(QIODevice::ReadOnly)) {
       qDebug() << "could not open" << autoconf_h.fileName();
       return 1;
    }

    QString qmk("DEFINES += \\\n");

    foreach (QString line, QString(autoconf_h.readAll()).split('\n')) {
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

    QFile autoconf_mk(mkSrcFileInfo.canonicalFilePath());

    if (autoconf_mk.open(QIODevice::ReadOnly)) {
	    foreach (QString line, QString(autoconf_mk.readAll()).split('\n')) {
		    if (line.contains(QRegExp("\\\".*\\\".*\\\"")))
			    continue;
		    line.replace("##", "");

		    qmk += line + " \\\n";
	    }
    }

    qmk += "\n";

    if (!qmkFile.open(QIODevice::WriteOnly)) {
       qDebug() << "could not create" << qmkFile.fileName() << qmkFile.errorString();
       return 3;
    }

    qmkFile.write(qPrintable(qmk));

    return 0;
}
