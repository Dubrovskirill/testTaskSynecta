#include "GraphController.h"
#include "LogMagProcessor.h"
#include "TouchstoneParser.h"

GraphController::GraphController(QObject* parent)
    : QObject(parent)
{
    parser = std::make_unique<TouchstoneParser>();
    processor = std::make_unique<LogMagProcessor>();
}

void GraphController::loadFile(const QString& filePath) {
    std::vector<MeasuringPoint> measurements;
    if (!parser->parse(filePath, measurements)) {
        emit errorOccurred(parser->getLastError());
        return;
    }
    auto processed = processor->process(measurements);

    QList<QPointF> points;
    for (const auto& p : processed) {
        points.append(QPointF(p.first, p.second));
    }
    emit dataUpdated(points);
}
