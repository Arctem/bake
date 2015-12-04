#include "test_help.h"

class CodeGenTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    testIR = new ir::ClassList();
    testClass = new ir::ClassDef("Test");
    testMeth = new ir::Method("DoesStuff");
    dev = codegen::Director::getInstance();

    testIR->addClass(testClass->getName(), testClass);
    testClass->addMethod(testMeth);
  }

  virtual void TearDown() {
    codegen::Director::reset();
  }

  ir::ClassList *testIR;
  ir::ClassDef *testClass;
  ir::Method *testMeth;
  codegen::Director *dev;
};

TEST_F(CodeGenTest, NopTest) {
  testMeth->addOp(new ir::Nop());

  dev->generateCode(testIR);

  std::cout << "Begin blocklist Print" << std::endl;
  for(auto block : dev->getBlockList()) {
    std::cout << *block << std::endl;
    //TODO: Add some kind of check that the output was correct.
    //TODO: Add some more complicated thingies.
  }
  std::cout << "End blocklist Print" << std::endl;
}

TEST_F(CodeGenTest, AddTest) {
  // 0 + 1 -> 1
  // 1 + 0 -> 1 (should be same as first)
  // 1 + 2 -> 3 (should generate a mov as well)
  testMeth->addOp(new ir::Add(std::pair<int, ir::RegisterType>(0, ir::INT),
                              std::pair<int, ir::RegisterType>(1, ir::INT),
                              std::pair<int, ir::RegisterType>(1, ir::INT)));
  testMeth->addOp(new ir::Add(std::pair<int, ir::RegisterType>(1, ir::INT),
                              std::pair<int, ir::RegisterType>(0, ir::INT),
                              std::pair<int, ir::RegisterType>(1, ir::INT)));
  testMeth->addOp(new ir::Add(std::pair<int, ir::RegisterType>(1, ir::INT),
                              std::pair<int, ir::RegisterType>(2, ir::INT),
                              std::pair<int, ir::RegisterType>(3, ir::INT)));

  dev->generateCode(testIR);

  std::cout << "Begin blocklist Print" << std::endl;
  for(auto block : dev->getBlockList()) {
    std::cout << *block << std::endl;
  }
  std::cout << "End blocklist Print" << std::endl;
}

TEST_F(CodeGenTest, SubTest) {
  //0 - 1 -> 0
  //1 - 0 -> 0
  //0 - 1 -> 2
  testMeth->addOp(new ir::Sub(std::pair<int, ir::RegisterType>(0, ir::INT),
                              std::pair<int, ir::RegisterType>(1, ir::INT),
                              std::pair<int, ir::RegisterType>(0, ir::INT)));
  testMeth->addOp(new ir::Sub(std::pair<int, ir::RegisterType>(1, ir::INT),
                              std::pair<int, ir::RegisterType>(0, ir::INT),
                              std::pair<int, ir::RegisterType>(0, ir::INT)));
  testMeth->addOp(new ir::Sub(std::pair<int, ir::RegisterType>(0, ir::INT),
                              std::pair<int, ir::RegisterType>(1, ir::INT),
                              std::pair<int, ir::RegisterType>(2, ir::INT)));

  dev->generateCode(testIR);

  std::cout << "Begin blocklist Print" << std::endl;
  for(auto block : dev->getBlockList()) {
    std::cout << *block << std::endl;
  }
  std::cout << "End blocklist Print" << std::endl;
}

TEST_F(CodeGenTest, MulTest) {
  //0 - 1 -> 0
  //1 - 0 -> 0
  //0 - 1 -> 2
  testMeth->addOp(new ir::Mul(std::pair<int, ir::RegisterType>(0, ir::INT),
    std::pair<int, ir::RegisterType>(1, ir::INT),
    std::pair<int, ir::RegisterType>(0, ir::INT)));
  testMeth->addOp(new ir::Mul(std::pair<int, ir::RegisterType>(1, ir::INT),
    std::pair<int, ir::RegisterType>(0, ir::INT),
    std::pair<int, ir::RegisterType>(1, ir::INT)));
  testMeth->addOp(new ir::Mul(std::pair<int, ir::RegisterType>(2, ir::INT),
    std::pair<int, ir::RegisterType>(1, ir::INT),
    std::pair<int, ir::RegisterType>(0, ir::INT)));

  dev->generateCode(testIR);

  std::cout << std::endl << "Begin blocklist Print" << std::endl;
  for (auto block : dev->getBlockList()) {
    std::cout << *block << std::endl;
  }
  std::cout << "End blocklist Print" << std::endl;
}

