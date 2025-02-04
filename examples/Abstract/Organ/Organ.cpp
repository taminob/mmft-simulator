#include <baseSimulator.h>
#include <baseSimulator.hh>

#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using T = double;

/*
Membrane and Organ Tank Example based on 

Alan Chramiec et al. “Integrated human organ-on-a-chip model for predictive studies of anti-tumor drug efficacy and cardiac safety”. In: Lab Chip 20 (23 2020), pp. 4357–4372. DOI: 10.1039/D0LC00424C. URL: http://dx.doi.org/10.1039/ D0LC00424C (cit. on pp. 32, 59, 60, 61).

executed with MembraneResistanceModel9
*/
int main() {
    // create the simulator
    std::cout << "--- create simulation ---" << std::endl;
    sim::Simulation<T> sim;
    arch::Network<T> network;

    // flowRate pump
    std::cout << "--- define flow rate pumps ---" << std::endl;
    auto flowRate = 5.5e-8;  //3.3mL/min
    // create flow-rate pump from node -1 to node 0 with the given flow-rate
    auto pump0 = network.addFlowRatePump(0, -1, flowRate);

    // network setup
    std::cout << "--- define network (channels, membranes, organs) ---" << std::endl;
    auto cWidth = 5e-3;
    auto cHeight = 0.3e-3;          // mentioned in paper
    auto cConnectionLength = 5e-3;  // mentioned in paper

    auto cMembraneLength = 8e-3;   // mentioned in paper
    auto mHeight = 55e-6;          // membrane as stated in personal communication with the authors and according to specification on website
    auto mWidth = 4e-3;            // mentioned in paper
    auto pillarArea = 6.28318e-6;  // area covered by pillars
    auto poreRadius = 20e-6 / 2;   // pore size 20e-6 mentioned in paper, millipore size specifies size as diameter
    auto porosity = 0.14;

    auto oHeight = 13e-3;
    auto oWidth = 1.5e-6 / (oHeight * cMembraneLength);  //1.5mL organ volume mentioned in paper

    // create channels
    auto c1 = network.addChannel(0, 1, cHeight, cWidth, cMembraneLength, arch::ChannelType::NORMAL);  //bone tumor tissue
    auto c2 = network.addChannel(1, 2, cHeight, cWidth, cConnectionLength, arch::ChannelType::NORMAL);
    auto c3 = network.addChannel(2, -1, cHeight, cWidth, cMembraneLength, arch::ChannelType::NORMAL);  //cardiac tissue
    // create membrane and organ
    auto m4 = network.addMembraneToChannel(c1->getId(), mHeight, mWidth, poreRadius, porosity);
    auto o5 = network.addOrganToMembrane(m4, oHeight, oWidth);

    auto m6 = network.addMembraneToChannel(c3->getId(), mHeight, mWidth - pillarArea / cMembraneLength, poreRadius, porosity);
    auto o7 = network.addOrganToMembrane(m6, oHeight, oWidth);

    // define that node -1 is a sink
    std::cout << "--- define sink ---" << std::endl;
    network.setSink(-1);
    // define that node -1 is the ground node
    std::cout << "--- define ground ---" << std::endl;
    network.setGround(-1);

    // fluids
    std::cout << "--- define fluids ---" << std::endl;
    auto continuousPhaseFluid = sim.addFluid(0.7e-3, 0.993e3, 1.0, /*molecular size: 9e-10,*/ 4.4e-10, 0.0);
    auto injectionFluid = sim.addFluid(0.7e-3, 0.993e3, 1.0, /*molecular size: 9e-10,*/ 4.4e-10, 3.894e-3);  // Linsitinib

    // define which fluid is the continuous phase
    std::cout << "--- initialize with continuous phase ---" << std::endl;
    sim.setContinuousPhase(continuousPhaseFluid);

    // continuous fluid injection
    std::cout << "--- add continuous injection ---" << std::endl;
    sim.addMixtureInjection(injectionFluid->getId(), pump0->getId(), 0.0);

    // TODO: - add setter for Simulation::maxIterations (==simulationResultTimeStep/setSimulationDuration? What is the difference)
    //       - setSimulationCalculationTimeStep removed?
    //sim.setSimulationDuration(86400.0);  //24H
    //sim.setSimulationTimeStep(7200.0);   //2H // TODO: does not exist?
    //sim.setSimulationResultTimeStep(1800.0);  //0.5H
    //sim.setSimulationCalculationTimeStep(0.01);

    sim.setNetwork(&network);

    std::cout << "--- check chip network for validity ---" << std::endl;

    // check if chip is valid
    // TODO: is this actually the equivalent of sim.checkChipValidity()?
    if (network.isNetworkValid()) {
        std::cout << "network is VALID" << std::endl;
    } else {
        std::cout << "network is INVALID" << std::endl;
    }

    // simulate the microfluidic network
    try {
        sim.simulate();
    } catch (const std::exception& exception) {
        std::cerr << "An error occurred while running the simulation: " << exception.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while running the simulation!" << std::endl;
    }

    sim.getSimulationResults()->printLastState();

    // TODO: how to "getAverageFluidConcentrationsInEdge"?
    //sim.getSimulationResults()->getMixtures().at(0)->getSpecieConcentrations();
    //sim.getSimulationResults()->getStates().at(3);

    // auto fluidConcentrations3 = result.getAverageFluidConcentrationsInEdge(3 / 0.5, o5);
    // ASSERT_NEAR(fluidConcentrations3.at(injectionFluid), 0.7, 0.15);
    // auto fluidConcentrations6 = result.getAverageFluidConcentrationsInEdge(6 / 0.5, o5);
    // ASSERT_NEAR(fluidConcentrations6.at(injectionFluid), 0.9, 0.1);
    // auto fluidConcentrations12 = result.getAverageFluidConcentrationsInEdge(12 / 0.5, o5);
    // ASSERT_NEAR(fluidConcentrations12.at(injectionFluid), 0.96, 0.05);
    // auto fluidConcentrations24 = result.getAverageFluidConcentrationsInEdge(24 / 0.5, o5);
    // ASSERT_NEAR(fluidConcentrations24.at(injectionFluid), 1.0, 0.05);

    // fluidConcentrations3 = result.getAverageFluidConcentrationsInEdge(3 / 0.5, o7);
    // ASSERT_NEAR(fluidConcentrations3.at(injectionFluid), 0.6, 0.1);
    // fluidConcentrations6 = result.getAverageFluidConcentrationsInEdge(6 / 0.5, o7);
    // ASSERT_NEAR(fluidConcentrations6.at(injectionFluid), 0.8, 0.1);
    // fluidConcentrations12 = result.getAverageFluidConcentrationsInEdge(12 / 0.5, o7);
    // ASSERT_NEAR(fluidConcentrations12.at(injectionFluid), 0.92, 0.05);
    // fluidConcentrations24 = result.getAverageFluidConcentrationsInEdge(24 / 0.5, o7);
    // ASSERT_NEAR(fluidConcentrations24.at(injectionFluid), 1.0, 0.05);
}
