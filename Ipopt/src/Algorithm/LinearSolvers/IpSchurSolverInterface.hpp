// Copyright (C) 2004, 2010 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// $Id: IpSchurSolverInterface.hpp 1861 2010-12-21 21:34:47Z andreasw $
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2005-03-17


#ifndef __IPPARDISO_Schur_SOLVERINTERFACE_HPP__
#define __IPPARDISO_Schur_SOLVERINTERFACE_HPP__

#include "IpSparseSymLinearSolverInterface.hpp"
#include "SchurSolve.hpp"

//#define PARDISO_MATCHING_PREPROCESS

namespace Ipopt
{

  /** Interface to the linear solver Pardiso, derived from
   *  SparseSymLinearSolverInterface.  For details, see description of
   *  SparseSymLinearSolverInterface base class.
   */
  class SchurSolverInterface: public SparseSymLinearSolverInterface
  {
  public:
    /** @name Constructor/Destructor */
    //@{
    /** Constructor */
    SchurSolverInterface();

    /** Destructor */
    virtual ~SchurSolverInterface();
    //@}

    /** overloaded from AlgorithmStrategyObject */
    bool InitializeImpl(const OptionsList& options,
                        const std::string& prefix);


    /** @name Methods for requesting solution of the linear system. */
    //@{
    /** Method for initializing internal stuctures. */
    virtual ESymSolverStatus InitializeStructure(Index dim, Index nonzeros,
        const Index *ia,
        const Index *ja);

    /** Method returing an internal array into which the nonzero
     *  elements are to be stored. */
    virtual double* GetValuesArrayPtr();

    /** Solve operation for multiple right hand sides. */
    virtual ESymSolverStatus MultiSolve(bool new_matrix,
                                        const Index* ia,
                                        const Index* ja,
                                        Index nrhs,
                                        double* rhs_vals,
                                        bool check_NegEVals,
                                        Index numberOfNegEVals);

    /** Number of negative eigenvalues detected during last
     *  factorization.
     */
    virtual Index NumberOfNegEVals() const;
    //@}

    //* @name Options of Linear solver */
    //@{
    /** Request to increase quality of solution for next solve.
     */
    virtual bool IncreaseQuality();

    /** Query whether inertia is computed by linear solver.
     *  Returns true, if linear solver provides inertia.
     */
    virtual bool ProvidesInertia() const
    {
      return true;
    }
    /** Query of requested matrix type that the linear solver
     *  understands.
     */
    EMatrixFormat MatrixFormat() const
    {
      return CSR_Format_1_Offset;
    }
    //@}

    /** Methods for IpoptType */
    //@{
    static void RegisterOptions(SmartPtr<RegisteredOptions> roptions);
    //@}

  private:
    /**@name Default Compiler Generated Methods
     * (Hidden to avoid implicit creation/calling).
     * These methods are not implemented and 
     * we do not want the compiler to implement
     * them for us, so we declare them private
     * and do not define them. This ensures that
     * they will not be implicitly created/called. */
    //@{
    /** Copy Constructor */
    SchurSolverInterface(const SchurSolverInterface&);

    /** Overloaded Equals Operator */
    void operator=(const SchurSolverInterface&);
    //@}

    /** @name Information about the matrix */
    //@{
    /** Number of rows and columns of the matrix */
    Index dim_;

    /** Number of nonzeros of the matrix in triplet representation. */
    Index nonzeros_;

    /** Array for storing the values of the matrix. */
    double* a_;

    /* Problem parameters, dimension of the single scenario grid and number of scenarios*/
    Index N_;
    Index NS_;
    //@}

    // Schur solver
    SchurSolve schurSolver;

    /** @name Information about most recent factorization/solve */
    //@{
    /** Number of negative eigenvalues */
    Index negevals_;
    //@}

    /** @name Solver specific options */
    //@{

    /** @name Initialization flags */
    //@{
    /** Flag indicating if internal data is initialized.
     *  For initialization, this object needs to have seen a matrix */
    bool initialized_;
    //@}

    //@}
  };

} // namespace Ipopt
#endif
