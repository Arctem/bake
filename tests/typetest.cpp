#include <iostream>

#include <dirent.h>

#include "gtest/gtest.h"

#include "driver.h"

#define TESTDIR "tests/"


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
  }
};

TEST_P(TypeTest, TestSuccess) {
  std::cout << GetParam().first << "Should pass: " << GetParam().second << std::endl;

  if(GetParam().second)
    ASSERT_NO_THROW(build_and_typecheck());
  else
    ASSERT_ANY_THROW(build_and_typecheck());

}

// From http://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c
inline bool ends_with(std::string const & value, std::string const & ending)
{
  if (ending.size() > value.size()) return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

// From http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
std::vector<pair<string, bool>> GetAllFiles(string directory, bool valid) {
  printf("%s\n", directory.c_str());
  DIR *dir = opendir(directory.c_str());
  struct dirent *ent;
  std::vector<pair<string, bool>> files;
  while((ent = readdir(dir)) != NULL) {
    std::string file(ent->d_name);
    if(ends_with(file, ".cl")) {
      files.push_back(make_pair(directory + file, valid));
    }
  }
  closedir(dir);
  return files;
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