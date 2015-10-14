
#ifndef __AST__
#define __AST__


// Contains:
//  BinaryOp, Plus, Minus, Multiply, Divide, LessThan,
//  LessThanEqual, Equal, Assign
#include "binary_ops.h"

// Contains:
//  NodeType Enum, Node parent class. 
#include "node.h"

// Contains:
//  Leaf, IntegerVal, StringVal, BoolVal, Id, Type.
#include "terminals.h"

// Contains:
//  UnaryOp, LogicalNot, BitNot, Isvoid, New, 
#include "unary_ops.h"

// Contains: 
//  
#include "misc_ops.h"

// Contains:
//  CaseList, CaseStatement ClassList, ClassStatement,
//  Dispatch, ExprList, Feature, FeatureList, FeatureOption,
//  LetStatement, ListFormalDeclare.
#include "nary.h"


#include "visitor.h"

#endif