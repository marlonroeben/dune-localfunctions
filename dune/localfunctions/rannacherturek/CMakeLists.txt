set(rannacherturekdir  ${CMAKE_INSTALL_INCLUDEDIR}/dune/localfunctions/rannacherturek)

set(rannacherturek_HEADERS
  rannacherturek.hh
  rannachertureklocalbasis.hh
  rannachertureklocalcoefficients.hh
  rannachertureklocalinterpolation.hh)

set(SUBDIRS  rannacherturek2d rannacherturek3d)

install(FILES ${rannacherturek_HEADERS} DESTINATION ${rannacherturekdir})
foreach(i ${SUBDIRS})
  if(${i} STREQUAL "test")
    set(opt "EXCLUDE_FROM_ALL")
  endif(${i} STREQUAL "test")
  add_subdirectory(${i} ${opt})
  unset(opt)
endforeach(i ${SUBDIRS})
