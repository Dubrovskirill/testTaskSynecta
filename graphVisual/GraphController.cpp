#include "GraphController.h"
#include "LogMagProcessor.h"
#include "TouchstoneParser.h"
#include <QUrl>
#include <QDebug>

GraphController::GraphController(QObject* parent)
    : QObject(parent)
{
    parser = std::make_unique<TouchstoneParser>();
    processor = std::make_unique<LogMagProcessor>();
}



void GraphController::loadFile(const QString& filePath) {
    QString localPath = QUrl(filePath).toLocalFile();
    if (localPath.isEmpty()) {
        localPath = filePath;
    }
    qDebug() << "Opening file:" << localPath;
    std::vector<MeasuringPoint> measurements;
    if (!parser->parse(localPath, measurements)) {
        emit errorOccurred(parser->getLastError());
        return;
    }

    for (int i = 0; i < std::min(5, (int)measurements.size()); ++i) {
        qDebug() << "Point" << i
                 << measurements[i].frequency
                 << measurements[i].real
                 << measurements[i].imag;
    }

    auto processed = processor->process(measurements);

    QList<QPointF> points;
    for (const auto& p : processed) {
        points.append(QPointF(p.first, p.second));
    }
    emit dataUpdated(points);
}
