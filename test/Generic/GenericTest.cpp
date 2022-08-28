// Copyright (C) 2021 by the IntelliStream team
// (https://github.com/intellistream)

//
// Created by wzru on 2022/3/24.
//

#include "Algorithm/DesignAspect/Generic.hpp"
#include "Algorithm/DataStructure/CFTree.hpp"
#include "Algorithm/DataStructure/GenericFactory.hpp"
#include "Algorithm/OfflineRefinement/DBSCAN.hpp"
#include "Algorithm/OfflineRefinement/KMeans.hpp"
#include "Algorithm/OfflineRefinement/OfflineRefinement.hpp"
#include "Algorithm/OutlierDetection/OutlierDetection.hpp"
#include "Algorithm/WindowModel/WindowModel.hpp"
#include "Sinks/DataSinkFactory.hpp"
#include "Sources/DataSourceFactory.hpp"
#include "Utils/BenchmarkUtils.hpp"
#include "Utils/Logger.hpp"

#include "gtest/gtest.h"

#include <filesystem>

using namespace SESAME;

TEST(GenericTest, V1) {
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // Parse parameters.
  param_t cmd_params;
  cmd_params.num_points = 3000;
  cmd_params.distance_threshold = 100;
  cmd_params.max_in_nodes = 10;
  cmd_params.max_leaf_nodes = 20;
  cmd_params.num_clusters = 7;
  cmd_params.dim = 54;
  cmd_params.seed = 10;
  cmd_params.num_clusters = 7;
  cmd_params.time_decay = false;
  cmd_params.landmark = 1000;
  cmd_params.outlier_distance_threshold = 5000;
  cmd_params.outlier_cap = 10;
  cmd_params.kmeansK = 100;

  cmd_params.input_file = std::filesystem::current_path().generic_string() +
                         "/datasets/CoverType.txt";
  cmd_params.output_file = "results.txt";
  cmd_params.algo = Generic;
  cmd_params.run_offline = true;

  std::vector<PointPtr> input;
  std::vector<PointPtr> results;

  // Create Spout.
  DataSourcePtr sourcePtr = GenericFactory::New<DataSource>(cmd_params);
  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  DataSinkPtr sinkPtr = GenericFactory::New<DataSink>(cmd_params);

  // Create Algorithm.
  AlgorithmPtr algoPtr = GenericFactory::New<StreamClustering<
      Landmark, ClusteringFeaturesTree, DistanceDetection, KMeans>>(cmd_params);

  // Run algorithm producing results.
  auto res =
      BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);

  ASSERT_NEAR(res->purity, 0.433, 0.03);
  ASSERT_NEAR(res->cmm, 0.7869, 0.03);
}

TEST(GenericTest, V2) {
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // Parse parameters.
  param_t cmd_params;
  cmd_params.num_points = 3000;
  cmd_params.distance_threshold = 100;
  cmd_params.max_in_nodes = 10;
  cmd_params.max_leaf_nodes = 20;
  cmd_params.dim = 54;
  cmd_params.num_clusters = 7;
  cmd_params.time_decay = false;
  cmd_params.min_points = 10;
  cmd_params.landmark = 1000;
  cmd_params.epsilon = 200; // 0.1
  cmd_params.run_offline = true;
  cmd_params.outlier_distance_threshold = 5000;
  cmd_params.outlier_cap = 10;

  cmd_params.input_file = std::filesystem::current_path().generic_string() +
                         "/datasets/CoverType.txt";
  cmd_params.output_file = "results.txt";
  cmd_params.algo = SESAME::Generic;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  // Create Spout.
  SESAME::DataSourcePtr sourcePtr = GenericFactory::New<DataSource>(cmd_params);
  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  SESAME::DataSinkPtr sinkPtr = GenericFactory::New<DataSink>(cmd_params);

  // Create Algorithm.
  AlgorithmPtr algoPtr = GenericFactory::New<StreamClustering<
      Landmark, ClusteringFeaturesTree, DistanceDetection, DBSCAN>>(cmd_params);

  // Run algorithm producing results.
  auto res =
      BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);

  ASSERT_NEAR(res->purity, 0.2987, 0.02);
  ASSERT_NEAR(res->cmm, 0.0096, 0.02);
}

