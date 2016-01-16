#include <gtest/gtest.h>

#include <string>

#include <utility/DateTime.h>

using std::string;
using todos_utility::DateTime;
using todos_utility::DateTimeConsistencyException;

class TestUtilityDateTime : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(TestUtilityDateTime, DateTimeConstructorsBad)
{
  int wrongDateTimes[][6] = {
    {2015, 12, 30, 12, 15, 70},
    {2015, 12, 30, 12, 65, 0},
    {2015, 12, 30, 25, 0, 0},
    {2015, 12, 32, 0, 0, 0},
    {2015, 14, 0, 0, 0, 0},
    {80, 0, 0, 0, 0, 0},
    {2015, 2, 29, 0, 0, 0}
  };

  for (int i = 0, iend = sizeof(wrongDateTimes) / sizeof(int[6]); i != iend; ++i) {
    bool constructorFailed = false;

    try {
      DateTime datetime2(2015, 12, 30, 12, 15, 70);
    } catch (DateTimeConsistencyException& exception) {
      constructorFailed = true;
    }

    ASSERT_TRUE(constructorFailed);
  }
}

TEST_F(TestUtilityDateTime, DateTimeConstructorsGood)
{
  bool constructorFailed = false;

  try {
    DateTime goodDateTime1(2015, 2, 2, 2, 2, 2);
  } catch (DateTimeConsistencyException& exception) {
    constructorFailed = true;
  }

  ASSERT_FALSE(constructorFailed);

  DateTime goodDateTime;
  time_t currentTimestamp = time(0);
  struct tm currentTimeFromGoodDateTime;

  ASSERT_TRUE(todos_utility::DateTimeToTm(goodDateTime, currentTimeFromGoodDateTime));

  time_t goodDateTimestamp = mktime(&currentTimeFromGoodDateTime);

  ASSERT_LT(difftime(currentTimestamp, goodDateTimestamp), 10);
}

TEST_F(TestUtilityDateTime, DateTimeGettersSetters)
{
  DateTime datetime(2015, 1, 2, 3, 4, 5);

  ASSERT_EQ(2015, datetime.GetYear());
  ASSERT_EQ(1, datetime.GetMonth());
  ASSERT_EQ(2, datetime.GetDay());
  ASSERT_EQ(3, datetime.GetHour());
  ASSERT_EQ(4, datetime.GetMinute());
  ASSERT_EQ(5, datetime.GetSecond());

  datetime.SetYear(2016);
  ASSERT_EQ(2016, datetime.GetYear());

  datetime.SetMonth(2);
  ASSERT_EQ(2, datetime.GetMonth());

  datetime.SetDay(3);
  ASSERT_EQ(3, datetime.GetDay());

  datetime.SetHour(4);
  ASSERT_EQ(4, datetime.GetHour());

  datetime.SetMinute(5);
  ASSERT_EQ(5, datetime.GetMinute());

  datetime.SetSecond(6);
  ASSERT_EQ(6, datetime.GetSecond());

  DateTime datetime1(2015, 1, 2, 3, 4, 5);
  DateTime datetime2(2015, 1, 2, 3, 4, 5);

  ASSERT_TRUE(datetime1 == datetime2);
}

TEST_F(TestUtilityDateTime, DateTimeConversions)
{
  DateTime datetime1(2015, 1, 2, 3, 4, 5);
  
  ASSERT_EQ(datetime1, todos_utility::StringToDateTime("2015-1-2 03:04:05"));
  ASSERT_EQ("2015-01-02 03:04:05", todos_utility::DateTimeToString(datetime1));

  struct tm testtm;

  ASSERT_TRUE(todos_utility::DateTimeToTm(datetime1, testtm));

  ASSERT_EQ(datetime1.GetYear() - 1900, testtm.tm_year);
  ASSERT_EQ(datetime1.GetMonth() - 1, testtm.tm_mon);
  ASSERT_EQ(datetime1.GetDay(), testtm.tm_mday);
  ASSERT_EQ(datetime1.GetHour(), testtm.tm_hour);
  ASSERT_EQ(datetime1.GetMinute(), testtm.tm_min);
  ASSERT_EQ(datetime1.GetSecond(), testtm.tm_sec);
}
