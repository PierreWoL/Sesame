// Copyright (C) 2021 by the IntelliStream team
// (https://github.com/intellistream)

/**
 * @brief This is the main entry point of the entire program.
 * Users will typically access this file to use the stream clustering algorithm.
 * We use this as the entry point for benchmarking.
 */
#include "Algorithm/AlgorithmFactory.hpp"
#include "Sinks/DataSinkFactory.hpp"
#include "Sources/DataSourceFactory.hpp"
#include "Utils/BenchmarkUtils.hpp"
#include "Utils/Logger.hpp"

#include <gflags/gflags.h>

using namespace std;

DEFINE_string(input_file, "dataset/CoverType.txt", "Input file path");
DEFINE_int32(num_points, 3000, "Number of points");
DEFINE_int32(dim, 5, "Dimension of points");
DEFINE_int32(num_clusters, 7, "Number of clusters");
// BIRCH
DEFINE_int32(max_in_nodes, 100, "Maximum number of internal nodes");
DEFINE_int32(max_leaf_nodes, 100, "Maximum number of leaf nodes");
DEFINE_double(distance_threshold, 100.0, "Distance threshold");
// StreamKM++
DEFINE_int32(seed, 1, "Seed for random number generator");
DEFINE_int32(coreset_size, 100, "Coreset size");
// EDMStream
DEFINE_double(radius, 50.0, "Radius");
DEFINE_double(delta, 100.0, "Delta");
DEFINE_double(beta, 0.1, "Beta");
DEFINE_int32(buf_size, 100, "Buffer size");
DEFINE_double(alpha, 0.998, "Alpha");
DEFINE_double(lambda, 1.0, "Lambda");
// DBStream
DEFINE_int32(clean_interval, 400, "Clean interval");
DEFINE_double(min_weight, 0.5, "Minimum weight");
DEFINE_double(base, 2, "Base");
// DStream
DEFINE_double(cm, 5.0, "Cm");
DEFINE_double(cl, 0.8, "Cl");
DEFINE_double(grid_width, 12.0, "Grid width");
// DenStream
DEFINE_int32(min_points, 10, "Minimum points");
DEFINE_double(epsilon, 20.0, "Epsilon");
DEFINE_double(mu, 2.0, "Mu");
// Clustream
DEFINE_int32(num_last_arr, 2, "Number of last arrive");
DEFINE_int32(time_window, 200, "Time window");
DEFINE_int32(time_interval, 100, "Time interval"); // random
DEFINE_int32(num_online_clusters, 80, "Number of online clusters");
DEFINE_int32(offline_time_window, 200, "Offline time window"); // random
// SL-KMeans
DEFINE_double(
    delta_grid, 0.2,
    "The delta parameter used int the grid for guessing the optimum.");
DEFINE_int32(num_samples, 100, "Number of samples");

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);

  // Parse parameters.
  param_t cmd_params;
  BenchmarkUtils::defaultParam(cmd_params);
  // gen from gen_flags.js
  cmd_params.input_file = FLAGS_input_file;
  cmd_params.num_points = FLAGS_num_points;
  cmd_params.dim = FLAGS_dim;
  cmd_params.num_clusters = FLAGS_num_clusters;
  cmd_params.max_in_nodes = FLAGS_max_in_nodes;
  cmd_params.max_leaf_nodes = FLAGS_max_leaf_nodes;
  cmd_params.distance_threshold = FLAGS_distance_threshold;
  cmd_params.seed = FLAGS_seed;
  cmd_params.coreset_size = FLAGS_coreset_size;
  cmd_params.radius = FLAGS_radius;
  cmd_params.delta = FLAGS_delta;
  cmd_params.beta = FLAGS_beta;
  cmd_params.buf_size = FLAGS_buf_size;
  cmd_params.alpha = FLAGS_alpha;
  cmd_params.lambda = FLAGS_lambda;
  cmd_params.clean_interval = FLAGS_clean_interval;
  cmd_params.min_weight = FLAGS_min_weight;
  cmd_params.base = FLAGS_base;
  cmd_params.cm = FLAGS_cm;
  cmd_params.cl = FLAGS_cl;
  cmd_params.grid_width = FLAGS_grid_width;
  cmd_params.min_points = FLAGS_min_points;
  cmd_params.epsilon = FLAGS_epsilon;
  cmd_params.mu = FLAGS_mu;
  cmd_params.num_last_arr = FLAGS_num_last_arr;
  cmd_params.time_window = FLAGS_time_window;
  cmd_params.time_interval = FLAGS_time_interval;
  cmd_params.num_online_clusters = FLAGS_num_online_clusters;
  cmd_params.offline_time_window = FLAGS_offline_time_window;
  cmd_params.delta_grid = FLAGS_delta_grid;
  cmd_params.num_samples = FLAGS_num_samples;

  cmd_params.output_file = "results.txt";
  cmd_params.algo = SESAME::Generic;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  // Create Spout.
  SESAME::DataSourcePtr sourcePtr = SESAME::DataSourceFactory::create();

  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  SESAME::DataSinkPtr sinkPtr = SESAME::DataSinkFactory::create();

  // Create Algorithm.
  SESAME::AlgorithmPtr algoPtr = SESAME::AlgorithmFactory::create(cmd_params);

  // Run algorithm producing results.
  BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);
}
