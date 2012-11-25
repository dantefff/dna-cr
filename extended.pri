## Extended rules to make the main .pro file easier.
######### Black magic... Don't touch unless you want to have a painful dead
######### Default paths for .h and .cpp are  src/controller and src/model 
######### Default path for .ui is  src/view 

# This allows to use the MYSOURCES variable to add source files, without needing
# to specify its location.
# TODO: use variable to specify root location.
for(file, MYSOURCES) {
  SOURCES += src/$${file}
}

# This allows to use class names to add its source and headers files, without
# needing to duplicate header/source or specify full path.
# TODO: use variables to specify default paths.

for(class, CLASSES) {
  exists(src/controller/$${class}.h) {
    SOURCES += src/controller/$${class}.cpp
    HEADERS += src/controller/$${class}.h
  } else:exists(src/model/$${class}.h) {
    SOURCES += src/model/$${class}.cpp
    HEADERS += src/model/$${class}.h
  } else:exists(src/utils/$${class}.h) {
    SOURCES += src/utils/$${class}.cpp
    HEADERS += src/utils/$${class}.h
  } else:exists(src/utils/controller/$${class}.h) {
    SOURCES += src/utils/controller/$${class}.cpp
    HEADERS += src/utils/controller/$${class}.h
  } else {
    error(Couldn't find file for class $${class})
  }
}

# This allows to add forms without needing to specify the full path.
# TODO: use variable to specify the default path.
for(form, MYFORMS) {
  exists(src/view/$${form}.ui) {
    FORMS += src/view/$${form}.ui
  } else:exists(src/utils/view/$${form}.ui) {
    FORMS += src/utils/view/$${form}.ui
  } else {
    error(Couldn't find file for form $${form})
  }
}
