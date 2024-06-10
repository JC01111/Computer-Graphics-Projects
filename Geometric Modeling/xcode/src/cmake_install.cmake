# Install script for directory: /Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

set(CMAKE_BINARY_DIR "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode")

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1" TYPE EXECUTABLE FILES "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode/Debug/meshedit")
    if(EXISTS "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
      endif()
    endif()
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1" TYPE EXECUTABLE FILES "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode/Release/meshedit")
    if(EXISTS "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
      endif()
    endif()
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1" TYPE EXECUTABLE FILES "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode/MinSizeRel/meshedit")
    if(EXISTS "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
      endif()
    endif()
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1" TYPE EXECUTABLE FILES "/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode/RelWithDebInfo/meshedit")
    if(EXISTS "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/meshedit")
      endif()
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    include("/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode/src/CMakeFiles/meshedit.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    include("/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode/src/CMakeFiles/meshedit.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    include("/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode/src/CMakeFiles/meshedit.dir/install-cxx-module-bmi-MinSizeRel.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    include("/Users/jaychen/Desktop/CS184/hw2-meshedit-sp24-j-c-1/xcode/src/CMakeFiles/meshedit.dir/install-cxx-module-bmi-RelWithDebInfo.cmake" OPTIONAL)
  endif()
endif()

