#!/bin/bash

. "`cd $(dirname ${BASH_SOURCE[0]}) && pwd`/all.sh"

ticat ${meta} : mark-time bench_begin : ${cover} \
    : join.new algo 25 \
    : join.new max_in_nodes 400 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 600 \
    : join.new outlier_distance_threshold 1000 \
    : join.new outlier_cap 500 \
    : join.new lambda 2 \
    : join.new alpha 1.1 \
    : join.run run.sesame

ticat ${meta} : mark-time bench_begin : ${kdd99} \
    : join.new algo 25 \
    : join.new max_in_nodes 400 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 600 \
    : join.new outlier_distance_threshold 1000 \
    : join.new outlier_cap 100 \
    : join.new lambda 0.5 \
    : join.new alpha 1.1 \
    : join.run run.sesame

ticat ${meta} : mark-time bench_begin : ${sensor} \
    : join.new algo 25 \
    : join.new max_in_nodes 1000 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 50 \
    : join.new outlier_distance_threshold 20 \
    : join.new outlier_cap 100 \
    : join.new lambda 0.5 \
    : join.new alpha 2 \
    : join.run run.sesame

# ticat ${meta} : mark-time bench.begin : ${eds} \
#     : join.new algo 25 \
#     : join.new max_in_nodes 100 \
#     : join.new max_leaf_nodes 100 \
#     : join.new distance_threshold 100 \
#     : join.new outlier_distance_threshold 10,15 \
#     : join.new outlier_cap 100,300,500 \
#     : join.new lambda 0.5,1.5,2 \
#     : join.new alpha 1.1,1.5,2 \
#     : join.run run.sesame

# ticat ${meta} : mark-time bench.begin : ${edso} \
#     : join.new algo 25 \
#     : join.new max_in_nodes 100 \
#     : join.new max_leaf_nodes 100 \
#     : join.new distance_threshold 20 \
#     : join.new outlier_distance_threshold 10,15 \
#     : join.new outlier_cap 100,300,500 \
#     : join.new lambda 0.5,1.5,2 \
#     : join.new alpha 1.1,1.5,2 \
#     : join.run run.sesame