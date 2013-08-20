/*
 *	This file is part of PSN Birthday Recover.
 *
 *	Copyright(C) 2013 Maël A
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include "aboutwindow.h"
#include "networkconnexion.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QWidget
{
Q_OBJECT

public slots:
    void on_buttonAbout_clicked();
    void on_buttonStart_clicked();
    void on_buttonStop_clicked();
    void birthdayRecovered(int day, int month, int year);
    void progressionChanged(int progression, int day, int month, int year);
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void setEditMail(QString mail);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    AboutWindow aboutw;
    NetworkConnexion *connexion;

};

#endif // MAINWINDOW_H
