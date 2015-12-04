#pragma once

#include <string>
#include <vector>

#include "ir/class_list.h"

// singleton. Only 1 instance is ever needed per program.
namespace codegen {
  class Director {
  public:
    void generateBlocksFromIR(ir::ClassList* classes);
    void generateDataFromIR(ir::ClassList* classes);
    void generateBuiltInClassList();
    std::vector<std::string*> getBlockList() { return blockList; }
    void addToBlockList(std::string* s) { blockList.push_back(s); }

    void writeFile(string filename);

    static Director* getInstance();
    static void generateCode(ir::ClassList* classes);
    static void reset();

    ~Director() { for (auto s : blockList) { delete s; } }

  private:
    Director() {};
    std::vector<std::string*> blockList;
    static Director* instance;
  };
}
