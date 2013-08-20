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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkconnexion.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connexion = new NetworkConnexion(this);

    QObject::connect(connexion, SIGNAL(birthdayRecovered(int,int,int)), this, SLOT(birthdayRecovered(int,int,int)));
    QObject::connect(connexion, SIGNAL(progressionChanged(int,int,int,int)), this, SLOT(progressionChanged(int,int,int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete connexion;
}

void MainWindow::on_buttonAbout_clicked()
{
    aboutw.show();
}

void MainWindow::on_buttonStart_clicked()
{
    connexion->setEmail(ui->lineEditMail->text());
    connexion->setConsoleID(ui->lineEditID->text());
    connexion->initiate();
}

void MainWindow::on_buttonStop_clicked()
{

}

void MainWindow::birthdayRecovered(int day, int month, int year)
{
    QString stringDay;
    QString stringMonth;
    QString stringYear;
    stringDay.setNum(day);
    stringMonth.setNum(month);
    stringYear.setNum(year);
    QMessageBox::information(this, "PSN Birthday Recovered", "La date de naissance de votre compte PSN est " + stringDay + "/" + stringMonth + "/" + stringYear + " !");
}

void MainWindow::progressionChanged(int progression, int day, int month, int year)
{
    ui->progressBar->setValue(progression);
    ui->dateEdit->setDate(QDate(year, month, day));
}

void MainWindow::setEditMail(QString mail)
{
    ui->lineEditMail->setText(mail);
}
