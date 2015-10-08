#include <iostream>

#include <dirent.h>

#include "gtest/gtest.h"

#include "driver.h"

#define TESTDIR "tests/"

class LexTest : public ::testing::TestWithParam<string> {
protected:
  virtual void SetUp() {
  }
};

TEST_P(LexTest, TestSuccess) {
  if(GetParam().find("/invalid/") == string::npos)
    ASSERT_FALSE(perform_lex(GetParam(), false));
  else
    ASSERT_TRUE(perform_lex(GetParam(), false));
}

// From http://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c
inline bool ends_with(std::string const & value, std::string const & ending)
{
  if (ending.size() > value.size()) return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

// From http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
std::vector<string> GetAllFiles(string directory) {
  printf("%s\n", directory.c_str());
  DIR *dir = opendir(directory.c_str());
  struct dirent *ent;
  std::vector<string> files;
  while((ent = readdir(dir)) != NULL) {
    std::string file(ent->d_name);
    if(ends_with(file, ".cl")) {
      files.push_back(directory + file);
    }
  }
  closedir(dir);
  return files;
}

INSTANTIATE_TEST_CASE_P(ValidCoresPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "core/valid/")));

INSTANTIATE_TEST_CASE_P(InvalidCoresFail,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "core/invalid/")));

INSTANTIATE_TEST_CASE_P(ValidExtendedsPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "extended/valid/")));

INSTANTIATE_TEST_CASE_P(InvalidExtendedsPass,
			LexTest,
			::testing::ValuesIn(GetAllFiles(TESTDIR "extended/invalid/")));

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
