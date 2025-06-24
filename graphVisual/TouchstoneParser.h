#ifndef TOUCHSTONEPARSER_H
#define TOUCHSTONEPARSER_H

#include "IParser.h"
#include <QString>

class TouchstoneParser: public IParser{
public:
    TouchstoneParser() = default;
    ~TouchstoneParser() override = default;
    bool parse(const QString& filePath, std::vector<MeasuringPoint>& result) override;
    QString getLastError() const override;
private:
    QString lastErrorMessage;

    bool validateHeader(const QString& line);
    bool parseDataLine(const QString& line, MeasuringPoint& point);
    bool validateData(const std::vector<MeasuringPoint>& data);
};

#endif // TOUCHSTONEPARSER_H
