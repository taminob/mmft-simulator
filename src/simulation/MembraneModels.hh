#include "MembraneModels.h"

#include <cmath>

namespace sim {

template<typename T>
MembraneModel<T>::MembraneModel() { }

//=========================================================================================
//=============================  permeability Membrane  ===================================
//=========================================================================================

template<typename T>
PermeabilityMembraneModel<T>::PermeabilityMembraneModel() : MembraneModel<T>() { }


//=========================================================================================
//============================  poreResistance Membrane  ==================================
//=========================================================================================

template<typename T>
PoreResistanceMembraneModel<T>::PoreResistanceMembraneModel() : MembraneModel<T>() { }

// Ishahak2020
template<typename T>
MembraneResistanceModel0<T>::MembraneResistanceModel0() = default;

template<typename T>
T MembraneResistanceModel0<T>::getMembraneResistance(arch::Membrane<T> const* const membrane, Fluid<T> const* const fluid, T area) const {
    return getPoreResistance(membrane, fluid) / (area * membrane->getPorosity());
}

template<typename T>
T MembraneResistanceModel0<T>::getPermeabilityParameter(const arch::Membrane<T>* const membrane) const {
    return (M_PI * membrane->getPorosity() * pow(membrane->getPoreRadius(), 4)) / 8;
}

template<typename T>
T MembraneResistanceModel0<T>::getPoreResistance(arch::Membrane<T> const* const membrane, Fluid<T> const* const fluid) const {
    return (8 * fluid->getViscosity() * membrane->getHeight()) / (M_PI * pow(membrane->getPoreRadius(), 4));
}

}   /// namespace sim
