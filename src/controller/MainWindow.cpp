/* Copyright (c) 2012 Iago Fernández Meilán
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the name of copyright holders nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.*/

#include "MainWindow.h"

#include <QDebug>
#include <QDesktopServices>
#include <QFile>
#include <QDir>
#include <QSettings>

MainWindow::MainWindow ( QWidget* parent, Qt::WindowFlags flags ) : 
    QMainWindow ( parent, flags )
{
  ui.setupUi(this);
  ui.pteOriginal->installEventFilter(this);
  connect(ui.pteOriginal,SIGNAL(textChanged()),SLOT(originalChanged()));
  connect(ui.pbDeleteOrig,SIGNAL(clicked(bool)),ui.pteOriginal,SLOT(clear()));
  connect(ui.pbUndo,SIGNAL(clicked(bool)),SLOT(undoOrig()));
  connect(ui.pbRedo,SIGNAL(clicked(bool)),SLOT(redoOrig()));
}

MainWindow::~MainWindow()
{
  storeGeometry();
}

void MainWindow::initGeometry()
{
  QSettings s;
  s.beginGroup("geometry");
  if (!s.value(objectName()).isValid())
    return;
  if(!restoreGeometry(s.value(objectName()).toByteArray()))
    qWarning() << "Couldn't restore" << objectName() << "geometry!";
}

void MainWindow::storeGeometry()
{
  QSettings s;
  s.beginGroup("geometry");
  s.setValue(objectName(), saveGeometry());
}

void MainWindow::originalChanged()
{
  QString original = ui.pteOriginal->toPlainText();
  QStringList originalLines = original.split('\n');
  QString result;
  foreach(QString linea,originalLines){
    if (linea.startsWith('>')){
      result.append(linea+"_RC");
    }
    else{
      for (int i = linea.size()-1;i>=0;i--){
	result.append(complementary(linea.at(i)));
      }
    }
    result.append('\n');
  }
  ui.pteResultado->setPlainText(result);
}

QChar MainWindow::complementary(QChar actg)
{
  if (actg == 'A' || actg =='a'){
    return 'T';
  }
  if (actg == 'C' || actg =='c'){
    return 'G';
  }
  if (actg == 'T' || actg =='t'){
    return 'A';
  }
  if (actg == 'G' || actg =='g'){
    return 'C';
  }
  return 'X';
}

void MainWindow::redoOrig()
{
  ui.pteOriginal->redo();
}

void MainWindow::undoOrig()
{
  ui.pteOriginal->undo();
}
