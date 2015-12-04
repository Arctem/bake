#include "codegen/allocator.h"

namespace codegen {
  //registers in order of preferred usage
  const char * Allocator::registers[] = { "%rax", "%rbx", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15" };
  const char * Allocator::stack_ptr = "%rsp";
  const int Allocator::regNum = sizeof(registers) / sizeof(*registers);

  Allocator::Allocator(ir::Method* method) {
    this->method = method;

    reduceRegisters();
    int regLimit = countRegisters();
    std::cout << "Need " << regLimit << " out of " <<
      sizeof(registers) / sizeof(*registers) <<
      " available registers." << std::endl;

    if(regLimit > sizeof(registers) / sizeof(*registers)) {
      //If we go over the amount we're allowed to use, we need an extra to store our overflow space.
      regLimit++;
      addMalloc(regLimit);
      addMemoryManagement(regLimit);
    }
  }

  void Allocator::reduceRegisters() {
    std::unordered_set<ir::BasicBlock*> reducedBlocks;

    queue<ir::BasicBlock*> toReduce;

    toReduce.push(this->method);

    while(!toReduce.empty()) {
      ir::BasicBlock* curBlock = toReduce.front();
      toReduce.pop();
      if(reducedBlocks.count(curBlock) != 0) {
        continue;
      }

      //TODO: Reduce things here.

      reducedBlocks.insert(curBlock);
      if(curBlock->getBrOnTrue() != nullptr) {
        toReduce.push(curBlock->getBrOnTrue());
      }
      if(curBlock->getBrOnFalse() != nullptr) {
        toReduce.push(curBlock->getBrOnFalse());
      }
    }
  }

  bool Allocator::usedInFuture(int regNum, ir::BasicBlock *block, int opNum) {
    return true;
  }

  int Allocator::countRegisters() {
    int maxRegister = -1;
    std::unordered_set<ir::BasicBlock*> countedBlocks;
    queue<ir::BasicBlock*> toCount;

    toCount.push(this->method);

    while(!toCount.empty()) {
      ir::BasicBlock* curBlock = toCount.front();
      toCount.pop();
      if(countedBlocks.count(curBlock) != 0) {
        continue;
      }

      for(auto op: curBlock->getOps()) {
        if(op->getSrc1Size() > 0 && op->getSrc1Register() > maxRegister) {
          maxRegister = op->getSrc1Register();
        }
        if(op->getSrc2Size() > 0 && op->getSrc2Register() > maxRegister) {
          maxRegister = op->getSrc2Register();
        }
        if(op->getDestSize() > 0 && op->getDestRegister() > maxRegister) {
          maxRegister = op->getDestRegister();
        }
      }

      countedBlocks.insert(curBlock);
      if(curBlock->getBrOnTrue() != nullptr) {
        toCount.push(curBlock->getBrOnTrue());
      }
      if(curBlock->getBrOnFalse() != nullptr) {
        toCount.push(curBlock->getBrOnFalse());
      }
    }

    return maxRegister + 1;
  }

  void Allocator::addMalloc(int registerLimit) {
    incrementRegisters();

    //And now we actually add the allocation.
    int size = registerLimit - sizeof(registers) / sizeof(*registers);
    size *= (8 * 4); //apparently this is stored in bits ¯\_(ツ)_/¯
    method->addOp(new ir::Alloc(size, std::pair<int, ir::RegisterType>(0, ir::INT)), 0);

    //Now we need to remember to free it before we return...
    std::unordered_set<ir::BasicBlock*> countedBlocks;
    queue<ir::BasicBlock*> toCount;

    toCount.push(this->method);

    while(!toCount.empty()) {
      ir::BasicBlock* curBlock = toCount.front();
      toCount.pop();
      if(countedBlocks.count(curBlock) != 0) {
        continue;
      }

      if(curBlock->getBrOnTrue() == nullptr && curBlock->getBrOnFalse() == nullptr) {
        curBlock->addOp(new ir::Free(std::pair<int, ir::RegisterType>(0, ir::INT)));
      }

      countedBlocks.insert(curBlock);
      if(curBlock->getBrOnTrue() != nullptr) {
        toCount.push(curBlock->getBrOnTrue());
      }
      if(curBlock->getBrOnFalse() != nullptr) {
        toCount.push(curBlock->getBrOnFalse());
      }
    }
  }

  void Allocator::incrementRegisters() {
    /**
     * Because the first register will store the address of the allocated space, we need
     * to offset every existing assigned register by 1
     */
    std::unordered_set<ir::BasicBlock*> countedBlocks;
    queue<ir::BasicBlock*> toCount;

    toCount.push(this->method);

    while(!toCount.empty()) {
      ir::BasicBlock* curBlock = toCount.front();
      toCount.pop();
      if(countedBlocks.count(curBlock) != 0) {
        continue;
      }

      for(auto op: curBlock->getOps()) {
        if(op->getSrc1Size() > 0) {
          op->setSrc1Register(op->getSrc1Register() + 1);
        }
        if(op->getSrc2Size() > 0) {
          op->setSrc2Register(op->getSrc2Register() + 1);
        }
        if(op->getDestSize() > 0) {
          op->setDestRegister(op->getDestRegister() + 1);
        }
      }

      countedBlocks.insert(curBlock);
      if(curBlock->getBrOnTrue() != nullptr) {
        toCount.push(curBlock->getBrOnTrue());
      }
      if(curBlock->getBrOnFalse() != nullptr) {
        toCount.push(curBlock->getBrOnFalse());
      }
    }
  }

  void Allocator::addMemoryManagement(int registerLimit) {
    //We assume that the first memory address stores the overflow area.
    int regAmt = sizeof(registers) / sizeof(*registers);

    //Start the giant loop thing to look for registers beyond the limit.
    std::unordered_set<ir::BasicBlock*> countedBlocks;
    queue<ir::BasicBlock*> toCount;

    toCount.push(this->method);

    while(!toCount.empty()) {
      ir::BasicBlock* curBlock = toCount.front();

      toCount.pop();
      if(countedBlocks.count(curBlock) != 0) {
        continue;
      }

      countedBlocks.insert(curBlock);
      if(curBlock->getBrOnTrue() != nullptr) {
        toCount.push(curBlock->getBrOnTrue());
      }
      if(curBlock->getBrOnFalse() != nullptr) {
        toCount.push(curBlock->getBrOnFalse());
      }

      //Start at op 1 if first block because 0 is the alloc.
      for(int i = (curBlock == this->method ? 1 : 0); i < curBlock->getOps().size(); i++) {
        std::cout << i << " " << curBlock->getOps().size() << std::endl;
        ir::Op* op = curBlock->getOps()[i];

        int src1 = -1, src2 = -1, dest = -1;

        //Need to figure out which registers we need to move in and which we're able to replace
        if(op->getSrc1Size() > 0) {
          src1 = op->getSrc1Register();
          //          method->addOp(, i); //push current thing in the register we're gonna use
        }
        if(op->getSrc2Size() > 0) {
          src2 = op->getSrc2Register();
          //          method->addOp(, i); //push current thing in the register we're gonna use
        }
        if(op->getDestSize() > 0) {
          dest = op->getDestRegister();
          //          method->addOp(, i); //push current thing in the register we're gonna use
        }

        std::cout << src1 << " " << src2 << " -> " << dest << std::endl;

        /**
         * In this section I actually determine which registers to use temporarily
         * add add commands to the IR to store those registers until after the operation.
         * The variable i should always be the index of the variable op, which is why I
         * increment it when I add an instruction before it (like a push).
         */
        if(dest >= regAmt) {
          dest = 1;
          while(dest == src1 || dest == src2) {
            dest++;
          }
          curBlock->addOp(new ir::Push(std::pair<int, ir::RegisterType>(dest, ir::INT)), i);
          i++; //Keep it pointing directly at the current op
          curBlock->addOp(new ir::StoreI(std::pair<int, ir::RegisterType>(dest, ir::INT),
                                       std::pair<int, ir::RegisterType>(0, ir::INT),
                                       op->getDestRegister() - regAmt), i + 1);
          curBlock->addOp(new ir::Pop(std::pair<int, ir::RegisterType>(dest, ir::INT)), i + 2);
        }

        //Find register to use for parameter 1
        if(src1 == op->getDestRegister() && dest != -1) {
          src1 = dest;

          //Don't need to Push/Pop because dest's block already did
          curBlock->addOp(new  ir::LoadI(std::pair<int, ir::RegisterType>(0, ir::INT),
                                       op->getSrc1Register() - regAmt,
                                       std::pair<int, ir::RegisterType>(src1, ir::INT)), i);
          i++;
        } else if(src1 >= regAmt) {
          src1 = 1;
          while(src1 == dest || src1 == src2) {
            src1++;
          }
          curBlock->addOp(new ir::Push(std::pair<int, ir::RegisterType>(src1, ir::INT)), i);
          i++;
          curBlock->addOp(new ir::LoadI(std::pair<int, ir::RegisterType>(0, ir::INT),
                                      op->getSrc1Register() - regAmt,
                                      std::pair<int, ir::RegisterType>(src1, ir::INT)), i);
          i++;
          curBlock->addOp(new ir::Pop(std::pair<int, ir::RegisterType>(src1, ir::INT)), i + 1);
        }

        //Find register to use for parameter 2
        if(src2 == op->getSrc1Register() && src1 != -1) {
          src2 = src1;
          //Nothing to do, src1 already did it
        } else if(src2 == op->getDestRegister() && dest != -1) {
          src2 = dest;

          //Don't need to Push/Pop because dest's block already did
          curBlock->addOp(new ir::LoadI(std::pair<int, ir::RegisterType>(0, ir::INT),
                                      op->getSrc2Register() - regAmt,
                                      std::pair<int, ir::RegisterType>(src1, ir::INT)), i);
        } else if(src2 >= regAmt) {
          src2 = 1;
          while(src2 == dest || src2 == src1) {
            src2++;
          }

          curBlock->addOp(new ir::Push(std::pair<int, ir::RegisterType>(src2, ir::INT)), i);
          i++;
          curBlock->addOp(new ir::LoadI(std::pair<int, ir::RegisterType>(0, ir::INT),
                                      op->getSrc2Register() - regAmt,
                                      std::pair<int, ir::RegisterType>(src2, ir::INT)), i);
          i++;
          curBlock->addOp(new ir::Pop(std::pair<int, ir::RegisterType>(src2, ir::INT)), i + 1);
        }

        std::cout << src1 << " " << src2 << " -> " << dest << std::endl;

        //Finally, adjust op with these changes.
        if(op->getSrc1Size() > 0) {
          op->setSrc1Register(src1);
        }
        if(op->getSrc2Size() > 0) {
          op->setSrc2Register(src2);
        }
        if(op->getDestSize() > 0) {
          op->setDestRegister(dest);
        }
      }
    }
  }
}
