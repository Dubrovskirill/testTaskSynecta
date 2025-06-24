#ifndef IPARSER_H
#define IPARSER_H



#include <QString>
#include <vector>
#include "MeasuringPoint.h"

class IParser {
public:
    virtual ~IParser()=default;
    virtual bool parse(const QString& filePath, std::vector<MeasuringPoint>& result)=0;
    virtual QString getLastError() const = 0;
};

#endif // IPARSER_H

