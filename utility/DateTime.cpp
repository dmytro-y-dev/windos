#include "DateTime.h"

#include <sstream>
#include <iomanip>

using namespace todos_utility;

DateTimeConsistencyException::DateTimeConsistencyException(const std::string& hint) :
  m_hint(hint)
{
}

std::string DateTimeConsistencyException::GetHint() const
{
  return m_hint;
}

DateTime::DateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second) :
  m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute), m_second(second)
{
  CheckIfSecondInProperRange();
  CheckIfMinuteInProperRange();
  CheckIfHourInProperRange();
  CheckIfDayInProperRange();
  CheckIfMonthInProperRange();
  CheckIfYearInProperRange();
  CheckIfCalendarDayExists();
}

DateTime::DateTime()
{
  std::time_t timestamp = std::time(NULL);
  struct tm *timeinfo = localtime(&timestamp);

  m_second = timeinfo->tm_sec;
  m_minute = timeinfo->tm_min;
  m_hour = timeinfo->tm_hour;
  m_day = timeinfo->tm_mday;
  m_month = timeinfo->tm_mon + 1;
  m_year = timeinfo->tm_year + 1900;
}

unsigned int DateTime::GetSecond() const
{
  return m_second;
}

unsigned int DateTime::GetMinute() const
{
  return m_minute;
}

unsigned int DateTime::GetHour() const
{
  return m_hour;
}

unsigned int DateTime::GetDay() const
{
  return m_day;
}

unsigned int DateTime::GetMonth() const
{
  return m_month;
}

unsigned int DateTime::GetYear() const
{
  return m_year;
}

void DateTime::SetSecond(unsigned int second)
{
  m_second = second;

  CheckIfSecondInProperRange();
}

void DateTime::SetMinute(unsigned int minute)
{
  m_minute = minute;

  CheckIfMinuteInProperRange();
}

void DateTime::SetHour(unsigned int hour)
{
  m_hour = hour;

  CheckIfHourInProperRange();
}

void DateTime::SetDay(unsigned int day)
{
  m_day = day;

  CheckIfDayInProperRange();
  CheckIfCalendarDayExists();
}

void DateTime::SetMonth(unsigned int month)
{
  m_month = month;

  CheckIfMonthInProperRange();
  CheckIfCalendarDayExists();
}

void DateTime::SetYear(unsigned int year)
{
  m_year = year;

  CheckIfYearInProperRange();
  CheckIfCalendarDayExists();
}

bool todos_utility::DateTime::operator==(const DateTime& rhs) const
{
  return
    m_year == rhs.m_year &&
    m_month == rhs.m_month &&
    m_day == rhs.m_day &&
    m_hour == rhs.m_hour &&
    m_minute == rhs.m_minute &&
    m_second == rhs.m_second
  ;
}

void DateTime::CheckIfSecondInProperRange()
{
  if (m_second >= 0 && m_second <= 60) {
    // Value is ok
  } else {
    throw DateTimeConsistencyException("DateTimeConsistencyException: Second must be between 0 and 60!");
  }
}

void DateTime::CheckIfMinuteInProperRange()
{
  if (m_minute >= 0 && m_minute <= 59) {
    // Value is ok
  } else {
    throw DateTimeConsistencyException("DateTimeConsistencyException: Minute must be between 0 and 59!");
  }
}

void DateTime::CheckIfHourInProperRange()
{
  if (m_hour >= 0 && m_hour <= 23) {
    // Value is ok
  } else {
    throw DateTimeConsistencyException("DateTimeConsistencyException: Hour must be between 0 and 23!");
  }
}

void DateTime::CheckIfDayInProperRange()
{
  if (m_day >= 1 && m_day <= 31) {
    // Value is ok
  } else {
    throw DateTimeConsistencyException("DateTimeConsistencyException: Day must be between 1 and 31!");
  }
}

void DateTime::CheckIfMonthInProperRange()
{
  if (m_month >= 1 && m_month <= 12) {
    // Value is ok
  } else {
    throw DateTimeConsistencyException("DateTimeConsistencyException: Month must be between 1 and 12!");
  }
}

void DateTime::CheckIfYearInProperRange()
{
  if (m_year >= 1900) {
    // Value is ok
  } else {
    throw DateTimeConsistencyException("DateTimeConsistencyException: Year must be larger than 1900!");
  }
}

void DateTime::CheckIfCalendarDayExists()
{
  struct tm timeinfo;

  if (DateTimeToTm(*this, timeinfo)) {
    // Value is ok
  } else {
    throw DateTimeConsistencyException("DateTimeConsistencyException: Calendar time cannot be represented!");
  }
}

bool todos_utility::DateTimeToTm(const DateTime & datetime, struct tm & timeinfo)
{
  timeinfo.tm_hour = datetime.GetHour();
  timeinfo.tm_min  = datetime.GetMinute();
  timeinfo.tm_sec  = datetime.GetSecond();
  timeinfo.tm_mday = datetime.GetDay();
  timeinfo.tm_mon  = datetime.GetMonth() - 1;
  timeinfo.tm_year = datetime.GetYear() - 1900;

  timeinfo.tm_isdst = -1;
  timeinfo.tm_wday = -1;
  timeinfo.tm_yday = -1;

  return mktime(&timeinfo) != -1;
}

DateTime todos_utility::StringToDateTime(const std::string &str)
{
  std::istringstream timestring(str);
  struct tm timeinfo;

  timestring >> std::get_time(&timeinfo, "%Y-%m-%d %H:%M:%S");

  return DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
}

std::string todos_utility::DateTimeToString(const DateTime &datetime)
{
  struct tm timeinfo;

  if (!DateTimeToTm(datetime, timeinfo)) {
    return "";
  }

  char dateTimeBuffer[255];
  strftime(dateTimeBuffer, 255, "%Y-%m-%d %H:%M:%S", &timeinfo);

  return std::string(dateTimeBuffer);
}
