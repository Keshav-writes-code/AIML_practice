#include "../includes/dataset.h"
#include <random>
#include <vector>

Datapoint::Datapoint(int attribs) { this->point.resize(attribs); }

Dataset::Dataset(int samples, double (*targetFunc)(double),
                 double noiselevel = 0.0) {}
