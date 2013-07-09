/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation, 
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file SymbolicBayesTree.h
 * @date Oct 29, 2009
 * @author Frank Dellaert
 * @author Richard Roberts
 */

#pragma once

#include <gtsam/symbolic/SymbolicBayesNetUnordered.h>
#include <gtsam/symbolic/SymbolicFactorGraphUnordered.h>
#include <gtsam/inference/BayesTreeUnordered.h>
#include <gtsam/inference/BayesTreeCliqueBaseUnordered.h>

namespace gtsam {

  // Forward declarations
  class SymbolicConditionalUnordered;

  /* ************************************************************************* */
  /// A clique in a SymbolicBayesTree
  class GTSAM_EXPORT SymbolicBayesTreeCliqueUnordered :
    public BayesTreeCliqueBaseUnordered<SymbolicBayesTreeCliqueUnordered, SymbolicFactorGraphUnordered, SymbolicBayesNetUnordered>
  {
  public:
    typedef SymbolicBayesTreeCliqueUnordered This;
    typedef BayesTreeCliqueBaseUnordered<SymbolicBayesTreeCliqueUnordered, SymbolicFactorGraphUnordered, SymbolicBayesNetUnordered> Base;
    typedef boost::shared_ptr<This> shared_ptr;
    typedef boost::weak_ptr<This> weak_ptr;
    SymbolicBayesTreeCliqueUnordered() {}
    SymbolicBayesTreeCliqueUnordered(const boost::shared_ptr<SymbolicConditionalUnordered>& conditional) : Base(conditional) {}
  };

  /* ************************************************************************* */
  /// A Bayes tree that represents the connectivity between variables but is not associated with any
  /// probability functions.
  class GTSAM_EXPORT SymbolicBayesTreeUnordered :
    public BayesTreeUnordered<SymbolicBayesTreeCliqueUnordered>
  {
  private:
    typedef BayesTreeUnordered<SymbolicBayesTreeCliqueUnordered> Base;

  public:
    typedef SymbolicBayesTreeUnordered This;
    typedef boost::shared_ptr<This> shared_ptr;

    /** Default constructor, creates an empty Bayes tree */
    SymbolicBayesTreeUnordered() {}

    /** Makes a deep copy of the tree structure, but only pointers to conditionals are
     *  copied, the conditionals and their matrices are not cloned. */
    SymbolicBayesTreeUnordered(const SymbolicBayesTreeUnordered& other);

    /** Makes a deep copy of the tree structure, but only pointers to conditionals are
     *  copied, the conditionals and their matrices are not cloned. */
    SymbolicBayesTreeUnordered& operator=(const SymbolicBayesTreeUnordered& other);

    /** check equality */
    bool equals(const This& other, double tol = 1e-9) const;
  };

}
