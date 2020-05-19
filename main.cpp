#include <QApplication>
#include <QFontDatabase>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "Core.h"
#include "apphelper.h"
#include "fileutilities.h"
#include "xoCorePlugin.h"
//#include "xoPrimitiveConsole.h"
#include "GlobalConsole.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);

    QApplication application(argc, argv);
#ifdef Q_OS_WIN
    int processCount = 0;
    QStringList processes = AppHelper::getRunningApps();
    foreach(QString str, processes)
    {
        if (str.compare("XORDE.exe", Qt::CaseInsensitive) == 0)
        {
            processCount++;
            if (processCount >1)
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

    QCommandLineOption configPathOption(QStringList{"p", "config_path"}, QObject::tr("sets path to xoRDE launch config"), "path");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(configPathOption);
    parser.process(application);

    QString configPath;
    if(parser.isSet(configPathOption)) configPath = parser.value(configPathOption);

    Core::Instance()->init(configPath);

    return application.exec();
}
