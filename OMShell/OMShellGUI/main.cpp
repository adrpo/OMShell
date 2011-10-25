/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2010, Link�pings University,
 * Department of Computer and Information Science,
 * SE-58183 Link�ping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF THIS OSMC PUBLIC
 * LICENSE (OSMC-PL). ANY USE, REPRODUCTION OR DISTRIBUTION OF
 * THIS PROGRAM CONSTITUTES RECIPIENT'S ACCEPTANCE OF THE OSMC
 * PUBLIC LICENSE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from Link�pings University, either from the above address,
 * from the URL: http://www.ida.liu.se/projects/OpenModelica
 * and in the OpenModelica distribution.
 *
 * This program is distributed  WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS
 * OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 * For more information about the Qt-library visit TrollTech's webpage 
 * regarding the Qt licence: http://www.trolltech.com/products/qt/licensing.html
 */


/*!
 * \file otherdlg.h
 * \author Anders Fernstr�m
 */

#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>

#include "oms.h"
#include "omcinteractiveenvironment.h"
#include <stdio.h>

#define CONSUME_CHAR(value,res,i) \
    if (value.at(i) == '\\') { \
    i++; \
    switch (value[i].toAscii()) { \
    case '\'': res.append('\''); break; \
    case '"':  res.append('\"'); break; \
    case '?':  res.append('\?'); break; \
    case '\\': res.append('\\'); break; \
    case 'a':  res.append('\a'); break; \
    case 'b':  res.append('\b'); break; \
    case 'f':  res.append('\f'); break; \
    case 'n':  res.append('\n'); break; \
    case 'r':  res.append('\r'); break; \
    case 't':  res.append('\t'); break; \
    case 'v':  res.append('\v'); break; \
    } \
    } else { \
    res.append(value[i]); \
    }

QString unparse(QString value)
{
    QString res;
    value = value.trimmed();
    if (value.length() > 1 && value.at(0) == '\"' && value.at(value.length() - 1) == '\"') {
        value = value.mid(1, (value.length() - 2));
        for (int i=0; i < value.length(); i++) {
            CONSUME_CHAR(value,res,i);
        }
        return res;
    } else {
        return "";
    }
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  OMS::startServer();
  
  IAEX::OmcInteractiveEnvironment env;
  env.evalExpression("getInstallationDirectoryPath()");
  QString dir = unparse(env.getResult()) + "/share/omshell/nls";
  QString locale = QString("OMShell_") + QLocale::system().name();

  QTranslator translator;
  translator.load(locale, dir);
  app.installTranslator(&translator);

  OMS oms;
  oms.show();

  return app.exec();
}