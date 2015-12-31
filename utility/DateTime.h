#ifndef TODOS_UTILITY_DATETIME_H
#define TODOS_UTILITY_DATETIME_H

#include <string>
#include <memory>

#include <time.h>

namespace todos_utility {
  class DateTimeConsistencyException
  {
  private:
    std::string m_hint;

  public:
    DateTimeConsistencyException(const std::string& hint);

    std::string GetHint() const;
  };

  class DateTime
  {
  private:
    unsigned int m_second;
    unsigned int m_minute;
    unsigned int m_hour;
    unsigned int m_day;
    unsigned int m_month;
    unsigned int m_year;

  public:
    DateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second);
    DateTime();

    unsigned int GetSecond() const;
    unsigned int GetMinute() const;
    unsigned int GetHour() const;
    unsigned int GetDay() const;
    unsigned int GetMonth() const;
    unsigned int GetYear() const;

    void SetSecond(unsigned int second);
    void SetMinute(unsigned int second);
    void SetHour(unsigned int second);
    void SetDay(unsigned int second);
    void SetMonth(unsigned int second);
    void SetYear(unsigned int second);

    bool operator==(const DateTime& rhs) const;

  private:
    void CheckIfSecondInProperRange();
    void CheckIfMinuteInProperRange();
    void CheckIfHourInProperRange();
    void CheckIfDayInProperRange();
    void CheckIfMonthInProperRange();
    void CheckIfYearInProperRange();

    void CheckIfCalendarDayExists();
  };

  bool DateTimeToTm(const DateTime& datetime, struct tm& timeinfo);

  DateTime StringToDateTime(const std::string& str);
  std::string DateTimeToString(const DateTime& datetime);
}

#endif //TODOS_UTILITY_DATETIME_H