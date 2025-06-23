#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include <vector>
#include "MeasuringPoint.h"

class IProcessor {
public:
    virtual ~IProcessor() = default;
    virtual std::vector<std::pair<double, double>> process(const std::vector<MeasuringPoint>& measurements) = 0;
};

#endif // IPROCESSOR_H
