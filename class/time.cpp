#include "time.h"

Time::Time()
{
}

Time::Time(QDate fDate, QTime fTime)
{
    day = 365 * fDate.year() + fDate.dayOfYear();
    time = fTime;
}

Time::Time(int fHours, int fMinutes, int fSeconds)
{
    if(fHours > 23)
        day = fHours / 24;
    else
        day = 0;

    time.setHMS(fHours%24, fMinutes, fSeconds);
}

Time::Time(QString fTime)
{
    Time();
    QStringList timeStringList = fTime.split(':');

    int tHours = timeStringList.at(0).toInt();
    int tMinutes = timeStringList.at(1).toInt();
    int tSeconds = timeStringList.at(2).toInt();

    if(tHours > 23)
        day = tHours / 24;
    else
        day = 0;

    time.setHMS(tHours%24, tMinutes, tSeconds);
}

int Time::hours()
{
    if(day)
    {
        return day*24 + time.hour();

    }else
    {
        return time.hour();
    }
}

int Time::minutes()
{
    return time.minute();
}

int Time::seconds()
{
    return time.second();
}

void Time::setHMS(QDate fDate, QTime fTime)
{
    day = 365 * fDate.year() + fDate.dayOfYear();
    time = fTime;
}

void Time::setHMS(int fHours, int fMinutes, int fSeconds)
{
    if(fHours > 23)
        day = fHours / 24;
    else
        day=0;

    time.setHMS(fHours%24, fMinutes, fSeconds);
}

void Time::setHMS(QString fTime)
{
    QStringList timeStringList = fTime.split(':');

    int tHours = timeStringList.at(0).toInt();
    int tMinutes = timeStringList.at(1).toInt();
    int tSeconds = timeStringList.at(2).toInt();

    if(tHours > 23)
        day = tHours / 24;
    else
        day=0;

    time.setHMS(tHours%24, tMinutes, tSeconds);
}

void Time::setHMS(Time fTime)
{
    day = fTime.day;
    time = fTime.time;
}

QString Time::toString()
{
    if(day)
    {
        return QString::number(day*24 + time.hour()) + time.toString(":mm:ss");

    }else
        return time.toString("hh:mm:ss");
}

Time Time::addHours(int fHours)
{    
    return fromSeconds( toSeconds(*this) + fHours*3600 );
}

Time Time::addMinutes(int fMinutes)
{
    return fromSeconds( toSeconds(*this) + fMinutes*60 );
}

Time Time::addSeconds(qint64 fSeconds)
{    
    return fromSeconds( toSeconds(*this) + fSeconds );
}

qint64 Time::secondsTo(Time fTarget)
{
    return toSeconds(fTarget) - toSeconds(*this);
}

int Time::toHours(Time fTime)
{
    return fTime.hours();
}

int Time::toMinutes(Time fTime)
{
    return fTime.hours()*60 + fTime.minutes();
}

qint64 Time::toSeconds(Time fTime)
{
    return (qint64)fTime.hours()*3600 + fTime.minutes()*60 + fTime.seconds();
}

Time Time::returnTheLongestTime(QList<Time> fTimeList)
{
    Time returnValue(0,0,0);
    foreach(Time i, fTimeList)
        if(returnValue < i)
            returnValue.setHMS(i);

    return returnValue;
}

int Time::returnTheLongestTimeIndex(QList<Time> fTimeList)
{
    Time tValue(0,0,0);
    int returnIndex = -1;
    for(int i=0; i < fTimeList.count(); i++)
        if(tValue < fTimeList.at(i))
        {
            tValue.setHMS( fTimeList.at(i) );
            returnIndex = i;
        }

    return returnIndex;
}


Time Time::currentTime()
{
    return Time(QDate::currentDate(), QTime::currentTime());
}

Time Time::fromHours(int fHours)
{
    Time returnValue(fHours,0,0);
    return returnValue;
}

Time Time::fromMinutes(int fMinutes)
{
    int tHours = fMinutes / 60;
    int tMinutes = fMinutes % 60;
    Time returnValue(tHours,tMinutes,0);
    return returnValue;
}

Time Time::fromSeconds(qint64 fSeconds)
{
    int tHours = fSeconds / 3600;
    int tMinutes = (fSeconds % 3600) / 60;
    int tSeconds = (fSeconds % 3600) % 60;
    Time returnValue(tHours,tMinutes,tSeconds);
    return returnValue;
}

bool Time::operator <(const Time &fTarget)
{
    if(toSeconds(*this) < toSeconds(fTarget))
        return true;
    else
        return false;
}


bool Time::operator <=(const Time &fTarget)
{
    if(toSeconds(*this) <= toSeconds(fTarget))
        return true;
    else
        return false;

}

bool Time::operator >(const Time &fTarget)
{
    if(toSeconds(*this) > toSeconds(fTarget))
        return true;
    else
        return false;
}

bool Time::operator >=(const Time &fTarget)
{
    if(toSeconds(*this) >= toSeconds(fTarget))
        return true;
    else
        return false;
}

bool Time::operator ==(const Time &fTarget)
{
    if(toSeconds(*this) == toSeconds(fTarget))
        return true;
    else
        return false;
}

Time Time::operator +(Time fTarget)
{
    return fromSeconds( toSeconds(*this) + toSeconds(fTarget) );
}

Time Time::operator -(Time fTarget)
{
    return fromSeconds( toSeconds(*this) - toSeconds(fTarget) );
}

Time *Time::operator &(Time &fTarget)
{
    return &fTarget;
}

Time TimeO(QDate fDate, QTime fTime)
{
    Time returnValue(fDate, fTime);
    return returnValue;
}

Time TimeO(int fHours, int fMinutes,  int fSeconds)
{
    Time returnValue(fHours, fMinutes, fSeconds);
    return returnValue;
}

Time TimeO(QString fTime)
{
    Time returnValue(fTime);
    return returnValue;
}

QDataStream &operator <<(QDataStream &fStream, Time &fTime)
{
    fStream << fTime.day << fTime.time;
    return fStream;
}

QDataStream &operator >>(QDataStream &fStream, Time &fTime)
{
    fStream >> fTime.day >> fTime.time;
    return fStream;
}
