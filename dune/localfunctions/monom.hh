// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:

#ifndef DUNE_MONOMLOCALFINITEELEMENT_HH
#define DUNE_MONOMLOCALFINITEELEMENT_HH

#warning This file is deprecated.  Please use monomial.hh instead!

#include <dune/localfunctions/monomial.hh>

namespace Dune
{
  /** \deprecated Deprecated in 2.4, only here for backward-compatibility */
  template<class D, class R, int d, int p, int diffOrder = p>
  class DUNE_DEPRECATED_MSG("Use MonomialLocalFiniteElement instead!") MonomLocalFiniteElement
  {
    enum { static_size = MonomImp::Size<d,p>::val };

  public:
    /** Traits class
     */
    typedef LocalFiniteElementTraits<
        MonomialLocalBasis<D,R,d,p, diffOrder>,
        MonomialLocalCoefficients<static_size>,
        MonomialLocalInterpolation<MonomialLocalBasis<D,R,d,p, diffOrder>,static_size>
        > Traits;

    //! Construct a MonomLocalFiniteElement
    MonomLocalFiniteElement (const GeometryType &gt_)
      : basis(), interpolation(gt_, basis), gt(gt_)
    {}

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

    /** \brief Number of shape functions in this finite element */
    unsigned int size () const
    {
      return basis.size();
    }

    /** \todo Please doc me !
     */
    GeometryType type () const
    {
      return gt;
    }

  private:
    MonomialLocalBasis<D,R,d,p, diffOrder> basis;
    MonomialLocalCoefficients<static_size> coefficients;
    MonomialLocalInterpolation<MonomialLocalBasis<D,R,d,p, diffOrder>,static_size> interpolation;
    GeometryType gt;
  };

    /** \deprecated Deprecated in 2.4, will be removed in 3.0 */
  template<class Geometry, class RF, std::size_t p>
  class DUNE_DEPRECATED_MSG("Use MonomialFiniteElementFactory instead!") MonomFiniteElementFactory {
    typedef typename Geometry::ctype DF;
    static const std::size_t dim = Geometry::mydimension;

    typedef MonomLocalFiniteElement<DF, RF, dim, p> LocalFE;

    std::vector<std::shared_ptr<const LocalFE> > localFEs;

    void init(const GeometryType &gt) {
      std::size_t index = gt.id() >> 1;
      if(localFEs.size() <= index)
        localFEs.resize(index+1);
      localFEs[index].reset(new LocalFE(gt));
    }

  public:
    typedef ScalarLocalToGlobalFiniteElementAdaptor<LocalFE, Geometry>
    FiniteElement;

    template<class ForwardIterator>
    MonomFiniteElementFactory(const ForwardIterator &begin,
                              const ForwardIterator &end)
    {
      for(ForwardIterator it = begin; it != end; ++it)
        init(*it);
    }

    MonomFiniteElementFactory(const GeometryType &gt)
    { init(gt); }

    MonomFiniteElementFactory() {
      static_assert(dim <= 3, "MonomFiniteElementFactory knows the "
                    "available geometry types only up to dimension 3");

      GeometryType gt;
      switch(dim) {
      case 0 :
        gt.makeVertex();        init(gt);
        break;
      case 1 :
        gt.makeLine();          init(gt);
        break;
      case 2 :
        gt.makeTriangle();      init(gt);
        gt.makeQuadrilateral(); init(gt);
        break;
      case 3 :
        gt.makeTetrahedron();   init(gt);
        gt.makePyramid();       init(gt);
        gt.makePrism();         init(gt);
        gt.makeHexahedron();    init(gt);
        break;
      default :
        // this should never happen -- it should be caught by the static
        // assert above.
        std::abort();
      };
    }

    const FiniteElement make(const Geometry& geometry) {
      std::size_t index = geometry.type().id() >> 1;
      assert(localFEs.size() > index && localFEs[index]);
      return FiniteElement(*localFEs[index], geometry);
    }
  };

}
#endif // DUNE_MONOMLOCALFINITEELEMENT_HH
