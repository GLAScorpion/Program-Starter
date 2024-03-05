#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "config.h"

int main(int argc, char *argv[])
{
    Config conf = Config("Config.xml");
    conf.SetButton(3,"C:/start");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/CProgStarter/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
