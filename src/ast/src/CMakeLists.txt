
include_directories(../inc)
add_library(ast STATIC node.cpp terminals.cpp binary_ops.cpp unary_ops.cpp visitor.cpp)