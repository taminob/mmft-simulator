#include "Membrane.h"

#include "Edge.h"
#include "Node.h"

#include <cmath>

namespace arch {

template<typename T>
Membrane<T>::Membrane(int id, int node0, int node1, T height, T width, T length, T poreRadius, T porosity) : Edge<T>(id, node0, node1), height(height), width(width), length(length), poreRadius(poreRadius), porosity(porosity) {}

template<typename T>
Membrane<T>::Membrane(int id, int node0, int node1, T resistance) : Edge<T>(id, node0, node1), membraneResistance(resistance) {}

template<typename T>
void Membrane<T>::setDimensions(T width, T height, T length) {
    this->height = height;
    this->width = width;
    this->length = length;
}

template<typename T>
void Membrane<T>::setHeight(T height) {
    this->height = height;
}

template<typename T>
void Membrane<T>::setWidth(T width) {
    this->width = width;
}

template<typename T>
void Membrane<T>::setLength(T length) {
    this->length = length;
}

template<typename T>
void Membrane<T>::setPoreRadius(T poreRadius) {
    this->poreRadius = poreRadius;
}

template<typename T>
void Membrane<T>::setPorosity(T porosity) {
    this->porosity = porosity;
}

template<typename T>
void Membrane<T>::setChannel(RectangularChannel<T>* channel) {
    this->channel = channel;
}

template<typename T>
void Membrane<T>::setOrgan(Organ<T>* organ) {
    this->organ = organ;
}

template<typename T>
T Membrane<T>::getHeight() const {
    return height;
}

template<typename T>
T Membrane<T>::getWidth() const {
    return width;
}

template<typename T>
T Membrane<T>::getLength() const {
    return length;
}

template<typename T>
RectangularChannel<T>* Membrane<T>::getChannel() const {
    return channel;
}

template<typename T>
Organ<T>* Membrane<T>::getOrgan() const {
    return organ;
}

template<typename T>
T Membrane<T>::getPoreRadius() const {
    return poreRadius;
}

template<typename T>
T Membrane<T>::getPoreDiameter() const {
    return poreRadius * 2;
}

template<typename T>
T Membrane<T>::getPorosity() const {
    return porosity;
}

template<typename T>
T Membrane<T>::getNumberOfPores(T area) const {
    return (porosity * area) / (M_PI * pow(poreRadius, 2));
}

template<typename T>
T Membrane<T>::getPoreDensity() const {
    return (porosity * M_PI * pow(poreRadius, 2));
}

template<typename T>
T Membrane<T>::getArea() const {
    return width * length;
}

template<typename T>
T Membrane<T>::getVolume() const {
    return width * height * length;
}

template<typename T>
T Membrane<T>::getPressure() const {
    return this->nodeA->getPressure() - this->nodeB->getPressure();
}

template<typename T>
T Membrane<T>::getFlowRate() const {
    return getPressure() / getResistance();
}

template<typename T>
T Membrane<T>::getResistance() const {
    return membraneResistance;
}

template<typename T>
T Membrane<T>::getConcentrationChange(T resistance, T timeStep, T concentrationDifference, T currTime) const {
    constexpr auto f = []([[maybe_unused]] T time, T concentration, T permeability) { return permeability * concentration; };

    auto* membraneChannel = this->getChannel();
    T permeability = 1 / resistance;
    T k1 = timeStep * (f(currTime, concentrationDifference, permeability));
    T k2 = timeStep * (f((currTime + timeStep / 2), (concentrationDifference + k1 / 2), permeability));
    T k3 = timeStep * (f((currTime + timeStep / 2), (concentrationDifference + k2 / 2), permeability));
    T k4 = timeStep * (f((currTime + timeStep), (concentrationDifference + k3), permeability));
    T concentrationChange = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    return concentrationChange;
}

}  // namespace arch