TEST(GenericTest, V3) {
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // Parse parameters.
  param_t cmd_params;
  cmd_params.num_points = 45690;
  cmd_params.distance_threshold = 50;
  cmd_params.max_in_nodes = 100;
  cmd_params.max_leaf_nodes = 100;
  cmd_params.dim = 2;
  cmd_params.num_clusters = 75;
  cmd_params.time_decay = true;
  cmd_params.landmark = 0;
  cmd_params.outlier_distance_threshold = 500;
  cmd_params.outlier_cap = 2000;

//  cmd_params.num_points = 3000;
//  cmd_params.distance_threshold = 1000;
//  cmd_params.max_in_nodes = 20;
//  cmd_params.max_leaf_nodes = 40;
//  cmd_params.dim = 54;
//  cmd_params.seed = 10;
//  cmd_params.num_clusters = 7;
//  cmd_params.time_decay = false;
//  cmd_params.landmark = 1000;
//  cmd_params.outlier_distance_threshold = 5000;
//  cmd_params.outlier_cap = 10;

  cmd_params.input_file = std::filesystem::current_path().generic_string() +
                         "/datasets/EDS.txt";
  cmd_params.output_file = "results.txt";
  cmd_params.algo = SESAME::Generic;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  // Create Spout.
  SESAME::DataSourcePtr sourcePtr = GenericFactory::New<DataSource>(cmd_params);
  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  SESAME::DataSinkPtr sinkPtr = GenericFactory::New<DataSink>(cmd_params);

  // Create Algorithm.
  AlgorithmPtr algoPtr =
      GenericFactory::New<StreamClustering<Landmark, ClusteringFeaturesTree,
                                           DistanceDetection, NoRefinement>>(
          cmd_params);

  // Run algorithm producing results.
  auto res =
      BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);

//  ASSERT_NEAR(res->purity, 0.403, 0.01);
}

TEST(GenericTest, V4) {
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // Parse parameters.
  param_t cmd_params;
  cmd_params.num_points = 3000;
  cmd_params.distance_threshold = 100;
  cmd_params.max_in_nodes = 20;
  cmd_params.max_leaf_nodes = 40;
  cmd_params.dim = 54;
  cmd_params.num_clusters = 7;
  cmd_params.time_decay = false;
  cmd_params.sliding = 1000;
  cmd_params.outlier_distance_threshold = 3000;
  cmd_params.outlier_cap = 3;

  cmd_params.input_file = std::filesystem::current_path().generic_string() +
                         "/datasets/CoverType.txt";
  cmd_params.output_file = "results.txt";
  cmd_params.algo = SESAME::Generic;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  // Create Spout.
  SESAME::DataSourcePtr sourcePtr = GenericFactory::New<DataSource>(cmd_params);
  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  SESAME::DataSinkPtr sinkPtr = GenericFactory::New<DataSink>(cmd_params);

  // Create Algorithm.
  AlgorithmPtr algoPtr =
      GenericFactory::New<StreamClustering<Sliding, ClusteringFeaturesTree,
                                           DistanceDetection, NoRefinement>>(
          cmd_params);

  // Run algorithm producing results.
  auto res =
      BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);

  ASSERT_NEAR(res->purity, 0.64, 0.02);
}

TEST(GenericTest, V5) {
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // Parse parameters.
  param_t cmd_params;
  cmd_params.num_points = 3000;
  cmd_params.distance_threshold = 1000;
  cmd_params.max_in_nodes = 20;
  cmd_params.max_leaf_nodes = 40;
  cmd_params.dim = 54;
  cmd_params.num_clusters = 7;
  cmd_params.time_decay = false;
  cmd_params.lambda = 1.25;
  cmd_params.alpha = 2;
  cmd_params.outlier_distance_threshold = 5000;
  cmd_params.outlier_cap = 10;

  cmd_params.input_file = std::filesystem::current_path().generic_string() +
                         "/datasets/CoverType.txt";
  cmd_params.output_file = "results.txt";
  cmd_params.algo = SESAME::Generic;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  // Create Spout.
  SESAME::DataSourcePtr sourcePtr = GenericFactory::New<DataSource>(cmd_params);
  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  SESAME::DataSinkPtr sinkPtr = GenericFactory::New<DataSink>(cmd_params);

  // Create Algorithm.
  AlgorithmPtr algoPtr =
      GenericFactory::New<StreamClustering<Damped, ClusteringFeaturesTree,
                                           DistanceDetection, NoRefinement>>(
          cmd_params);

  // Run algorithm producing results.
  auto res =
      BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);

  ASSERT_NEAR(res->purity, 0.2987, 0.01);
}

