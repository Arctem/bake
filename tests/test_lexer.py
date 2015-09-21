#!/usr/bin/python3
import sys
import os
from subprocess import check_output, STDOUT, CalledProcessError
import difflib
import codecs

BAKE = "../build/src/bake"
CL_TEST_DIR = "lexer_tests/" # Directory that contains the .cl files to be tested
OUTPUT = "lexer_output/" # Where to put the lexer files produced by the official Cool interpreter.
VERBOSE = "v" in sys.argv

def ref_output(filename):
  """
    Lexes the file pointed to by the path in filename using the reference Cool lexer
    Returns a string contianing the output of the reference lexer
  """
  # Cool command: Run only the lexer and send the output to the correct directory
  cmd = "cool --lex {} --out {}".format(CL_TEST_DIR + filename, OUTPUT + filename)
  
  # Run the cool compiler. If it fails, it will return a string containing a description of why.
  fail = check_output(cmd, shell = True)

  if fail:
    return fail.decode("latin-1")

  # If the lexer succeeded, open the output file and return its contents
  with codecs.open(OUTPUT + filename + ".cl-lex", encoding="latin-1") as output:
    return output.read()

def bake_output(filename):
  """
    Lexes the file pointed to by the path in filename using the Bake lexer
    Returns a string contianing the output of the lexer
  """
  # Command that runs our lexer on the given file
  cmd = "{} -i {} -o {}".format(BAKE, CL_TEST_DIR + filename, OUTPUT + filename + "-lex-bake")

  fail = check_output(cmd, shell = True)
  if fail:
    return fail.decode("latin-1")

  # If the lexer succeeded, open the output file and return its contents
  with codecs.open(OUTPUT + filename + "-lex-bake", encoding="latin-1") as output:
    return output.read()

def same_output(filename):
  """
    Checks that the reference lexer and Bake have the same output
  """
  # Compare output of good test between the bake and reference
  bake_o = bake_output(filename)
  ref_o = ref_output(filename)

  if bake_o == ref_o:
    print("Match!")
  else:
    print("Don't match")
    
    if VERBOSE:
      for line in difflib.ndiff(bake_o, ref_o):
        if line[0] == '+':
          print("Reference lexer: {}".format(line))
        elif line[0] == '-':
          print("Bake: {}".format(line))

def check_failure(filename):
  """
    Checks whether the given file fails.
  """
  try:
    bake_output(filename)
  except CalledProcessError:
    print("Test faild as excepted")

def main():
  cool_files = [f for f in os.listdir(CL_TEST_DIR) if f.endswith(".cl")] # Get all .cl files in the test directory

  for f in cool_files:
    print("----------- Testing {} -----------".format(f))

    # Check tests that should error
    if f in ["invalid-character.cl"]:
      check_failure(f)
    else:
      same_output(f)

if __name__ == "__main__":
  main()