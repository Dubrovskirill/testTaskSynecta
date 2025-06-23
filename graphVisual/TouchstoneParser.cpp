#include "TouchstoneParser.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <algorithm>
#include <cmath>

bool TouchstoneParser::parse(const QString& filePath, std::vector<MeasuringPoint>& result) {

    result.clear();
    lastErrorMessage.clear();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        lastErrorMessage = "Cannot open file: " + filePath;
        return false;
    }

    QTextStream in(&file);
    QString line;
    bool headerFound = false;
    int lineNumber = 0;

    while(!in.atEnd()){
        line=in.readLine().trimmed();
        lineNumber++;

        if(line.isEmpty()||line.startsWith("!")) {
            continue;
        }

        if(!headerFound) {
            if(validateHeader(line)) {
                headerFound=true;
            } else {
               lastErrorMessage="Invalid header format at line " + QString::number(lineNumber);
                return false;
            }
            continue;
        }

        MeasuringPoint point;
        if (parseDataLine(line, point)) {
            result.push_back(point);
        } else {
            lastErrorMessage = "Invalid data format at line " + QString::number(lineNumber);
            return false;
        }
    }

    if(result.empty()) {
        lastErrorMessage="No valid data found";
        return false;
    }
    if (!validateData(result)) {
        return false;
    }

    return true;

}

bool TouchstoneParser::validateHeader(const QString& line) {

    return line.startsWith("# Hz S RI R 50");
}

bool TouchstoneParser::parseDataLine(const QString& line, MeasuringPoint& point) {
    QStringList parts = line.split(QRegExp("\\s+"), Qt::SkipEmptyParts);

    if (parts.size() < 3) {
        return false;
    }

    bool ok1, ok2, ok3;
    point.frequency = parts[0].toDouble(&ok1);
    point.real = parts[1].toDouble(&ok2);
    point.imag = parts[2].toDouble(&ok3);

    return ok1 && ok2 && ok3;
}

bool TouchstoneParser::validateData(const std::vector<MeasuringPoint>& data) {
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].frequency <= data[i-1].frequency) {
            lastErrorMessage = "Data not sorted by frequency";
            return false;
        }
    }
    return true;
}

QString TouchstoneParser::getLastError() const {
    return lastErrorMessage;
}
