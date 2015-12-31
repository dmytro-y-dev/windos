#include <gtest/gtest.h>

#include <model/entity/user/User.h>

using todos_model_entity::User;

class TestModelEntityUser: public ::testing::Test
{
public:
  TestModelEntityUser()
  {
  }

protected:
  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(TestModelEntityUser, UserGettersSetters)
{
  unsigned int id = 1;
  User::String login = "old-login";
  User::String password = "old-password";
  User::DateTime signedUpOn = User::DateTime(2015, 12, 31, 23, 59, 0);

  User user(id, login, password, signedUpOn);
  ASSERT_TRUE(user.GetId() == id);
  ASSERT_TRUE(user.GetLogin() == login);
  ASSERT_TRUE(user.GetPassword() == password);
  ASSERT_TRUE(user.GetSignedUpOn() == signedUpOn);

  unsigned int newId = 2;
  user.SetId(newId);
  EXPECT_TRUE(user.GetId() == newId);

  User::String newLogin = "new-login";
  user.SetLogin(newLogin);
  EXPECT_TRUE(user.GetLogin() == newLogin);

  User::String newPassword = "new-password";
  user.SetPassword(newPassword);
  EXPECT_TRUE(user.GetPassword() == newPassword);

  User::DateTime newSignedUpOn = User::DateTime(2015, 12, 13, 20, 14, 0);
  user.SetSignedUpOn(newSignedUpOn);
  EXPECT_TRUE(user.GetSignedUpOn() == newSignedUpOn);
}
