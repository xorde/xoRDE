#include "Core.h"
#include <QApplication>
#include <QFontDatabase>
#include "apphelper.h"
#include "fileutilities.h"
#include "xoCorePlugin.h"
#include "xoPrimitiveConsole.h"
#include "GlobalConsole.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
#ifdef Q_OS_WIN
    int processCount = 0;
    QStringList processes = AppHelper::getRunningApps();
    foreach(QString str, processes)
    {
        if (str.compare("XORDE.exe", Qt::CaseInsensitive) == 0)
        {
            processCount++;
            if (processCount > 1)
            {
                AppHelper::warningMessage(QCoreApplication::translate("Generic", "XORDE уже запущена"));
                return 0;
            }
        }
    }
#endif


    QCoreApplication::setOrganizationName("Neurobotics");
    QCoreApplication::setOrganizationDomain("xorde.org");
    QCoreApplication::setApplicationName("XORDE");

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    Core core;

    core.loadCorePlugins();

    auto corePlugins = core.getCorePlugins();

    bool uiProvided = false;
    foreach(QString key, corePlugins.keys())
    {
        qDebug() << "loading" << key;

        xoCorePlugin *corePlugin = corePlugins[key];
        corePlugin->start();
        if (corePlugin->providesUI())
        {
            uiProvided = true;
        }
    }
    if (!uiProvided)
    {
        auto console = new xoPrimitiveConsole();
        console->show();
    }
    return application.exec();
}
