#include "GraphController.h"

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
