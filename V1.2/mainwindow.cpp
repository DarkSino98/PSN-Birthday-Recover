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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    int i =0;
    for(i=0; i<controllerList.size(); i++)
    {
        NetworkConnexionController *connexionController = controllerList.at(i);
        delete connexionController;
    }
    controllerList.clear();
}

void MainWindow::on_buttonAbout_clicked()
{
    aboutw.show();
}

void MainWindow::on_buttonStart_clicked()
{
    ui->buttonStart->setEnabled(false);
    ui->threadNumber->setEnabled(false);
    ui->progressBar->setValue(0);

    if(ui->groupProxy->isChecked())
    {
        QNetworkProxy proxy;

        if(ui->comboType->currentText() == "Proxy HTTP")
        {
            proxy.setType(QNetworkProxy::HttpProxy);
        }
        else if(ui->comboType->currentText() == "Proxy SOCKS 5")
        {
            proxy.setType(QNetworkProxy::Socks5Proxy);
        }
        else if(ui->comboType->currentText() == "Proxy-Cache HTTP")
        {
            proxy.setType(QNetworkProxy::HttpCachingProxy);
        }

        proxy.setHostName(ui->lineEditAddress->text());
        proxy.setPort(ui->portNumber->value());

        if(ui->groupProxyUser->isChecked())
        {
            proxy.setUser(ui->lineEditUser->text());
            proxy.setPassword(ui->lineEditPass->text());
        }

        QNetworkProxy::setApplicationProxy(proxy);
    }

    int threadNumber = ui->threadNumber->value();
    int i = 0;
    int dayPerThread = 41245/threadNumber;
    int pas = dayPerThread/365;
    for(i=0; i<threadNumber; i++)
    {
        NetworkConnexionController *connexionController = new NetworkConnexionController(this);
        connexionController->setEmail(ui->lineEditMail->text());
        connexionController->setConsoleID(ui->lineEditID->text());
        connexionController->setStart(1900+(pas*i));
        QObject::connect(connexionController, SIGNAL(showErrorMessageSignal(QString,QString)), this, SLOT(showErrorMessage(QString,QString)));
        QObject::connect(connexionController, SIGNAL(progressionChangedSignal(bool)), this, SLOT(progressionChanged(bool)));
        QObject::connect(connexionController, SIGNAL(birthdayRecoveredSignal(int,int,int)), this, SLOT(birthdayRecovered(int,int,int)));
        controllerList.append(connexionController);
        connexionController->initiate();
    }

    ui->buttonStop->setEnabled(true);
}

void MainWindow::on_buttonStop_clicked()
{
    ui->buttonStop->setEnabled(false);

    int i = 0;
    for(i=0; i<controllerList.size(); i++)
    {
        NetworkConnexionController *connexionController = controllerList.at(i);
        delete connexionController;
    }
    controllerList.clear();

    ui->threadNumber->setEnabled(true);
    ui->buttonStart->setEnabled(true);
}

void MainWindow::birthdayRecovered(int day, int month, int year)
{
    ui->buttonStop->setEnabled(false);

    int i = 0;
    for(i=0; i<controllerList.size(); i++)
    {
        NetworkConnexionController *connexionController = controllerList.at(i);
        delete connexionController;
    }
    controllerList.clear();

    QString stringDay;
    QString stringMonth;
    QString stringYear;
    stringDay.setNum(day);
    stringMonth.setNum(month);
    stringYear.setNum(year);
    QMessageBox::information(this, "PSN Birthday Recovered", QMessageBox::tr("La date de naissance de votre compte PSN est ") + stringDay + "/" + stringMonth + "/" + stringYear + QMessageBox::tr(" (jour/mois/année) !"));

    ui->threadNumber->setEnabled(true);
    ui->buttonStart->setEnabled(true);

}

void MainWindow::progressionChanged(bool end)
{
    if(end)
    {
        ui->progressBar->setValue(41245);
    }
    else
    {
        int progression = ui->progressBar->value();
        progression += 1;
        ui->progressBar->setValue(progression);
    }
}

void MainWindow::showErrorMessage(QString title, QString text)
{
    QMessageBox::critical(this, title, text);
}