TEST(GenericTest, V6) {
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // Parse parameters.
  param_t cmd_params;

  cmd_params.num_points = 245270;
  cmd_params.distance_threshold = 10;
  cmd_params.max_in_nodes = 100;
  cmd_params.max_leaf_nodes = 50;
  cmd_params.dim = 2;
  cmd_params.num_clusters = 363;
  cmd_params.time_decay = false;
  cmd_params.landmark = 1000;

  cmd_params.input_file = std::filesystem::current_path().generic_string() +
                         "/datasets/EDS.txt";
  cmd_params.output_file = "results.txt";
  cmd_params.algo = SESAME::V6Stream;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  // Create Spout.
  SESAME::DataSourcePtr sourcePtr = GenericFactory::New<DataSource>(cmd_params);
  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  SESAME::DataSinkPtr sinkPtr = GenericFactory::New<DataSink>(cmd_params);

  // Create Algorithm.
  AlgorithmPtr algoPtr = GenericFactory::New<StreamClustering<
      Landmark, ClusteringFeaturesTree, NoDetection, NoRefinement>>(cmd_params);

  // Run algorithm producing results.
  auto res =
      BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);

//  ASSERT_NEAR(res->purity, 0.3987, 0.01);
}

TEST(GenericTest, V7) {
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // Parse parameters.
  param_t cmd_params;
  cmd_params.num_points = 3000;
  cmd_params.distance_threshold = 1000;
  cmd_params.max_in_nodes = 20;
  cmd_params.max_leaf_nodes = 40;
  cmd_params.dim = 54;
  cmd_params.num_clusters = 7;
  cmd_params.time_decay = false;
  cmd_params.landmark = 1000;
  cmd_params.neighbor_distance = 5000;
  cmd_params.outlier_density_threshold = 0.5;
  cmd_params.outlier_cap = 10;

  cmd_params.input_file = std::filesystem::current_path().generic_string() +
                         "/datasets/CoverType.txt";
  cmd_params.output_file = "results.txt";
  cmd_params.algo = SESAME::V7Stream;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  // Create Spout.
  SESAME::DataSourcePtr sourcePtr = GenericFactory::New<DataSource>(cmd_params);
  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  SESAME::DataSinkPtr sinkPtr = GenericFactory::New<DataSink>(cmd_params);

  // Create Algorithm.
  AlgorithmPtr algoPtr =
      GenericFactory::New<StreamClustering<Landmark, ClusteringFeaturesTree,
                                           DensityDetection, NoRefinement>>(
          cmd_params);

  // Run algorithm producing results.
  auto res =
      BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);

  ASSERT_NEAR(res->purity, 0.401, 0.01);
}

TEST(GenericTest, V8) {
  // Setup Logs.
  setupLogging("benchmark.log", LOG_DEBUG);
  // Parse parameters.
  param_t cmd_params;
  cmd_params.num_points = 45690;
  cmd_params.distance_threshold = 50;
  cmd_params.max_in_nodes = 100;
  cmd_params.max_leaf_nodes = 100;
  cmd_params.dim = 2;
  cmd_params.num_clusters = 75;
  cmd_params.time_decay = true;
  cmd_params.landmark = 0;
  cmd_params.run_offline = false;
  cmd_params.outlier_distance_threshold = 600;
  cmd_params.outlier_cap = 2000;

  cmd_params.input_file = std::filesystem::current_path().generic_string() +
                         "/datasets/EDS.txt";
  cmd_params.output_file = "results.txt";
  cmd_params.algo = SESAME::V8Stream;

  std::vector<SESAME::PointPtr> input;
  std::vector<SESAME::PointPtr> results;

  // Create Spout.
  SESAME::DataSourcePtr sourcePtr = GenericFactory::New<DataSource>(cmd_params);
  // Directly load data from file. TODO: configure it to load from external
  // sensors, e.g., HTTP.
  BenchmarkUtils::loadData(cmd_params, sourcePtr);

  // Create Sink.
  SESAME::DataSinkPtr sinkPtr = GenericFactory::New<DataSink>(cmd_params);

  // Create Algorithm.
  AlgorithmPtr algoPtr =
      GenericFactory::New<StreamClustering<Landmark, ClusteringFeaturesList,
                                           DistanceDetection, NoRefinement>>(
          cmd_params);

  // Run algorithm producing results.
  auto res =
      BenchmarkUtils::runBenchmark(cmd_params, sourcePtr, sinkPtr, algoPtr);

//  ASSERT_NEAR(res->purity, 0.3887, 0.01);
}
