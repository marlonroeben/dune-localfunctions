set(monomialdir  ${CMAKE_INSTALL_INCLUDEDIR}/dune/localfunctions/monomial)

set(monomial_HEADERS  monomiallocalbasis.hh monomiallocalcoefficients.hh monomiallocalinterpolation.hh)

# include not needed for CMake
# include $(top_srcdir)/am/global-rules

install(FILES ${monomial_HEADERS} DESTINATION ${monomialdir})
