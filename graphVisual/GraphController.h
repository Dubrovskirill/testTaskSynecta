#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include <QObject>
#include <QPointF>
#include <vector>
#include <memory>
#include "IParser.h"
#include "IProcessor.h"
#include "MeasuringPoint.h"

class GraphController : public QObject
{
    Q_OBJECT
public:
   explicit GraphController(QObject* parent = nullptr);
    Q_INVOKABLE void loadFile(const QString& filePath);

signals:
   void dataUpdated(const QList<QPointF>& points);
   void errorOccurred(const QString& message);

private:
   std::unique_ptr<IParser> parser;
   std::unique_ptr<IProcessor> processor;
};

#endif // GRAPHCONTROLLER_H
