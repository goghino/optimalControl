#!/bin/bash

# This scipt sets proper options in ipopt.opt required by SchurSolver.
# Particularly the dimension of the grid N and the number of stochastic scenarios NS.
# These parameter has to match with runtime parameters of the solve_problems
# $ mpirun -n NP ./solve_problem N NS, where N NS has to be same in the ipopt.opt
# Example:
# ./run.sh 2 10 2 schur     run 2 MPI processes using Schur solver (N>1 always)
# ./run.sh 1 10 2 pardiso   run !!single!! process with Pardiso (N=1 always)

OPENMPI_DIR=/home/kardos/privateapps/openmpi/2.0.1
MKLROOT=/apps/intel/17.0.0/mkl

# check command line arguments
if [ $# -ne 4 ]; then
    echo 'Usage: $./run.sh NP N NS SOLVER'
    echo 'SOLVER is pardiso or schur'
    exit
fi

NP=$1 # number of processes
N=$2  # dimension of the grid
NS=$3 # number of scenarios
SOLVER=$4 #linear solver

if [ -e ipopt.opt ]; then
    sed -i "s/^problem_dimension\ [0-9]*[[:space:]]*$/problem_dimension\ $N/g" ipopt.opt
    sed -i "s/^problem_scenarios\ [0-9]*[[:space:]]*$/problem_scenarios\ $NS/g" ipopt.opt
    sed -i "s/^linear_solver\ [a-z]*[[:space:]]*$/linear_solver\ $SOLVER/g" ipopt.opt
else
    echo "problem_dimension $N" > ipopt.opt
    echo "problem_scenarios $NS" >> ipopt.opt
    echo "linear_solver $SOLVER" >> ipopt.opt
fi

LD_LIBRARY_PATH=${MKLROOT}/lib/intel64:$LD_LIBRARY_PATH
LD_LIBRARY_PATH=~/PowerGrid/lib:$LD_LIBRARY_PATH
${OPENMPI_DIR}/bin/mpirun -np $NP ./solve_problem $N $NS
