/* This file is part of the aCademias application.
Copyright Aplicaciones Informáticas Corporativas
y Empresariales SL (aCore) 2012. All rights reserved.*/

#include "MessageHandler.h"
#include <cstdio>
#include <cstdlib>
#include <QApplication>
#include <QDesktopServices>
#include <QDir>

FILE* output = 0;

void myMessageOutput(QtMsgType type, const char *msg)
{
  if (output==0){
    #ifdef Q_OS_WIN32
    output = fopen(
      (QDesktopServices::storageLocation(QDesktopServices::TempLocation) + 
      QDir::separator() + qAppName() + ".log").toAscii().data(),
      "a");
    #else 
    output = stderr;
    #endif
  }
  
  QString str = QString(msg);
  switch (type) {
  case QtDebugMsg:
    if (str.contains("create image from")) break;
    fprintf(output, "Debug: %s\n", msg);
    break;
  case QtWarningMsg:
    if (str.contains("linearGradient")) break;
    if (str.contains("radialGradient")) break;
    if (str.contains("link path")) break;
    if (str.contains("sand_bitmap")) break;
    fprintf(output, "----Warning: %s\n", msg);
    break;
  case QtCriticalMsg:
    fprintf(output, "------Critical: %s\n", msg);
    break;
  case QtFatalMsg:
    fprintf(output, "--------Fatal: %s\n", msg);
    abort();
  }
}
