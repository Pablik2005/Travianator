#ifndef TIME_H
#define TIME_H

#include <QtCore>
#include <QMessageBox>

class Time
{
public:
    Time();
    Time(QDate fDate, QTime fTime);
    Time(int fHours, int fMinutes,  int fSeconds);
    Time(QString fTime);

    int day;
    QTime time;


    int hours();
    int minutes();
    int seconds();

    void setHMS(QDate fDate, QTime fTime);
    void setHMS(int fHours, int fMinutes,  int fSeconds);
    void setHMS(QString fTime);
    void setHMS(Time fTime);

    QString toString();

    Time addHours(int fHours);
    Time addMinutes(int fMinutes);
    Time addSeconds(qint64 fSeconds);

    qint64 secondsTo(Time fTarget);

    Time fromHours(int fHours);
    Time fromMinutes(int fMinutes);
    Time fromSeconds(qint64 fSeconds);

    bool operator<(const Time &fTarget);
    bool operator<=(const Time &fTarget);
    bool operator>(const Time &fTarget);
    bool operator>=(const Time &fTarget);
    bool operator==(const Time &fTarget);
    Time operator+(Time fTarget);
    Time operator-(Time fTarget);
    Time* operator&(Time &fTarget);

    int static toHours(Time fTime);
    int static toMinutes(Time fTime);
    qint64 static toSeconds(Time fTime);

    Time static returnTheLongestTime(QList<Time> fTimeList);
    int static returnTheLongestTimeIndex(QList<Time> fTimeList);

    Time static currentTime();
};

QDataStream &operator<<(QDataStream &fStream, Time &fTime);
QDataStream &operator>>(QDataStream &fStream, Time &fTime);

#endif // TIME_H
