#ifndef LOGMAGPROCESSOR_H
#define LOGMAGPROCESSOR_H

#include "IProcessor.h"
#include <cmath>

class LogMagProcessor: public IProcessor
{
public:
    std::vector<std::pair<double, double>> process(const std::vector<MeasuringPoint>& measurements) override {
        std::vector<std::pair<double, double>> result;
        for (const auto& m : measurements) {
            double magnitude = std::sqrt(m.real * m.real + m.imag * m.imag);
            double logMag = 20.0 * std::log10(magnitude);
            result.emplace_back(m.frequency, logMag);
        }
        return result;
    }
};

#endif // LOGMAGPROCESSOR_H
