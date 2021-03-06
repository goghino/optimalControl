#!/bin/bash
MKLROOT=/opt/intel/compilers_and_libraries_2017/linux/mkl #archimedes
#MKLROOT=/apps/intel/17.0.0/mkl #ICS
PARDISO_DIR=/home/kardos/lib/pardiso
#MATLAB=/apps/matlab/R2016a
MATLAB=/opt/MATLAB/R2014b
../configure ADD_CXXFLAGS="-fPIC -fopenmp -m64" F77=gfortran CC=gcc CXX=g++ \
    --enable-static --enable-inexact-solver --disable-shared --with-pic \
    --enable-matlab-static --disable-dependency-linking --without-ma27 \
     --with-blas-lib="-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_core.a ${MKLROOT}/lib/intel64/libmkl_gnu_thread.a -Wl,--end-group -ldl -lpthread -lm"  \
    --with-lapack-lib="${MKLROOT}/lib/intel64/libmkl_lapack95_lp64.a" \
    --with-matlab-home=${MATLAB} \
    --with-pardiso="-Wl,--start-group ${PARDISO_DIR}/libpardiso.a  ${PARDISO_DIR}/libpils_pardiso.a ${PARDISO_DIR}/libmetis41_pardiso.a  ${PARDISO_DIR}/libmetis41-P_pardiso.a -Wl,--end-group  -ldl -lpthread -lm -lgomp -lgfortran" 
