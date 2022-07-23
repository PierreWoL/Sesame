#!/bin/bash

. "`cd $(dirname ${BASH_SOURCE[0]}) && pwd`/all.sh"

ticat ${meta} : mark-time bench_begin : ${cover} \
    : join.new algo 24 \
    : join.new max_in_nodes 400 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 600 \
    : join.new sliding 10000 \
    : join.new outlier_distance_threshold 1000 \
    : join.new outlier_cap 500 \
    : join.run run.sesame

ticat ${meta} : mark-time bench_begin : ${kdd99} \
    : join.new algo 24 \
    : join.new max_in_nodes 400 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 600 \
    : join.new sliding 10000 \
    : join.new outlier_distance_threshold 1000 \
    : join.new outlier_cap 100 \
    : join.run run.sesame

ticat ${meta} : mark-time bench_begin : ${sensor} \
    : join.new algo 24 \
    : join.new max_in_nodes 1000 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 50 \
    : join.new sliding 1000 \
    : join.new outlier_distance_threshold 20 \
    : join.new outlier_cap 500 \
    : join.run run.sesame

ticat ${meta} : mark-time bench_begin : ${insects} \
    : join.new algo 24 \
    : join.new max_in_nodes 400 \
    : join.new max_leaf_nodes 100 \
    : join.new distance_threshold 600 \
    : join.new sliding 10000 \
    : join.new outlier_distance_threshold 1000 \
    : join.new outlier_cap 100 \
    : join.run run.sesame

# ticat ${meta} : mark-time bench.begin : ${eds} \
#     : join.new algo 24 \
#     : join.new max_in_nodes 100 \
#     : join.new max_leaf_nodes 100 \
#     : join.new distance_threshold 100 \
#     : join.new sliding 1000,10000,20000 \
#     : join.new outlier_distance_threshold 10,15 \
#     : join.new outlier_cap 100,300,500 \
#     : join.run run.sesame

# ticat ${meta} : mark-time bench.begin : ${edso} \
#     : join.new algo 24 \
#     : join.new max_in_nodes 100 \
#     : join.new max_leaf_nodes 100 \
#     : join.new distance_threshold 20 \
#     : join.new sliding 1000,10000,20000 \
#     : join.new outlier_distance_threshold 10,15 \
#     : join.new outlier_cap 100,300,500 \
#     : join.run run.sesame
