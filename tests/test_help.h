#pragma once

#include <iostream>
#include <dirent.h>

#include "gtest/gtest.h"
#include "driver.h"
#include "codegen/allocator.h"
#include "codegen/director.h"

#define TESTDIR "tests/"


inline bool ends_with(std::string const & value, std::string const & ending);
std::vector<pair<string, bool>> GetAllFiles(string directory, bool valid);
