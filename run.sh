#!/usr/bin/env bash

cd build
rm JMQ.root JMQ.out -rf
./JMQ JMQ.in > JMQ.out
cd ../analysis
root analysis.C
