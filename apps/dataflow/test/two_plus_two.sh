#!/bin/bash

ADD=1
SUB=2
MUL=3
DIV=4
SQR=5

# Start the namespace platform
echo "Starting namespace platform..."
/home/centos/cspot/build/bin/woofc-namespace-platform -N /home/centos/cspot/apps/dataflow/test >& namespace.log &
PLATFORM_PID=$! # Save PID to kill later
sleep 3 # Sleep for 3 seconds

# Initialize the program
echo "\nInitializing program...\n"
./dfinit -W test -s 10000

# Add the ADD node (node 1, outputs to node 0)
echo "\nAdding nodes...\n"
./dfaddnode -W test -o $ADD -i 1 -d 0

# Add the operands (output to node 1)
echo "\nAdding operands...\n"
./dfaddoperand -W test -d 1 -V 2.0
./dfaddoperand -W test -d 1 -V 2.0

sleep 1

# Kill the platform
kill ${PLATFORM_PID}

# Clean up
rm -f test.df* cspot-log.*

echo "Done"