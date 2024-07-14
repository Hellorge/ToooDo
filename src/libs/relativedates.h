#ifndef RELATIVEDATES_H
#define RELATIVEDATES_H

#include <QString>
#include <QDateTime>

class RelativeDates
{
public:
    static QString pDate(const QDateTime &dateTime, bool includeMinutes = false);
};

#endif // RELATIVEDATES_H
