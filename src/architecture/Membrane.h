/**
 * @file Membrane.h
 */

#pragma once

#include "Channel.h"
#include "Edge.h"
#include "Node.h"
#include "Organ.h"

namespace arch {

/**
 * @brief Class to specify a membrane, which is a component of a chip in which droplet can flow.
 */
template<typename T>
class Membrane : public Edge<T> {
  private:
    T height = 0;              ///< Height of a membrane in m.
    T width = 0;               ///< Width of a membrane in m.
    T length = 0;              ///< Length of a membrane in m.
    T poreRadius = 0;          ///< Radius of the pores.
    T porosity = 0;            ///< Porosity of the membrane in % (between 0.0 and 1.0)
    T numberOfPores = 0;       ///< Numbers of pores of the membrane.
    T membraneResistance = 0;  ///< Resistance of the membrane in Pas/m^3.
    RectangularChannel<T>* channel;               ///< Membrane on which the barrier is attached (length must be equal).
    Organ<T>* organ;                   ///< Pointer to the organ this membrane is attached to (length must be equal).

  public:
    /**
     * @brief Constructor of a membrane.
     * @param[in] id Id of the membrane.
     * @param[in] node0 Node at one end of the membrane.
     * @param[in] node1 Node at other end of the membrane.
     * @param[in] height Height of the membrane in m.
     * @param[in] width Width of the membrane in m.
     * @param[in] length Length of the membrane in m.
     * @param[in] poreRadius Radius of the pores in the membrane in m.
     * @param[in] porosity Porosity of the membrane.
     * @param[in] type Type of the membrane.
     */
    Membrane(int id, int node0, int node1, T height, T width, T length, T poreRadius, T porosity);

    /**
     * @brief Constructor of a membrane.
     * @param[in] id Id of the membrane.
     * @param[in] node0 Node at one end of the membrane.
     * @param[in] node1 Node at other end of the membrane.
     * @param[in] resistance Resistance of the membrane in Pas/m^3.
     * @param[in] type Type of the membrane.
     */
    Membrane(int id, int node0, int node1, T resistance);

    /**
     * @brief Set dimensions of a membrane.
     * @param[in] width Width of a membrane in m.
     * @param[in] height Height of a membrane in m.
     * @param[in] length Length of a membrane in m.
     */
    void setDimensions(T width, T height, T length);

    /**
     * @brief Set height of a membrane.
     * @param height New height of membrane in m.
     */
    void setHeight(T height);

    /**
     * @brief Set width of membrane.
     * @param[in] width New width of a membrane in m.
     */
    void setWidth(T width);

    /**
     * @brief Set length of membrane.
     * @param[in] length New length of this membrane in m.
     */
    void setLength(T length);

    /**
     * @brief Set radius of the pores of the membrane.
     * 
     * @param poreRadius Radius of the pores in m.
     */
    void setPoreRadius(T poreRadius);

    /**
     * @brief Set porosity of the membrane.
     * 
     * @param porosity Porosity in % (between 0.0 and 1.0)
     */
    void setPorosity(T porosity);

    /**
     * @brief Set channel the membrane is connected to.
     * 
     * @param channel Pointer to the channel the membrane is attached to.
     */
    void setChannel(RectangularChannel<T>* channel);

    /**
     * @brief Set organ the membrane is connected to.
     * 
     * @param organ Pointer to the organ the membrane is attached to.
     */
    void setOrgan(Organ<T>* organ);

    /**
     * @brief Get the concentration change caused by the membrane for a specific species in a mixture given the concentration difference between the channel and the organ tank to which the membrane is connected to.
     * 
     * @param resistance Resistance of the membrane for the mixture area for a specific species.
     * @param timeStep Time step for which the simulation is forwarded.
     * @param concentrationDifference Concentration difference between the channel and the organ tank.
     * @param currTime Current simulation time.
     * @return Absolute concentration change in mol.
     */
    [[nodiscard]] T getConcentrationChange(T resistance, T timeStep, T concentrationDifference, T currTime) const;

    /**
     * @brief Returns the height of this membrane.
     * @returns Height of channel in m.
     */
    [[nodiscard]] T getHeight() const;

    /**
     * @brief Returns the width of this membrane.
     * @returns Width of channel in m.
     */
    [[nodiscard]] T getWidth() const;

    /**
     * @brief Returns the length of this membrane.
     * @returns Length of channel in m.
     */
    [[nodiscard]] T getLength() const;

    /**
     * @brief Get pointer to the channel the membrane is connected to.
     * 
     * @return Pointer to the channel the membrane is connected to.
     */
    [[nodiscard]] RectangularChannel<T>* getChannel() const;

    /**
    * @brief Get pointer to the organ the membrane is connected to.
    * 
    * @return Pointer to the organ the membrane is connected to.
    */
    [[nodiscard]] Organ<T>* getOrgan() const;

    /**
     * @brief Get radius of the pores of the membrane.
     * 
     * @return Radius of a pore of the membrane in m. 
     */
    [[nodiscard]] T getPoreRadius() const;

    /**
     * @brief Get diameter of the pores of the membrane.
     * 
     * @return Diameter of a pore of the membrane in m.
     */
    [[nodiscard]] T getPoreDiameter() const;

    /**
     * @brief Get the porosity of the membrane.
     * 
     * @return Porosity of the membrane in % (between 0.0 and 1.0).
     */
    [[nodiscard]] T getPorosity() const;

    /**
     * @brief Get the number of pores of the membrane.
     * @param area Area for which the number of pores should be calculated. This is used to get the number of pores for a specific area covered by one mixture.
     * @return The number of pores of the membrane.
     */
    [[nodiscard]] T getNumberOfPores(T area) const;

    /**
     * @brief Get the density of the pores on the membrane.
     * 
     * @return Density of the pores.
     */
    [[nodiscard]] T getPoreDensity() const;

    /**
     * @brief Returns area of a membrane.
     * @returns Area in m^2.
     */
    [[nodiscard]] T getArea() const;

    /**
     * @brief Calculates and returns volume of the membrane.
     * @returns Volume of a channel in m^3.
     */
    [[nodiscard]] T getVolume() const;

    /**
     * @brief Calculates and returns pressure difference over a channel.
     * @returns Pressure in Pa.
     */
    [[nodiscard]] T getPressure() const override;

    /**
     * @brief Calculate flow rate within the channel.
     * @returns Flow rate in m^3/s.
     */
    [[nodiscard]] T getFlowRate() const override;

    /**
     * @brief Calculate and returns overall resistance caused by the channel itself and the droplets within the channel.
     * @returns Overall resistance in Pas/m^3.
     */
    [[nodiscard]] T getResistance() const override;
};

}  // namespace arch
