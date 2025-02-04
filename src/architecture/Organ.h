/**
 * @file Organ.h
 */

#pragma once

#include "Channel.h"
#include "Edge.h"

namespace arch {

/**
 * @brief Class to specify a membrane, which is a component of a chip in which droplet can flow.
 */
template<typename T>
class Organ : public Edge<T> {
  private:
    T height = 0;           ///< Height of a membrane in m.
    T width = 0;            ///< Width of a membrane in m.
    T length = 0;           ///< Length of a membrane in m.
    T organResistance = 0;  ///< Resistance of the membrane in Pas/m^3.

  public:
    /**
     * @brief Constructor of a membrane.
     * @param[in] id Id of the membrane.
     * @param[in] node0 Node at one end of the membrane.
     * @param[in] node1 Node at other end of the membrane.
     * @param[in] height Height of the membrane in m.
     * @param[in] width Width of the membrane in m.
     * @param[in] length Length of the membrane in m.
     */
    Organ(int id, int node0, int node1, T height, T width, T length);

    /**
     * @brief Constructor of a membrane.
     * @param[in] id Id of the membrane.
     * @param[in] node0 Node at one end of the membrane.
     * @param[in] node1 Node at other end of the membrane.
     * @param[in] resistance Resistance of the membrane in Pas/m^3.
     * @param[in] type Type of the membrane.
     */
    Organ(int id, int node0, int node1, T resistance);

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
     * @brief Returns area of a membrane.
     * @returns Area in m^2.
     */
    [[nodiscard]] T getArea() const;

    /**
     * @brief Calculates and returns volume of the membrane.
     * @returns Volumne of a channel in m^3.
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
