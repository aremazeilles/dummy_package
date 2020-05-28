cmake_minimum_required(VERSION 2.8.3)
project(dummy_package)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  std_srvs
  actionlib
  actionlib_msgs
  dynamic_reconfigure
  tf
)

# protected region additional user defined REQUIREMENTS begin #
# protected region additional user defined REQUIREMENTS end #

if (dummy_package_dyn_rec_files)
  list(APPEND dummy_package_dyn_rec_files cfg/dummy_node.cfg)
  # message("Append of cfg/dummy_node.cfg")
else ()
  set(dummy_package_dyn_rec_files cfg/dummy_node.cfg)
  # message("Setting with cfg/dummy_node.cfg")
endif ()

# message("Test: ${dummy_package_dyn_rec_files}")
if (dummy_package_dyn_rec_files)
  generate_dynamic_reconfigure_options(${dummy_package_dyn_rec_files})
endif ()

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS
    common/src
  CATKIN_DEPENDS
    roscpp
    roscpp
    std_msgs
    std_srvs
    actionlib
    actionlib_msgs
    dynamic_reconfigure
    tf
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(common/src)
include_directories(${catkin_INCLUDE_DIRS})

## Declare cpp executable
add_executable(dummy_node ros/src/dummy_node_ros.cpp)
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
add_dependencies(dummy_node ${PROJECT_NAME}_gencfg)
add_dependencies(dummy_node ${${PROJECT_NAME}_EXPORTED_TARGETS})
## Specify libraries to link a library or executable target against
target_link_libraries(dummy_node ${catkin_LIBRARIES}
)
# protected region additional user defined BUILD STATEMENTS begin #
# protected region additional user defined BUILD STATEMENTS end #

##########
## Test ##
##########

if (CATKIN_ENABLE_TESTING)
  find_package(rostest REQUIRED)
  add_rostest(test/test_dummy_node_hz_loop.test)
  add_rostest(test/test_dummy_node_dyn_param.test)
endif()

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS dummy_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# protected region user Cmake macros begin #
# protected region user Cmake macros end #
