/*
 *	This file is part of PSN Birthday Recover.
 *
 *	Copyright (C) 2013 Maël A
 *
 *	PSN Birthday Recover is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PSN Birthday Recover is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with PSN Birthday Recover.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
 /*
 *	This program uses Qt version 5.1.0
 *
 *	Qt is available under the terms of the GNU Lesser General Public License
 *	version 2.1 as published by the Free Software Foundation.
 *
 *	Copyright(C) 2013 Digia Plc and/or its subsidiary(-ies) and other contributors.
 *
 *	Qt and the Qt logo are trademarks of Digia Plc and/or its subsidiary(-ies)
 *
 *	Qt is developed as an open source project on qt-project.org.
 *
 *	Qt is a Digia product. See qt.digia.com for more information.
 *
 */

#ifndef NETWORKCONNEXIONCONTROLLER_H
#define NETWORKCONNEXIONCONTROLLER_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include "networkconnexion.h"

class NetworkConnexionController : public QObject
{
    Q_OBJECT
public:
    explicit NetworkConnexionController(QWidget *parent = 0);
    ~NetworkConnexionController();
    void setEmail(QString email);
    void setConsoleID(QString consoleID);
    void setStart(int year);
    void initiate();
    
signals:
    void birthdayRecoveredSignal(int day, int month, int year);
    void progressionChangedSignal(bool end);
    void showErrorMessageSignal(QString title, QString errorMessage);
    void starting();
    
public slots:
    void birthdayRecoveredSlot(int day, int month, int year);
    void progressionChangedSlot(bool end);
    void showErrorMessageSlot(QString title, QString errorMessage);

private:
    NetworkConnexion *connexion;
    QThread connexionThread;
    QWidget *parentWidget;
    
};

#endif // NETWORKCONNEXIONCONTROLLER_H
