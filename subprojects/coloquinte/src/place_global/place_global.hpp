#pragma once

#include <random>
#include <vector>

#include "coloquinte.hpp"
#include "place_global/density_legalizer.hpp"
#include "place_global/net_model.hpp"

namespace coloquinte {

/**
 * @brief Main class for global placement
 */
class GlobalPlacer {
 public:
  /**
   * @brief Run global placement on the circuit representation
   *
   * @param circuit The circuit to be modified
   * @param params Placement parameters
   */
  static void place(Circuit &circuit, const ColoquinteParameters &params,
                    const std::optional<PlacementCallback> &callback = {});

 private:
  /**
   * @brief Initialize the datastructure
   */
  explicit GlobalPlacer(Circuit &circuit, const ColoquinteParameters &params);

  /**
   * @brief Run the whole global placement algorithm
   */
  void run();

  /**
   * @brief Return the net model length of the lower-bound placement
   */
  float valueLB() const;

  /**
   * @brief Return the net model length of the upper-bound placement
   */
  float valueUB() const;

  /**
   * @brief Obtain the initial lower-bound placement
   */
  void runInitialLB();

  /**
   * @brief Obtain the lower-bound placement for one iteration
   */
  void runLB();

  /**
   * @brief Obtain the upper-bound placement for one iteration
   */
  void runUB();

  /**
   * @brief Call the callback with this placement
   */
  void callback(PlacementStep step, const std::vector<float> &xplace,
                const std::vector<float> &yplace);

  /**
   * @brief Export the placement to the ISPD circuit
   */
  void exportPlacement(Circuit &) const;

  /**
   * @brief Export a given placement to the ISPD circuit
   */
  static void exportPlacement(Circuit &, const std::vector<float> &xplace,
                              const std::vector<float> &yplace);

  /**
   * @brief Compute the average cell size of the circuit
   */
  float computeAverageCellSize() const;

  /**
   * @brief Compute the base penalty forces from the area of the cells
   */
  std::vector<float> computePerCellPenalty() const;

  /**
   * @brief Approximation distance used by the continuous model
   */
  float initialApproximationDistance() const {
    return params_.global.continuousModel.approximationDistance *
           averageCellLength_;
  }

  /**
   * @brief Distance at which the full displacement penalty is obtained
   */
  float initialPenaltyCutoffDistance() const {
    return params_.global.penalty.cutoffDistance * averageCellLength_;
  }

  /**
   * @brief Distance between upper and lower bound at which we stop placement
   */
  float distanceTolerance() const {
    return params_.global.distanceTolerance * averageCellLength_;
  }

  /**
   * @brief Compute the penalty forces for this iteration
   */
  std::vector<float> computeIterationPerCellPenalty();

  /**
   * @brief React to a change in cell sizes during a callback
   */
  void updateCellSizes();

  /**
   * @brief React to a change in nets during a callback
   */
  void updateNets();

 private:
  DensityLegalizer leg_;
  NetModel xtopo_;
  NetModel ytopo_;

  std::vector<float> xPlacementLB_;
  std::vector<float> yPlacementLB_;
  std::vector<float> xPlacementUB_;
  std::vector<float> yPlacementUB_;

  ColoquinteParameters params_;

  float averageCellLength_;
  std::vector<float> perCellPenalty_;
  int step_;
  float penalty_;
  float penaltyCutoffDistance_;
  float approximationDistance_;
  std::mt19937 rgen_;

  // Only for callbacks
  Circuit &circuit_;
  std::optional<PlacementCallback> callback_;
};

}  // namespace coloquinte