#pragma once

#include <unordered_set>
#include <queue>

#include "ir/basic_block.h"

/*
  We have X registers (I forget off the top of my head).
  Use very simple painting algorithm to figure out how many we need total (first version will likely be "we need lots").
  Start assigning registers, keeping track of which are available to be used and not.
  Add a new command at the very start of the block to allocate how much spare space we need.
  Insert new things into the IR to store/load stuff from that allocated block.
*/

namespace codegen {
  class Allocator {
  public:
    Allocator(ir::Method* method);

    static const char * getRegister(int registerNum) { return registers[registerNum]; };

    void reduceRegisters();
    bool usedInFuture(int regNum, ir::BasicBlock *block, int opNum);
    int countRegisters();
    void addMalloc(int registerLimit);
    void incrementRegisters();
    void addMemoryManagement(int registerLimit);

  private:
    static const char * registers[];
    static const char * stack_ptr;
    //might need to put other register types (rbp, rsi, rdi) here.

    ir::Method* method;
  };
}
