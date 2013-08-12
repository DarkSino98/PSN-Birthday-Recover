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

#ifndef NETWORKCONNEXION_H
#define NETWORKCONNEXION_H

#include <QString>
#include <QMessageBox>
#include <QWidget>
#include <QLineEdit>
#include <QtNetwork>
#include <QtCore>
#include <QtGui>

class NetworkConnexion : public QObject
{
Q_OBJECT

public slots:
    void replyNetworkError(QNetworkReply::NetworkError code);
    void managerSslError(QNetworkReply * reply, const QList<QSslError> & errors);
    void requestFinished(QNetworkReply * reply);

signals:
    void birthdayRecovered(int day, int month, int year);
    void progressionChanged(int progression, int day, int month, int year);

public:
    NetworkConnexion(QWidget *parent);
    ~NetworkConnexion();
    void initiate();
    void setEmail(QString email);
    void setConsoleID(QString consoleID);
    void setStart(int day, int month, int year);

protected:
    void recover();

private:
    QWidget *parentWidget;

    QString consoleID;
    QString email;

    QNetworkRequest *httpRequest;
    QNetworkReply *httpReply;
    QNetworkAccessManager *httpManager;

    QSslConfiguration *sslConfig;

    bool initialisation;
    int day;
    int month;
    int year;
    int progression;
};

#endif // NETWORKCONNEXION_H
