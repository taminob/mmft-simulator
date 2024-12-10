/**
 * @file MembraneModels.h
 */

#pragma once

#include "Fluid.h"
#include "Membrane.h"

namespace sim { 

/**
 * @brief Virtual class that describes the basic functionality for mixing models.
*/
template<typename T>
class MembraneModel {
protected:

public:

    /**
     * @brief Constructor of a membrane model.
    */
    MembraneModel();

    /**
     * @brief Virtual default destructor for inheritance.
     */
    virtual ~MembraneModel() = default;

    /**
     * @brief Get the resistance caused by the membrane based on the specific resistance model.
     *
     * @param membrane Pointer to the membrane for which the resistance should be calculated.
     * @param fluid Species for which the resistance should be calculated.
     * @return The resistance of this membrane to this fluid.
     */
    virtual T getMembraneResistance(arch::Membrane<T> const* membrane, Fluid<T> const* fluid, T area) const = 0;
};

/**
 * @brief Class that describes the poreResistance membrane model. This membrane model derives the permeability from pore geometry.
*/
template<typename T>
class PermeabilityMembraneModel : public MembraneModel<T> {

private:

public:

    /**
     * @brief Constructor of a poreResistance membrane model.
    */
    PermeabilityMembraneModel();

};

/**
 * @brief Class that describes the poreResistance membrane model. This membrane model derives the permeability from pore geometry.
*/
template<typename T>
class PoreResistanceMembraneModel : public MembraneModel<T> {

private:

public:

    /**
     * @brief Constructor of a poreResistance membrane model.
    */
    PoreResistanceMembraneModel();

};

/**
 * @brief Class that defines the functionality of the 1D membrane resistance model.
 * Membrane Resistance Model 0
 * Based on Source: M. Ishahak, J. Hill, Q. Amin, L. Wubker, A. Hernandez, A. Mitrofanova, A. Sloan, A. Fornoni and A. Agarwal. "Modular Microphysiological System for Modeling of Biologic Barrier Function". In: Front. Bioeng. Biotechnol. 8:581163. (2020). doi: 10.3389/fbioe.2020.581163
 */
template<typename T>
class MembraneResistanceModel0 : public MembraneModel<T> {
  private:
    T getPoreResistance(arch::Membrane<T> const*  membrane, Fluid<T> const*  fluid) const;

  public:
    MembraneResistanceModel0();

    [[nodiscard]] T getMembraneResistance(arch::Membrane<T> const* membrane, Fluid<T> const* fluid, T area) const override;
    [[nodiscard]] T getPermeabilityParameter(const arch::Membrane<T>* membrane) const;
};

}   // namespace sim
