#pragma once

#include <string>

#include "codegen/allocator.h"

namespace codegen {
  class Generator {
  private:
    
  public:
    static std::string* generateBuiltInClassList();
    static std::string* generateBuiltInMethods();

    void addToDataList(std::string* s);

    void pushAll();
    void popAll();

    void genNoOp();
    void fnop();

    void genLabel(std::string label);

    void genMov(std::string r1, std::string r2);
    void genCopy(std::string r1, std::string r2);

    void genAdd(std::string r1, std::string r2);
    void genSub(std::string r1, std::string r2);
    void genMul(std::string r1);
    void genDiv(std::string r1);
    void genNeg(std::string r1);

    void genPush(std::string src);
    void genPop(std::string dest);

    void genCall(std::string func);
    void genXchg(std::string r1, std::string r2);
  };
}
