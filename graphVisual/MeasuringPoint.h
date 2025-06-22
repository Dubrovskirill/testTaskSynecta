#ifndef MEASURINGPOINT_H
#define MEASURINGPOINT_H

struct MeasuringPoint {
    double frequency;
    double real;
    double imag;
    MeasuringPoint(): frequency(0.0), real(0.0), imag(0.0) {}
    MeasuringPoint(double freq, double r, double i)
    :frequency(freq), real(r), imag(i) {}
};



#endif // MEASURINGPOINT_H
