#!/bin/bash

export eds="join.new input_file /home/shaun/Sesame/build/benchmark/datasets/EDS.txt : join.new num_points 245270 : join.new dim 2 : join.new num_clusters 363 : join.new arr_rate 1000,10000,20000,50000"

ticat ${meta} : mark-time bench.begin : ${eds} \
    : join.new algo 0 \
    : join.new max_in_nodes 100 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 100 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 2 \
    : join.new num_last_arr 2 \
    : join.new time_window 200 \
    : join.new num_online_clusters 1000 \
    : join.new radius 10 \
    : join.new buf_size 1500 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 4 \
    : join.new lambda 0.998 \
    : join.new radius 20 \
    : join.new clean_interval 400 \
    : join.new min_weight 0.5 \
    : join.new alpha 0.2 \
    : join.new base 2 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 3 \
    : join.new buf_size 500 \
    : join.new min_points 30 \
    : join.new epsilon 20 \
    : join.new base 2 \
    : join.new lambda 0.25 \
    : join.new mu 6 \
    : join.new beta 0.2 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 6 \
    : join.new lambda 0.998 \
    : join.new beta 0.001 \
    : join.new cm 4 \
    : join.new cl 2 \
    : join.new grid_width 4 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 5 \
    : join.new radius 30 \
    : join.new delta 300 \
    : join.new beta 1 \
    : join.new buf_size 4000 \
    : join.new alpha 0.998 \
    : join.new lambda 1 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 1 \
    : join.new seed 10 \
    : join.new coreset_size 5000 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 21 \
    : join.new max_in_nodes 100 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 100 \
    : join.new landmark 1000 \
    : join.new outlier_distance_threshold 15 \
    : join.new outlier_cap 500 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 22 \
    : join.new max_in_nodes 100 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 100 \
    : join.new landmark 1000 \
    : join.new outlier_distance_threshold 15 \
    : join.new outlier_cap 500 \
    : join.new min_points 10 \
    : join.new epsilon 10 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 23 \
    : join.new max_in_nodes 100 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 100 \
    : join.new landmark 1000 \
    : join.new outlier_distance_threshold 15 \
    : join.new outlier_cap 500 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 24 \
    : join.new max_in_nodes 100 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 100 \
    : join.new sliding 20000 \
    : join.new outlier_distance_threshold 15 \
    : join.new outlier_cap 500 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 25 \
    : join.new max_in_nodes 100 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 100 \
    : join.new landmark 1000 \
    : join.new outlier_distance_threshold 15 \
    : join.new outlier_cap 500 \
    : join.new lambda 0.5 \
    : join.new alpha 1.1 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 26 \
    : join.new max_in_nodes 100 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 100 \
    : join.new landmark 1000 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 27 \
    : join.new max_in_nodes 100 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 100 \
    : join.new landmark 1000 \
    : join.new outlier_density_threshold 100 \
    : join.new neighbor_distance 500 \
    : join.new outlier_cap 500 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 28 \
    : join.new distance_threshold 100 \
    : join.new landmark 1000 \
    : join.new outlier_distance_threshold 15 \
    : join.new outlier_cap 100 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 29 \
    : join.new beta 0.001,0.3 \
    : join.new cm 4 \
    : join.new cl 2 \
    : join.new landmark 1000 \
    : join.new outlier_distance_threshold 10 \
    : join.new outlier_cap 100 \
    : join.run run.sesame
ticat ${meta} : mark-time bench.begin : ${eds}\
    : join.new algo 7 \
    : join.new delta_grid 0.2 \
    : join.new num_samples 100 \
    : join.run run.sesame