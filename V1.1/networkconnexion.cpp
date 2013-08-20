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

#include "networkconnexion.h"
#include "mainwindow.h"

NetworkConnexion::NetworkConnexion(QWidget *parent)
{
    parentWidget = parent;

    day = 1;
    month = 1;
    year = 1900;
    initialisation = true;

    httpManager = new QNetworkAccessManager(this);
    httpRequest = new QNetworkRequest();

    sslConfig = new QSslConfiguration(QSslConfiguration::defaultConfiguration());
    sslConfig->setPeerVerifyDepth(0);
    sslConfig->setProtocol(QSsl::SslV3);
    sslConfig->setCaCertificates(QSslCertificate::fromPath("ca.crt"));

    QObject::connect(httpManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(managerSslError(QNetworkReply*,QList<QSslError>)));
    QObject::connect(httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
}

NetworkConnexion::~NetworkConnexion()
{
    delete httpManager;
    delete httpRequest;
    delete sslConfig;
}

void NetworkConnexion::managerSslError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    reply->deleteLater();
    QString errorMessage;
    QString nbr;
    int i=0;
    for(i=0; i<errors.size(); i++)
    {
        nbr.setNum(i+1);
        errorMessage += "Erreur " + nbr + " : " + errors.at(i).errorString() + "\n";
    }
    emit showErrorMessage("Erreur SSL", errorMessage);
}

void NetworkConnexion::replyNetworkError(QNetworkReply::NetworkError code)
{
    emit showErrorMessage("Erreur réseau", "Erreur : " + code);
}

void NetworkConnexion::requestFinished(QNetworkReply *reply)
{
    if(initialisation)
    {
        reply->deleteLater();
        initialisation = false;
        recover();
    }
    else
    {
        QTextStream streamReply(reply);
        QString stringReply;
        while (!streamReply.atEnd())
        {
                QString line = streamReply.readLine();
                stringReply += line;
        }

        if(!(stringReply.left(2)=="=O"))
        {
            emit progressionChanged(true);
            emit birthdayRecovered(day, month, year);
        }
        else
        {
            emit progressionChanged(false);
            day +=1;
            if(day==32)
            {
                day = 1;
                month +=1;
                if(month==13)
                {
                    month = 1;
                    year +=1;
                }
            }
            recover();
        }
    }
}

void NetworkConnexion::initiate()
{
    initialisation = true;

    httpRequest->setAttribute(QNetworkRequest::CacheLoadControlAttribute, QVariant(QNetworkRequest::AlwaysNetwork));
    httpRequest->setAttribute(QNetworkRequest::CacheSaveControlAttribute, QVariant(false));
    httpRequest->setAttribute(QNetworkRequest::AuthenticationReuseAttribute, QVariant(QNetworkRequest::Manual));
    httpRequest->setSslConfiguration(*sslConfig);

    httpRequest->setUrl(QUrl("https://native.np.ac.playstation.net/native/reg/getCountries.action"));

    httpRequest->setRawHeader("User-Agent", "commerce2/1.0 (PSP (PlayStation Portable); 4.00)");
    httpRequest->setRawHeader("Accept","*/*;q=0.01");
    httpRequest->setRawHeader("Accept-Encoding", " ");
    httpRequest->setRawHeader("Accept-Charset", "iso-8859-1;q=0.01");
    httpRequest->setRawHeader("Host", "native.np.ac.playstation.net");
    httpRequest->setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    httpRequest->setRawHeader("Authorization", "Basic cjI0NjpHUG9FZmJkYQ==");
    httpRequest->setRawHeader("X-MediaInformation", "PSP/480x272");
    httpRequest->setRawHeader("Accept-Language", "ja, en, fr, es, de, it, nl, pt, ru, ko, zh, ch");
    httpRequest->setRawHeader("Connection", "Keep-Alive");
    httpRequest->setRawHeader("Content-Length", "10");

    httpReply = httpManager->post(*httpRequest, "version=12");
    QObject::connect(httpReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(replyNetworkError(QNetworkReply::NetworkError)));
}

void NetworkConnexion::recover()
{
    QString postAttribute;
    QString stringDay;
    QString stringMonth;
    QString stringYear;
    stringDay.setNum(day);
    stringMonth.setNum(month);
    stringYear.setNum(year);
    postAttribute = "version=12&account.loginName=" + email + "&account.yob=" + stringYear + "&account.mob=" + stringMonth + "&account.dob=" + stringDay + "&consoleId=" + consoleID;
    QByteArray byteAttribute = postAttribute.toLatin1();

    QString sizeAttribute;
    sizeAttribute.setNum(postAttribute.size());
    QByteArray byteSize = sizeAttribute.toLatin1();

    httpRequest->setUrl(QUrl("https://native.np.ac.playstation.net/native/cam/verifyDob.action"));
    httpRequest->setRawHeader("Content-Length", byteSize);

    httpReply = httpManager->post(*httpRequest, byteAttribute);
    QObject::connect(httpReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(replyNetworkError(QNetworkReply::NetworkError)));
}

void NetworkConnexion::setEmail(QString email)
{
    NetworkConnexion::email = email;
}

void NetworkConnexion::setConsoleID(QString consoleID)
{
    NetworkConnexion::consoleID = consoleID;
}

void NetworkConnexion::setStart(int year)
{
    NetworkConnexion::year = year;
}