TEST_F(CodeGenTest, DivTest) {
  //0 - 1 -> 0
  //1 - 0 -> 0
  //0 - 1 -> 2
  testMeth->addOp(new ir::Div(std::pair<int, ir::RegisterType>(0, ir::INT),
    std::pair<int, ir::RegisterType>(1, ir::INT),
    std::pair<int, ir::RegisterType>(0, ir::INT)));
  testMeth->addOp(new ir::Div(std::pair<int, ir::RegisterType>(1, ir::INT),
    std::pair<int, ir::RegisterType>(0, ir::INT),
    std::pair<int, ir::RegisterType>(1, ir::INT)));
  testMeth->addOp(new ir::Div(std::pair<int, ir::RegisterType>(2, ir::INT),
    std::pair<int, ir::RegisterType>(1, ir::INT),
    std::pair<int, ir::RegisterType>(0, ir::INT)));

  dev->generateCode(testIR);

  std::cout << std::endl << "Begin blocklist Print" << std::endl;
  for (auto block : dev->getBlockList()) {
    std::cout << *block << std::endl;
  }
  std::cout << "End blocklist Print" << std::endl;
}

TEST_F(CodeGenTest, ManyRegistersHandleIt) {
  for(int i = 0; i < 15; i++) {
    testMeth->addOp(new ir::Add(std::pair<int, ir::RegisterType>(i, ir::INT),
                                std::pair<int, ir::RegisterType>(i + 1, ir::INT),
                                std::pair<int, ir::RegisterType>(i + 2, ir::INT)));
  }

  dev->generateCode(testIR);

  std::cout << "Begin blocklist Print" << std::endl;
  for(auto block : dev->getBlockList()) {
    std::cout << *block << std::endl;
  }
  std::cout << "End blocklist Print" << std::endl;
}

TEST_F(CodeGenTest, GenningEverything) {
  testMeth->addOp(new ir::Copy(std::pair<int, ir::RegisterType>(1, ir::CONSTANT), std::pair<int, ir::RegisterType>(0, ir::INT)));
  testMeth->addOp(new ir::Copy(std::pair<int, ir::RegisterType>(1, ir::CONSTANT), std::pair<int, ir::RegisterType>(1, ir::INT)));
  testMeth->addOp(new ir::Add(std::pair<int, ir::RegisterType>(0, ir::INT),
    std::pair<int, ir::RegisterType>(1, ir::INT),
    std::pair<int, ir::RegisterType>(2, ir::INT)));
  
  testMeth->addOp(new ir::OutInt(std::pair<int, ir::RegisterType>(2, ir::INT), std::pair<int, ir::RegisterType>(2, ir::INT)));

  // generate the code
  dev->generateCode(testIR);

  std::cout << "Begin blocklist Print genningeverything" << std::endl;
  for (auto block : dev->getBlockList()) {
    std::cout << *block << std::endl;
  }
  std::cout << "End blocklist Print" << std::endl;

  // write it to a file
  dev->writeFile("outint.s");
}

TEST_F(CodeGenTest, MultiBlockDrifting) {
  testMeth->addOp(new ir::Copy(std::pair<int, ir::RegisterType>(1, ir::CONSTANT), std::pair<int, ir::RegisterType>(0, ir::INT)));
  testMeth->addOp(new ir::Copy(std::pair<int, ir::RegisterType>(2, ir::CONSTANT), std::pair<int, ir::RegisterType>(1, ir::INT)));

  for(int i = 2; i < codegen::Allocator::regNum + 1; i++) {
    testMeth->addOp(new ir::Add(std::pair<int, ir::RegisterType>(0, ir::INT),
                                std::pair<int, ir::RegisterType>(1, ir::INT),
                                std::pair<int, ir::RegisterType>(i, ir::INT)));
  }

  testMeth->setBrOnTrue(new ir::BasicBlock());
  testMeth->getBrOnTrue()->addOp(new ir::Add(std::pair<int, ir::RegisterType>(0, ir::INT),
                                             std::pair<int, ir::RegisterType>(1, ir::INT),
                                             std::pair<int, ir::RegisterType>(codegen::Allocator::regNum, ir::INT)));
  testMeth->getBrOnTrue()->addOp(new ir::OutInt(std::pair<int, ir::RegisterType>(codegen::Allocator::regNum, ir::INT),
                                                std::pair<int, ir::RegisterType>(codegen::Allocator::regNum, ir::INT)));

  dev->generateCode(testIR);

  std::cout << "Begin blocklist Print" << std::endl;
  for(auto block : dev->getBlockList()) {
    std::cout << *block << std::endl;
  }
  std::cout << "End blocklist Print" << std::endl;

  dev->writeFile("multiblock.s");
}
