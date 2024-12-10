#include "Organ.h"

#include "Edge.h"
#include "Node.h"

#include <cmath>
#include <stdexcept>

namespace arch {

template<typename T>
Organ<T>::Organ(int id, Node<T>* node0, Node<T>* node1, T height, T width, T length) : Edge<T>(id, node0, node1), height(height), width(width), length(length) {}

template<typename T>
Organ<T>::Organ(int id, Node<T>* node0, Node<T>* node1, T resistance) : Edge<T>(id, node0, node1), organResistance(resistance) {}

template<typename T>
void Organ<T>::setDimensions(T width, T height, T length) {
    this->height = height;
    this->width = width;
    this->length = length;
}

template<typename T>
void Organ<T>::setHeight(T height) {
    this->height = height;
}

template<typename T>
void Organ<T>::setWidth(T width) {
    this->width = width;
}

template<typename T>
void Organ<T>::setLength(T length) {
    this->length = length;
}

template<typename T>
T Organ<T>::getHeight() const {
    return height;
}

template<typename T>
T Organ<T>::getWidth() const {
    return width;
}

template<typename T>
T Organ<T>::getLength() const {
    return length;
}

template<typename T>
T Organ<T>::getArea() const {
    return width * length;
}

template<typename T>
T Organ<T>::getVolume() const {
    return width * height * length;
}

template<typename T>
T Organ<T>::getPressure() const {
    return node0->getPressure() - node1->getPressure();
}

template<typename T>
T Organ<T>::getFlowRate() const {
    // there is no flow in an organ, thus the organ does not have a flow-rate
    // to ensure time-accurate concentration changes
    // mixtures move through the organ based on the flow-rate of the connected channel
    return 0;
}

T Organ<T>::getResistance() const {
    return organResistance;
}

}  // namespace arch
