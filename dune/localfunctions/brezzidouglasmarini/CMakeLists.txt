set(brezzidouglasmarinidir  ${CMAKE_INSTALL_INCLUDEDIR}/dune/localfunctions/brezzidouglasmarini)

set(brezzidouglasmarini_HEADERS
  brezzidouglasmarini1cube2d.hh
  brezzidouglasmarini1cube3d.hh
  brezzidouglasmarini2cube2d.hh
  brezzidouglasmarini1simplex2d.hh
  brezzidouglasmarini2simplex2d.hh)

set(SUBDIRS
  brezzidouglasmarini1cube2d
  brezzidouglasmarini1cube3d
  brezzidouglasmarini2cube2d
  brezzidouglasmarini1simplex2d
  brezzidouglasmarini2simplex2d)

install(FILES ${brezzidouglasmarini_HEADERS} DESTINATION ${brezzidouglasmarinidir})
foreach(i ${SUBDIRS})
  if(${i} STREQUAL "test")
    set(opt "EXCLUDE_FROM_ALL")
  endif(${i} STREQUAL "test")
  add_subdirectory(${i} ${opt})
  unset(opt)
endforeach(i ${SUBDIRS})
