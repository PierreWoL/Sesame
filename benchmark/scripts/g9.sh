#!/bin/bash

. "`cd $(dirname ${BASH_SOURCE[0]}) && pwd`/part.sh"

ticat ${meta} : mark-time bench_begin : ${cover} \
    : join.new algo 29 \
    : join.new beta 0.001,0.3 \
    : join.new cm [5,20,5] \
    : join.new cl 0.8,1.0,0.001 \
    : join.new landmark 1000,10000,20000 \
    : join.new outlier_distance_threshold 1000 \
    : join.new outlier_cap 100,300,500 \
    : join.run run.sesame

ticat ${meta} : mark-time bench_begin : ${kdd99} \
    : join.new algo 29 \
    : join.new beta 0.001,0.3 \
    : join.new cm 1.001,3 \
    : join.new cl 0.7,0.8,0.9,0.999,0.1001 \
    : join.new landmark 1000,10000,20000 \
    : join.new outlier_distance_threshold 1000 \
    : join.new outlier_cap 100,300,500 \
    : join.run run.sesame

ticat ${meta} : mark-time bench_begin : ${sensor} \
    : join.new algo 29 \
    : join.new beta 0.001 \
    : join.new cm 4 \
    : join.new cl 2 \
    : join.new landmark 1000,10000,20000 \
    : join.new outlier_distance_threshold 20 \
    : join.new outlier_cap 100,300,500 \
    : join.run run.sesame

ticat ${meta} : mark-time bench.begin : ${eds} \
    : join.new algo 29 \
    : join.new beta 0.001,0.3 \
    : join.new cm 4 \
    : join.new cl 2 \
    : join.new landmark 1000,10000,20000 \
    : join.new outlier_distance_threshold 10,15 \
    : join.new outlier_cap 100,300,500 \
    : join.run run.sesame

ticat ${meta} : mark-time bench.begin : ${edso} \
    : join.new algo 29 \
    : join.new beta 0.001,0.3 \
    : join.new cm 4\
    : join.new cl 2 \
    : join.new landmark 1000,10000,20000 \
    : join.new outlier_distance_threshold 10,15 \
    : join.new outlier_cap 100,300,500 \
    : join.run run.sesame