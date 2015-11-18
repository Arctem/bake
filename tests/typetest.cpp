#include "test_help.h"

class TypeTest : public ::testing::TestWithParam<pair<string, bool>> {
protected:
  virtual void SetUp() {
    ASSERT_FALSE(perform_lex(GetParam().first, false));

    add_builtins();
  }

  virtual void TearDown() {
    ast = nullptr;
  }

  void build_and_typecheck() {
    BuildST build;
    ast->accept(&build);
    CheckScope cs;
    build.getCurrScope()->accept(&cs);
    TypeCheck tc(build.getCurrScope());
    ast->accept(&tc);
  }
};

TEST_P(TypeTest, TestSuccess) {
  if(GetParam().second)
    ASSERT_NO_THROW(build_and_typecheck());
  else
    ASSERT_ANY_THROW(build_and_typecheck());

}

INSTANTIATE_TEST_CASE_P(TypeCoresFail,
			TypeTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "core/type/", false)));

INSTANTIATE_TEST_CASE_P(ValidCoresPass,
			TypeTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "core/valid/", true)));

/* Extended test cases */
INSTANTIATE_TEST_CASE_P(TypeExtendsFail,
			TypeTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "extended/type/", false)));

INSTANTIATE_TEST_CASE_P(ValidExtendsPass,
			TypeTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "extended/valid/", true)));


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
