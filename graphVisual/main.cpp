#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "TouchstoneParser.h"
#include <QDebug>
#include <vector>
#include <QString>

// Test function
void testTouchstoneParser(const QString& filePath) {
    TouchstoneParser parser;
    std::vector<MeasuringPoint> data;

    if (parser.parse(filePath, data)) {
        qDebug() << "File parsed successfully!";
        qDebug() << "Number of points:" << data.size();
        // Print first 5 points for verification
        for (size_t i = 0; i < data.size() && i < 5; ++i) {
            qDebug() << "Point" << i+1 << ":"
                     << "freq =" << data[i].frequency
                     << "real =" << data[i].real
                     << "imag =" << data[i].imag;
        }
    } else {
        qDebug() << "Parsing error:" << parser.getLastError();
    }
}

int main(int argc, char *argv[])
{

    QCoreApplication app(argc, argv);

    // Укажите путь к вашему файлу
    testTouchstoneParser("C:/Users/Кирилл/Downloads/S21.s1p");

    return 0;




//#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif
//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//        &app, [url](QObject *obj, const QUrl &objUrl) {
//            if (!obj && url == objUrl)
//                QCoreApplication::exit(-1);
//        }, Qt::QueuedConnection);
//    engine.load(url);

//    return app.exec();
}
