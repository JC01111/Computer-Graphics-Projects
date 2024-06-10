#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/jaychen/Desktop/CS184/hw0-intro/xcode
  make -f /Users/jaychen/Desktop/CS184/hw0-intro/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/jaychen/Desktop/CS184/hw0-intro/xcode
  make -f /Users/jaychen/Desktop/CS184/hw0-intro/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/jaychen/Desktop/CS184/hw0-intro/xcode
  make -f /Users/jaychen/Desktop/CS184/hw0-intro/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/jaychen/Desktop/CS184/hw0-intro/xcode
  make -f /Users/jaychen/Desktop/CS184/hw0-intro/xcode/CMakeScripts/ReRunCMake.make
fi

