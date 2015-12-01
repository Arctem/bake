/*
 *   Authors:        Russell White, Will Rosenberger
 *   Date:           Sept. 20th, 2015
 *   Description:    Flex lexical anylizer for the COOL language
 *   Bugs:           Probably lots.
 */

#include "driver.h"

/* Function prints the help message */
void help(char* cmd_name) {
  cout << "Usage: " << endl;
  cout << "\t" << cmd_name << " input_file" << endl;
  cout << "\t" << cmd_name << " -i input_file -l output_file" << endl;
  cout << "input_file: File to scan" << endl;
  cout << "output_file: File in which to place the output. Defaults to <input_file>-lex-bake" << endl;
}

void add_builtins() {
  // Adds built ins: Object, IO, String, Int, Bool
  ast->add(buildObject());
  ast->add(buildIO());
  ast->add(buildString());
  ast->add(buildBool());
  add_nums();

  ast->add(buildConvert());
}

void add_nums() {
  ast->add(new ClassStatement(new Type(new string("_Num")), new Type(new string("Object")), nullptr, false));
  ast->add(new ClassStatement(new Type(new string("Int")), new Type(new string("_Num")), nullptr, true));

  // Add the extended built ins: Float, Int8, Int32, Int64
  ast->add(new ClassStatement(new Type(new string("Float")), new Type(new string("_Num")), nullptr, true));
  ast->add(new ClassStatement(new Type(new string("Int8")), new Type(new string("_Num")), nullptr, true));
  ast->add(new ClassStatement(new Type(new string("Int32")), new Type(new string("_Num")), nullptr, true));
  ast->add(new ClassStatement(new Type(new string("Int64")), new Type(new string("_Num")), nullptr, true));
}

/* Build Object */
ClassStatement* buildObject() {
  FeatureList* methods = new FeatureList();
  methods->add(new FeatureOption(new Feature(new Id(new string("abort")), new ListFormalDeclare(), new Type(new string("Object")), new ExprList())));
  methods->add(new FeatureOption(new Feature(new Id(new string("type_name")), new ListFormalDeclare(), new Type(new string("SELF_TYPE")), new ExprList())));
  methods->add(new FeatureOption(new Feature(new Id(new string("copy")), new ListFormalDeclare(), new Type(new string("SELF_TYPE")), new ExprList())));
  return new ClassStatement(new Type(new string("Object")), nullptr, methods);
}

ClassStatement* buildIO() {
  FeatureList* methods = new FeatureList();
  ListFormalDeclare* outStringList = new ListFormalDeclare();
  ListFormalDeclare* outIntList = new ListFormalDeclare();

  outStringList->add(new FormalDeclare(new Id(new string("x")), new Type(new string("String")), nullptr));
  outIntList->add(new FormalDeclare(new Id(new string("x")), new Type(new string("Int")), nullptr));

  methods->add(new FeatureOption(new Feature(new Id(new string("out_string")), outStringList, new Type(new string("SELF_TYPE")), new ExprList())));
  methods->add(new FeatureOption(new Feature(new Id(new string("out_int")),outIntList, new Type(new string("SELF_TYPE")), new ExprList())));
  methods->add(new FeatureOption(new Feature(new Id(new string("in_string")), new ListFormalDeclare(), new Type(new string("String")), new ExprList())));
  methods->add(new FeatureOption(new Feature(new Id(new string("in_int")), new ListFormalDeclare(), new Type(new string("Int")), new ExprList())));
  return new ClassStatement(new Type(new string("IO")), new Type(new string("Object")), methods);
}

ClassStatement* buildString() {
  FeatureList* methods = new FeatureList();
  ListFormalDeclare* concatParam = new ListFormalDeclare();
  ListFormalDeclare* substrParam = new ListFormalDeclare();

  concatParam->add(new FormalDeclare(new Id(new string("s")), new Type(new string("String")), nullptr));
  substrParam->add(new FormalDeclare(new Id(new string("i")), new Type(new string("Int")), nullptr));
  substrParam->add(new FormalDeclare(new Id(new string("l")), new Type(new string("Int")), nullptr));

  methods->add(new FeatureOption(new FormalDeclare(new Id(new string("theString")), new Type(new string("Bool")))));
  methods->add(new FeatureOption(new Feature(new Id(new string("length")), new ListFormalDeclare(), new Type(new string("Int")), new ExprList())));
  methods->add(new FeatureOption(new Feature(new Id(new string("concat")), concatParam, new Type(new string("String")), new ExprList())));
  methods->add(new FeatureOption(new Feature(new Id(new string("substr")), substrParam, new Type(new string("String")), new ExprList())));
  return new ClassStatement(new Type(new string("String")), new Type(new string("Object")), methods, true);
}

ClassStatement* buildBool() {
  return new ClassStatement(new Type(new string("Bool")), new Type(new string("Object")), nullptr, true);
}

ClassStatement* buildConvert() {
  FeatureList* methods = new FeatureList();

  const char * const types[] = { "Int", "Int64", "Int32", "Int8", "Float" };
  for(string type : types) {
    methods->add(buildConvertFunc(type));
  }

  return new ClassStatement(new Type(new string("Convert")), new Type(new string("Object")), methods, true);
}

FeatureOption* buildConvertFunc(string name) {
  ListFormalDeclare* convertArgs = new ListFormalDeclare();
  convertArgs->add(new FormalDeclare(new Id(new string("s")), new Type(new string("_Num")), nullptr));
  return new FeatureOption(new Feature(new Id(new string("to" + name)), convertArgs, new Type(new string(name)), new ExprList()));
}
