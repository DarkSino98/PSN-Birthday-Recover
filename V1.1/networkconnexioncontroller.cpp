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
 
#include "networkconnexioncontroller.h"

NetworkConnexionController::NetworkConnexionController(QWidget *parent)
{
    parentWidget = parent;
    connexion = new NetworkConnexion(parent);
    connexion->moveToThread(&connexionThread);
    QObject::connect(&connexionThread, SIGNAL(finished()), connexion, SLOT(deleteLater()));
    QObject::connect(connexion, SIGNAL(progressionChanged(bool)), this, SLOT(progressionChangedSlot(bool)));
    QObject::connect(connexion, SIGNAL(birthdayRecovered(int,int,int)), this, SLOT(birthdayRecoveredSlot(int,int,int)));
    QObject::connect(connexion, SIGNAL(showErrorMessage(QString,QString)), this, SLOT(showErrorMessageSlot(QString,QString)));
    QObject::connect(this, SIGNAL(starting()), connexion, SLOT(initiate()));
    connexionThread.start();
}

NetworkConnexionController::~NetworkConnexionController()
{
    connexionThread.quit();
    connexionThread.wait();
}

void NetworkConnexionController::birthdayRecoveredSlot(int day, int month, int year)
{
    emit birthdayRecoveredSignal(day, month, year);
}

void NetworkConnexionController::progressionChangedSlot(bool end)
{
    emit progressionChangedSignal(end);
}

void NetworkConnexionController::showErrorMessageSlot(QString title, QString errorMessage)
{
    emit showErrorMessageSignal(title, errorMessage);
}

void NetworkConnexionController::setEmail(QString email)
{
    connexion->setEmail(email);
}

void NetworkConnexionController::setConsoleID(QString consoleID)
{
    connexion->setConsoleID(consoleID);
}

void NetworkConnexionController::setStart(int year)
{
    connexion->setStart(year);
}

void NetworkConnexionController::initiate()
{
    emit starting();
}
