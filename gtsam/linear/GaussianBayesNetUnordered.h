/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation, 
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    GaussianBayesNet.h
 * @brief   Chordal Bayes Net, the result of eliminating a factor graph
 * @brief   GaussianBayesNet
 * @author  Frank Dellaert
 */

// \callgraph

#pragma once

#include <gtsam/linear/GaussianConditionalUnordered.h>
#include <gtsam/inference/FactorGraphUnordered.h>
#include <gtsam/global_includes.h>

namespace gtsam {

  /** A Bayes net made from linear-Gaussian densities */
  class GTSAM_EXPORT GaussianBayesNetUnordered: public FactorGraphUnordered<GaussianConditionalUnordered> {

  public:

    typedef FactorGraphUnordered<GaussianConditionalUnordered> Base;
    typedef GaussianBayesNetUnordered This;
    typedef GaussianConditionalUnordered ConditionalType;
    typedef boost::shared_ptr<This> shared_ptr; 
    typedef boost::shared_ptr<ConditionalType> sharedConditional;

    /// @name Standard Constructors
    /// @{

    /** Construct empty factor graph */
    GaussianBayesNetUnordered() {}

    /** Construct from iterator over conditionals */
    template<typename ITERATOR>
    GaussianBayesNetUnordered(ITERATOR firstConditional, ITERATOR lastConditional) : Base(firstConditional, lastConditional) {}

    /// @}

    /// @name Testable
    /// @{

    /** Check equality */
    bool equals(const This& bn, double tol = 1e-9) const;

    /// @}

    /// @name Standard Interface
    /// @{

    /**
    * Solve the GaussianBayesNet, i.e. return \f$ x = R^{-1}*d \f$, computed by
    * back-substitution.
    */
    VectorValuesUnordered optimize() const;

    /**
     * Optimize along the gradient direction, with a closed-form computation to
     * perform the line search.  The gradient is computed about \f$ \delta x=0 \f$.
     *
     * This function returns \f$ \delta x \f$ that minimizes a reparametrized
     * problem.  The error function of a GaussianBayesNet is
     *
     * \f[ f(\delta x) = \frac{1}{2} |R \delta x - d|^2 = \frac{1}{2}d^T d - d^T R \delta x + \frac{1}{2} \delta x^T R^T R \delta x \f]
     *
     * with gradient and Hessian
     *
     * \f[ g(\delta x) = R^T(R\delta x - d), \qquad G(\delta x) = R^T R. \f]
     *
     * This function performs the line search in the direction of the
     * gradient evaluated at \f$ g = g(\delta x = 0) \f$ with step size
     * \f$ \alpha \f$ that minimizes \f$ f(\delta x = \alpha g) \f$:
     *
     * \f[ f(\alpha) = \frac{1}{2} d^T d + g^T \delta x + \frac{1}{2} \alpha^2 g^T G g \f]
     *
     * Optimizing by setting the derivative to zero yields
     * \f$ \hat \alpha = (-g^T g) / (g^T G g) \f$.  For efficiency, this function
     * evaluates the denominator without computing the Hessian \f$ G \f$, returning
     *
     * \f[ \delta x = \hat\alpha g = \frac{-g^T g}{(R g)^T(R g)} \f]
     *
     * @param bn The GaussianBayesNet on which to perform this computation
     * @return The resulting \f$ \delta x \f$ as described above
     */
    //VectorValuesUnordered optimizeGradientSearch() const;

    ///@}

    ///@name Linear Algebra
    ///@{
    
    /**
     * Return (dense) upper-triangular matrix representation
     */
    std::pair<Matrix, Vector> matrix() const;

    /**
     * Compute the gradient of the energy function,
     * \f$ \nabla_{x=x_0} \left\Vert \Sigma^{-1} R x - d \right\Vert^2 \f$,
     * centered around \f$ x = x_0 \f$.
     * The gradient is \f$ R^T(Rx-d) \f$.
     * @param bayesNet The Gaussian Bayes net $(R,d)$
     * @param x0 The center about which to compute the gradient
     * @return The gradient as a VectorValues
     */
    //VectorValuesUnordered gradient(const VectorValuesUnordered& x0) const;

    /**
     * Compute the gradient of the energy function,
     * \f$ \nabla_{x=0} \left\Vert \Sigma^{-1} R x - d \right\Vert^2 \f$,
     * centered around zero.
     * The gradient about zero is \f$ -R^T d \f$.  See also gradient(const GaussianBayesNet&, const VectorValues&).
     * @param bayesNet The Gaussian Bayes net $(R,d)$
     * @param [output] g A VectorValues to store the gradient, which must be preallocated, see allocateVectorValues
     * @return The gradient as a VectorValues
     */
    //VectorValuesUnordered gradientAtZero() const;

    /**
     * Computes the determinant of a GassianBayesNet. A GaussianBayesNet is an upper triangular
     * matrix and for an upper triangular matrix determinant is the product of the diagonal
     * elements. Instead of actually multiplying we add the logarithms of the diagonal elements and
     * take the exponent at the end because this is more numerically stable.
     * @param bayesNet The input GaussianBayesNet
     * @return The determinant */
    double determinant() const;

    /**
     * Computes the log of the determinant of a GassianBayesNet. A GaussianBayesNet is an upper
     * triangular matrix and for an upper triangular matrix determinant is the product of the
     * diagonal elements.
     * @param bayesNet The input GaussianBayesNet
     * @return The determinant */
    double logDeterminant() const;

    /**
     * Backsubstitute with a different RHS vector than the one stored in this BayesNet.
     * gy=inv(R*inv(Sigma))*gx
     */
    VectorValuesUnordered backSubstitute(const VectorValuesUnordered& gx) const;

    /**
     * Transpose backsubstitute with a different RHS vector than the one stored in this BayesNet.
     * gy=inv(L)*gx by solving L*gy=gx.
     * gy=inv(R'*inv(Sigma))*gx
     * gz'*R'=gx', gy = gz.*sigmas
     */
    VectorValuesUnordered backSubstituteTranspose(const VectorValuesUnordered& gx) const;

    /// @}
  };

} /// namespace gtsam
