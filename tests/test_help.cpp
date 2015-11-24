#include "test_help.h"

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
