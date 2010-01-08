// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_MIMETIC_ALL_HH
#define DUNE_MIMETIC_ALL_HH

#include <cstddef>

#include <dune/common/exceptions.hh>
#include <dune/common/fvector.hh>
#include <dune/common/geometrytype.hh>

#include "../common/localbasis.hh"
#include "../common/localcoefficients.hh"
#include "../common/localinterpolation.hh"

namespace Dune
{
  template<class D, class R, int dim>
  class MimeticLocalBasis :
    public Dune::C0LocalBasisInterface<
        Dune::C0LocalBasisTraits<D,dim,Dune::FieldVector<D,dim>,
            R,1,Dune::FieldVector<R,1> >,
        MimeticLocalBasis<D,R,dim> >
  {
  public:
    typedef Dune::C0LocalBasisTraits<D,dim,Dune::FieldVector<D,dim>,
        R,1,Dune::FieldVector<R,1> > Traits;

    MimeticLocalBasis (unsigned int variant_)
      : variant(variant_)
    {}

    MimeticLocalBasis ()
      : variant(0)
    {}

    unsigned int size () const { return variant; }

    //! \brief Evaluate all shape functions
    inline void evaluateFunction (
      const typename Traits::DomainType& in,
      std::vector<typename Traits::RangeType>& out) const
    {
      DUNE_THROW(Dune::Exception,"mimetic basis evaluation not available");
    }

    //! \brief Polynomial order of the shape functions
    unsigned int order () const
    {
      DUNE_THROW(Dune::Exception,"mimetic order evaluation not available");
    }

  private:
    unsigned int variant;
  };

  template<class LB>
  class MimeticLocalInterpolation : public Dune::
                                    LocalInterpolationInterface<MimeticLocalInterpolation<LB> > {
  public:

    //! \brief Local interpolation of a function
    template<typename F, typename C>
    void interpolate (const F& f, std::vector<C>& out) const {
      DUNE_THROW(Dune::Exception,"mimetic local interpolation not available");
    }
  };

  /** \brief !
      \implements Dune::LocalCoefficientsVirtualImp
   */
  class MimeticLocalCoefficients
  {
  public:
    MimeticLocalCoefficients (unsigned int variant_)
      : variant(variant_), li(variant_)
    {
      for (int i=0; i<variant; i++) li[i] = Dune::LocalKey(i,Dune::intersectionCodim,0);
    }

    MimeticLocalCoefficients ()
      : variant(0), li(0)
    {}

    //! number of coefficients
    std::size_t size () const { return variant; }

    //! map index i to local key
    const Dune::LocalKey& localKey (std::size_t i) const {
      return li[i];
    }

  private:
    unsigned int variant;
    std::vector<Dune::LocalKey> li;
  };
}

#endif