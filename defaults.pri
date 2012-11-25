# Default values for Qt projects

# The include path will usually be src related
INCLUDEPATH += src

unix {
  CONFIG += debug
}
# Compile in release only for windows. TODO: read env variable to use release mode.
win32 {
  CONFIG += release
}

# Build and dir folders, depending on system.
unix {
  CONFIG(debug, debug|release) {
    DESTDIR = dist/Debug/GNU-Linux
    OBJECTS_DIR = build/Debug/GNU-Linux
  } else {
    DESTDIR = dist/Release/GNU-Linux
    OBJECTS_DIR = build/Release/GNU-Linux
  }
}
win32 {
  CONFIG(debug, debug|release) {
    DESTDIR = dist/Debug/Windows
    OBJECTS_DIR = build/Debug/Windows
  } else {
    DESTDIR = dist/Release/Windows
    OBJECTS_DIR = dist/Release/Windows
  }
}

# This ones are platform independent, so they're safe there.
MOC_DIR = build
RCC_DIR = build
UI_DIR = build
