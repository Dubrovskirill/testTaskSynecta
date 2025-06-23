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

        if(line.isEmpty()||line.startsWith("!")){
            continue;
        }

        if(!headerFound){
            if(validateHeader(line)){
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

    if(result.empty()){
        lastErrorMessage="No valid data found";
        return false;
    }
    if (!validateData(result)) {
        return false;
    }

    return true;



}
