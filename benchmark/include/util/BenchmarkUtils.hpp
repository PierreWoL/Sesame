//
// Created by Shuhao Zhang on 19/07/2021.
//

#ifndef ONLINEMLBENCHMARK_BENCHMARK_SRC_UTIL_BENCHMARKUTILS_HPP_
#define ONLINEMLBENCHMARK_BENCHMARK_SRC_UTIL_BENCHMARKUTILS_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <Algorithm/DataStructure/Point.hpp>

struct param_t {
  int pointNumber;
  int clusterNumber;
  int dimension;
  int coresetSize;
  int seed;
  std::string inputPath;
  std::string outputPath;
  std::string algoName;
};

class BenchmarkUtils {
 public:
  static void parseArgs(int argc, char **argv, param_t *cmd_params);
  static void defaultParam(param_t *cmd_params);
  static void print_help(char *string);
  static void loadData(param_t *cmd_params, Point *input);
  static void runBenchmark(param_t *cmd_params, Point *input, Point *results);
  static void evaluate(param_t *cmd_params, Point *input, Point *results);
};

#endif // ONLINEMLBENCHMARK_BENCHMARK_SRC_UTIL_BENCHMARKUTILS_HPP_
