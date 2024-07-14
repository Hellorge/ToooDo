#include "relativedates.h"

QString RelativeDates::pDate(const QDateTime &dateTime, bool includeMinutes)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    qint64 secondsDiff = currentDateTime.secsTo(dateTime);
    qint64 minutesDiff = secondsDiff / 60;
    qint64 hoursDiff = minutesDiff / 60;
    qint64 daysDiff = hoursDiff / 24;

    if (daysDiff == 0) {
        if (hoursDiff == 0) {
            if (minutesDiff == 0) {
                return "just now";
            } else {
                return QString(includeMinutes ? "%1 minutes ago" : "today").arg(qAbs(minutesDiff));
            }
        } else {
            return QString(includeMinutes ? "%1 hours %2 minutes ago" : "today")
                    .arg(qAbs(hoursDiff))
                    .arg(qAbs(minutesDiff % 60));
        }
    } else if (daysDiff == 1) {
        return "tomorrow";
    } else if (daysDiff == -1) {
        return "yesterday";
    } else if (daysDiff < 0) {
        if (-daysDiff < 7) {
            return QString("%1 days ago").arg(-daysDiff);
        } else if (-daysDiff < 30) {
            return QString("%1 weeks ago").arg(-daysDiff / 7);
        } else if (-daysDiff < 365) {
            return QString("%1 months ago").arg(-daysDiff / 30);
        } else {
            return QString("%1 years ago").arg(-daysDiff / 365);
        }
    } else {
        if (daysDiff < 7) {
            return QString("in %1 days").arg(daysDiff);
        } else if (daysDiff < 30) {
            return QString("in %1 weeks").arg(daysDiff / 7);
        } else if (daysDiff < 365) {
            return QString("in %1 months").arg(daysDiff / 30);
        } else {
            return QString("in %1 years").arg(daysDiff / 365);
        }
    }
}
