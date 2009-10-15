// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_FIELD_HH
#define DUNE_FIELD_HH

#include <dune/alglib/multiprecision.hh>
#include <dune/common/fvector.hh>

namespace Dune
{

  // Unity
  // -----

  template< class Field >
  struct Unity
  {
    operator Field () const
    {
      return Field( 1 );
    }
  };



  template< class Field >
  Field operator+ ( const Unity< Field > &u, const Field &f )
  {
    return (Field)u + f;
  }

  template< class Field >
  Field operator- ( const Unity< Field > &u, const Field &f )
  {
    return (Field)u - f;
  }

  template< class Field >
  Field operator* ( const Unity< Field > &u, const Field &f )
  {
    return f;
  }

  template< class Field >
  Field operator/ ( const Unity< Field > &u, const Field &f )
  {
    return (Field)u / f;
  }



  // Zero
  // ----

  template< class Field >
  struct Zero
  {
    operator Field () const
    {
      return Field( 0 );
    }
    static const Field epsilon()
    {
      return Field(1e-12);
    }
  };
  template< unsigned int precision >
  struct Zero< amp::ampf< precision > >
  {
    typedef amp::ampf< precision > Field;
    operator Field () const
    {
      return Field( 0 );
    }
    static const Field epsilon()
    {
      return Field(1e-20);
    }
  };

  template< class Field >
  inline bool operator == ( const Zero< Field > &, const Field &f )
  {
    return ( f < Zero<Field>::epsilon() && f > -Zero<Field>::epsilon() );
  }

  template< class Field >
  inline bool operator == ( const Field &f, const Zero< Field > &z)
  {
    return ( z == f );
  }

  template< class Field >
  inline bool operator< ( const Zero< Field > &, const Field &f )
  {
    return f > Zero<Field>::epsilon();
  }

  template< class Field >
  inline bool operator< ( const Field &f, const Zero< Field > & )
  {
    return f < -Zero<Field>::epsilon();
  }

  template< class Field >
  inline bool operator> ( const Zero< Field > &z, const Field &f )
  {
    return f < z;
  }

  template< class Field >
  inline bool operator> ( const Field &f, const Zero< Field > &z )
  {
    return z < f;
  }

  // Precision
  // ---------

  template <class Field>
  struct Precision;

  template<>
  struct Precision< double >
  {
    static const unsigned int value = 64;
  };

  template<>
  struct Precision< long double >
  {
    static const unsigned int value = 80;
  };

  template<>
  struct Precision< float >
  {
    static const unsigned int value = 32;
  };

  template< unsigned int precision >
  struct Precision< amp::ampf< precision > >
  {
    static const unsigned int value = precision;
  };



  // ComputeField
  // ------------

  template <class Field,unsigned int sum>
  struct ComputeField
  {
    typedef amp::ampf<Precision<Field>::value+sum> Type;
  };

}

// field_cast
// ----------

template< class F2, class F1 >
inline void field_cast ( const F1 &f1, F2 &f2 )
{
  f2 = f1;
}

template< unsigned int precision >
inline void field_cast ( const amp::ampf< precision > &f1, double &f2 )
{
  f2 = f1.toDouble();
}

template< unsigned int precision >
inline void field_cast ( const amp::ampf< precision > &f1, long double &f2 )
{
  f2 = f1.toDouble();
}

template< class F2, class F1, int dim >
inline void field_cast ( const Dune::FieldVector< F1, dim > &f1, Dune::FieldVector< F2, dim > &f2 )
{
  for( int d = 0; d < dim; ++d )
    field_cast( f1[ d ], f2[ d ] );
}
template< class F2, class F1 >
inline void field_cast ( const Dune::FieldVector< F1, 1 > &f1, F2 &f2 )
{
  field_cast( f1[ 0 ], f2 );
}
template< class F2, class F1 >
inline void field_cast ( const F1 &f1, Dune::FieldVector< F2, 1 > &f2 )
{
  field_cast( f1, f2[ 0 ] );
}

template< class F2, class F1, int rdim, int cdim >
inline void field_cast ( const Dune::FieldMatrix< F1, rdim, cdim > &f1, Dune::FieldMatrix< F2, rdim, cdim > &f2 )
{
  for( int r = 0; r < rdim; ++r )
    field_cast( f1[ r ], f2[ r ] );
}
template< class F2, class F1 >
inline void field_cast ( const Dune::FieldMatrix<F1,1,1> &f1, Dune::FieldMatrix< F2, 1,1 > &f2 )
{
  field_cast( f1[ 0 ][ 0 ], f2[ 0 ][ 0 ] );
}
template< class F2, class F1 >
inline void field_cast ( const Dune::FieldMatrix< F1, 1,1 > &f1, F2 &f2 )
{
  field_cast( f1[ 0 ][ 0 ], f2 );
}
template< class F2, class F1 >
inline void field_cast ( const F1 &f1, Dune::FieldMatrix< F2, 1,1 > &f2 )
{
  field_cast( f1, f2[ 0 ][ 0 ] );
}
template< class F2, class F1 >
inline void field_cast ( const Dune::FieldVector<F1,1> &f1, Dune::FieldMatrix< F2, 1,1 > &f2 )
{
  field_cast( f1[ 0 ], f2[ 0 ][ 0 ] );
}
template< class F2, class F1 >
inline void field_cast ( const Dune::FieldMatrix<F1,1,1> &f1, Dune::FieldVector< F2, 1 > &f2 )
{
  field_cast( f1[ 0 ][ 0 ], f2[ 0 ] );
}

template< class F2, class F1 >
inline void field_cast ( const Dune::FieldVector< F1, 1 > &f1, Dune::FieldVector<F2, 1> &f2 )
{
  field_cast( f1[ 0 ], f2[ 0 ] );
}


template< class F2,class F1 >
inline F2 field_cast ( const F1 &f1 )
{
  F2 f2;
  field_cast( f1, f2 );
  return f2;
}

template< class F2,class F1,int dim >
inline Dune::FieldVector<F2,dim> field_cast ( const Dune::FieldVector<F1,dim> &f1 )
{
  Dune::FieldVector<F2,dim> f2;
  field_cast( f1, f2 );
  return f2;
}

template< class F2,class F1,int dim1, int dim2>
inline Dune::FieldMatrix<F2,dim1,dim2> field_cast ( const Dune::FieldMatrix<F1,dim1,dim2> &f1 )
{
  Dune::FieldMatrix<F2,dim1,dim2> f2;
  field_cast( f1, f2 );
  return f2;
}

#endif // #ifndef DUNE_FIELD_HH
