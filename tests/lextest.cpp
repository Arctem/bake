#include "test_help.h"

class LexTest : public ::testing::TestWithParam<pair<string, bool>> {
protected:
  virtual void SetUp() {
  }
};

TEST_P(LexTest, TestSuccess) {
  //If the bool is true, it should pass
  if(GetParam().second)
    ASSERT_FALSE(perform_lex(GetParam().first, false));
  else
    ASSERT_TRUE(perform_lex(GetParam().first, false));
}

INSTANTIATE_TEST_CASE_P(LexCoresFail,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "core/lex/", false)));

INSTANTIATE_TEST_CASE_P(ParseCoresPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "core/parse/", false)));

INSTANTIATE_TEST_CASE_P(TypeCoresPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "core/type/", true)));

INSTANTIATE_TEST_CASE_P(ValidCoresPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "core/valid/", true)));

/* Extended test cases */
INSTANTIATE_TEST_CASE_P(LexExtendsFail,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "extended/lex/", false)));

INSTANTIATE_TEST_CASE_P(ParseExtendsPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "extended/parse/", false)));

INSTANTIATE_TEST_CASE_P(TypeExtendsPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "extended/type/", true)));

INSTANTIATE_TEST_CASE_P(ValidExtendsPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "extended/valid/", true)));


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
