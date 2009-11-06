// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_PRISM2_3DLOCALFINITEELEMENT_HH
#define DUNE_PRISM2_3DLOCALFINITEELEMENT_HH

#include <dune/common/geometrytype.hh>

#include "common/localfiniteelement.hh"
#include "prismp2/prismp2localbasis.hh"
#include "prismp2/prismp2localcoefficients.hh"
#include "prismp2/prismp2localinterpolation.hh"

namespace Dune
{

  /** \todo Please doc me !
   */
  template<class D, class R>
  class PrismP2LocalFiniteElement
#ifdef DUNE_VIRTUAL_SHAPEFUNCTIONS
    : public LocalFiniteElementInterface<D,R,3>
#else
    : public LocalFiniteElementInterface<LocalFiniteElementTraits<PrismP2LocalBasis<D,R>,
              PrismP2LocalCoefficients,
              PrismP2LocalInterpolation<PrismP2LocalBasis<D,R> > >,
          PrismP2LocalFiniteElement<D,R> >
#endif
  {
  public:
    /** \todo Please doc me !
     */
    typedef LocalFiniteElementTraits<PrismP2LocalBasis<D,R>,
        PrismP2LocalCoefficients,
        PrismP2LocalInterpolation<PrismP2LocalBasis<D,R> > > Traits;

    /** \todo Please doc me !
     */
    PrismP2LocalFiniteElement ()
    {
      gt.makePrism();
    }

    /** \todo Please doc me !
     */
    const typename Traits::LocalBasisType& localBasis () const
    {
      return basis;
    }

    /** \todo Please doc me !
     */
    const typename Traits::LocalCoefficientsType& localCoefficients () const
    {
      return coefficients;
    }

    /** \todo Please doc me !
     */
    const typename Traits::LocalInterpolationType& localInterpolation () const
    {
      return interpolation;
    }

    /** \todo Please doc me !
     */
    GeometryType type () const
    {
      return gt;
    }

    PrismP2LocalFiniteElement* clone () const
    {
      return new PrismP2LocalFiniteElement(*this);
    }

  private:
    PrismP2LocalBasis<D,R> basis;
    PrismP2LocalCoefficients coefficients;
    PrismP2LocalInterpolation<PrismP2LocalBasis<D,R> > interpolation;
    GeometryType gt;
  };

}

#endif
