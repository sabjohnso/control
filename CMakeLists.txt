#
# ... Build script for control
#

cmake_minimum_required( VERSION 3.7 )

project( CONTROL )
set( CONTROL_MAJOR 0)
set( CONTROL_MINOR 1)
set( CONTROL_UPDATE 0)
set( CONTROL_VERSION control-${CONTROL_MAJOR}.${CONTROL_MINOR} )
set( CONTROL_VERSION_UPDATE ${CONTROL_VERSION}.${CONTROL_UPDATE} )

option( BUILD_CONTROL_TESTING  "Build the control  tests" ON )
option( BUILD_CONTROL_DOCUMENTATION "Build the control documentation" ON )

include_directories( 
  ${CONTROL_SOURCE_DIR}
  ${CONTROL_BINARY_DIR} )

if( NOT CONTROL_INSTALL_INCLUDE_DIR)
  set( CONTROL_INSTALL_INCLUDE_DIR include/control
    CACHE PATH "Path for installation of header files" )
endif( NOT CONTROL_INSTALL_INCLUDE_DIR)

add_subdirectory( control )



#
# ... Testing
#
if( BUILD_CONTROL_TESTING )
  enable_testing()
  add_subdirectory( control_testing )
endif( BUILD_CONTROL_TESTING )



#
# ... Documentation
#
if( BUILD_CONTROL_DOCUMENTATION )

  configure_file( Doxyfile.in Doxyfile )

  if( NOT CONTROL_INSTALL_DOC_DIR)
    set( CONTROL_INSTALL_DOC_DIR share/doc/${CONTROL_VERSION}
      CACHE PATH "Path for installation of documentation files" )
  endif( NOT CONTROL_INSTALL_DOC_DIR)

  if( NOT CONTROL_INTALL_MAN_DIR)
    set( CONTROL_INTALL_MAN_DIR include/control
      CACHE PATH "Path for installation of man files" )
  endif( NOT CONTROL_INTALL_MAN_DIR)

  find_package( Doxygen REQUIRED )

  add_custom_command(
    OUTPUT ${CONTROL_BINARY_DIR}/doxygen.log
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile > doxygen.log
    MAIN_DEPENDENCY Doxyfile
    DEPENDS ${CONTROL_BINARY_DIR}/control
    WORKING_DIRECTORY ${CONTROL_BINARY_DIR} )

  add_custom_target(
    control_documentation ALL
    DEPENDS ${CONTROL_BINARY_DIR}/doxygen.log )

  install( DIRECTORY ${CONTROL_BINARY_DIR}/doc/html DESTINATION ${CONTROL_INSTALL_DOC_DIR} )
  install( DIRECTORY ${CONTROL_BINARY_DIR}/doc/man DESTINATION ${CONTROL_INTALL_MAN_DIR} )
  
endif( BUILD_CONTROL_DOCUMENTATION )

# end of build definition for control
