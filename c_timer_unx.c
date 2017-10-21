// 时间戳转换
#include <stdio.h>

struct tm
{
    int tm_sec;  /*秒，正常范围0-59， 但允许至61*/
    int tm_min;  /*分钟，0-59*/
    int tm_hour; /*小时， 0-23*/
    int tm_mday; /*日，即一个月中的第几天，1-31*/
    int tm_mon;  /*月， 从一月算起，0-11*/  // 1+p->tm_mon;
    int tm_year;  /*年， 从1900至今已经多少年*/   // 1900＋ p->tm_year;
    int tm_wday; /*星期，一周中的第几天， 从星期日算起，0-6*/
    int tm_yday; /*从今年1月1日到目前的天数，范围0-365*/
    int tm_isdst; /*日光节约时间的旗标*/
};

#define SECSPERMIN 60L
#define MINSPERHOUR 60L
#define HOURSPERDAY 24L
#define SECSPERHOUR (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY (SECSPERHOUR * HOURSPERDAY)
#define DAYSPERWEEK 7
#define MONSPERYEAR 12

#define YEAR_BASE 1900
#define EPOCH_YEAR 1970
#define EPOCH_WDAY 4
#define EPOCH_YEARS_SINCE_LEAP 2
#define EPOCH_YEARS_SINCE_CENTURY 70
#define EPOCH_YEARS_SINCE_LEAP_CENTURY 370

#define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)

static const int mon_lengths[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

static const int year_lengths[2] = {
    365,
    366};

struct tm res_buf;

typedef int time_t;
time_t system_timestam = 0;
struct tm *
my_sntp_mktm_r(const time_t *tim_p, struct tm *res, int is_gmtime)
{
  long days, rem;
  time_t lcltime;
  int i;
  int y;
  int yleap;
  const int *ip;

  /* base decision about std/dst time on current time */
  lcltime = *tim_p;

  days = ((long)lcltime) / SECSPERDAY;
  rem = ((long)lcltime) % SECSPERDAY;
  while (rem < 0)
  {
    rem += SECSPERDAY;
    --days;
  }
  while (rem >= SECSPERDAY)
  {
    rem -= SECSPERDAY;
    ++days;
  }

  /* compute hour, min, and sec */
  res->tm_hour = (int)(rem / SECSPERHOUR);
  rem %= SECSPERHOUR;
  res->tm_min = (int)(rem / SECSPERMIN);
  res->tm_sec = (int)(rem % SECSPERMIN);

  /* compute day of week */
  if ((res->tm_wday = ((EPOCH_WDAY + days) % DAYSPERWEEK)) < 0)
    res->tm_wday += DAYSPERWEEK;

  /* compute year & day of year */
  y = EPOCH_YEAR;
  if (days >= 0)
  {
    for (;;)
    {
      yleap = isleap(y);
      if (days < year_lengths[yleap])
        break;
      y++;
      days -= year_lengths[yleap];
    }
  }
  else
  {
    do
    {
      --y;
      yleap = isleap(y);
      days += year_lengths[yleap];
    } while (days < 0);
  }

  res->tm_year = y - YEAR_BASE;
  res->tm_yday = days;
  ip = mon_lengths[yleap];
  for (res->tm_mon = 0; days >= ip[res->tm_mon]; ++res->tm_mon)
    days -= ip[res->tm_mon];
  res->tm_mday = days + 1;

  if (!is_gmtime)
  {
    int offset;
    int hours, mins, secs;

    //      TZ_LOCK;
    //      if (_daylight)
    //	{
    //	  if (y == __tzyear || __tzcalc_limits (y))
    //	    res->tm_isdst = (__tznorth
    //			     ? (*tim_p >= __tzrule[0].change && *tim_p < __tzrule[1].change)
    //			     : (*tim_p >= __tzrule[0].change || *tim_p < __tzrule[1].change));
    //	  else
    //	    res->tm_isdst = -1;
    //	}
    //      else
    res->tm_isdst = 0;

    // 时间偏移 - 8 * 60 * 60 东八区 -去

    offset = -8 * 60 * 60;
    hours = offset / SECSPERHOUR;
    offset = offset % SECSPERHOUR;

    mins = offset / SECSPERMIN;
    secs = offset % SECSPERMIN;

    res->tm_sec -= secs;
    res->tm_min -= mins;
    res->tm_hour -= hours;

    if (res->tm_sec >= SECSPERMIN)
    {
      res->tm_min += 1;
      res->tm_sec -= SECSPERMIN;
    }
    else if (res->tm_sec < 0)
    {
      res->tm_min -= 1;
      res->tm_sec += SECSPERMIN;
    }
    if (res->tm_min >= MINSPERHOUR)
    {
      res->tm_hour += 1;
      res->tm_min -= MINSPERHOUR;
    }
    else if (res->tm_min < 0)
    {
      res->tm_hour -= 1;
      res->tm_min += MINSPERHOUR;
    }
    if (res->tm_hour >= HOURSPERDAY)
    {
      ++res->tm_yday;
      ++res->tm_wday;
      if (res->tm_wday > 6)
        res->tm_wday = 0;
      ++res->tm_mday;
      res->tm_hour -= HOURSPERDAY;
      if (res->tm_mday > ip[res->tm_mon])
      {
        res->tm_mday -= ip[res->tm_mon];
        res->tm_mon += 1;
        if (res->tm_mon == 12)
        {
          res->tm_mon = 0;
          res->tm_year += 1;
          res->tm_yday = 0;
        }
      }
    }
    else if (res->tm_hour < 0)
    {
      res->tm_yday -= 1;
      res->tm_wday -= 1;
      if (res->tm_wday < 0)
        res->tm_wday = 6;
      res->tm_mday -= 1;
      res->tm_hour += 24;
      if (res->tm_mday == 0)
      {
        res->tm_mon -= 1;
        if (res->tm_mon < 0)
        {
          res->tm_mon = 11;
          res->tm_year -= 1;
          res->tm_yday = 365 + isleap(res->tm_year);
        }
        res->tm_mday = ip[res->tm_mon];
      }
    }
  }
  else
    res->tm_isdst = 0;

  printf("res %d-%d-%d %d:%d:%d\r\n",1900 + res->tm_year, 1+ res->tm_mon, res->tm_mday, res->tm_hour,res->tm_min,res->tm_sec);
  return (res);
}
int main(int argc, char const *argv[])
{
    time_t t = 1508577258;
	my_sntp_mktm_r(&t, &res_buf, 0);
	return 0;
}
