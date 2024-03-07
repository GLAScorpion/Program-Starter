#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "config.h"
#include <iostream>
int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    Config conf("Config.xml");
    conf.SetButton(7,"C:/deploy");
    conf.xml_write();
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/CProgStarter/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    QList<QObject*> obj = engine.rootObjects();
    obj[0]->dumpObjectInfo();
    return app.exec();
}
