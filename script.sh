#!/bin/bash
cd ../..
echo "Starting simple LTE scenario simulation."
./ns3 run scratch/L2Test/mylena-simple.cc --cwd=scratch/L2Test/L2testStats
echo "End of simulation."
echo "Calculating Throughput:"
g++ scratch/L2Test/L2test.cpp -o scratch/L2Test/L2test
./scratch/L2Test/L2test

