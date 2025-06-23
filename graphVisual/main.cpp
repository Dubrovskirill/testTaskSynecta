
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "GraphController.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GraphController>("App", 1, 0, "GraphController");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
