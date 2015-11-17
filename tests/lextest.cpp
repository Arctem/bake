#include <iostream>

#include <dirent.h>

#include "gtest/gtest.h"

#include "driver.h"

#define TESTDIR "tests/"

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
  if(dir) {
    while((ent = readdir(dir)) != NULL) {
      std::string file(ent->d_name);
      if(ends_with(file, ".cl")) {
	files.push_back(make_pair(directory + file, valid));
      }
    }
  }
  closedir(dir);
  return files;
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
