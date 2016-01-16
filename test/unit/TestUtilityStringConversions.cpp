#include <gtest/gtest.h>

#include <string>

#include <utility/StringConversions.h>

using std::string;

class TestUtilityStringConversions : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(TestUtilityStringConversions, IntToString)
{
  int value = 5;

  ASSERT_EQ("5", todos_utility::IntToString(value));
}

TEST_F(TestUtilityStringConversions, StringToInt)
{
  string value = "5";

  ASSERT_EQ(5, todos_utility::StringToInt(value));
}
