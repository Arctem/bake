#!/usr/bin/python3
import sys
import os
from subprocess import check_output, STDOUT, CalledProcessError
import difflib

BAKE = "../build/src/bake"
CL_TEST_DIR = "lexer_tests/" # Directory that contains the .cl files to be tested
OUTPUT = "lexer_output/" # Where to put the lexer files produced by the official Cool interpreter.

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
    return fail.decode("unicode_escape")

  # If the lexer succeeded, open the output file and return its contents
  with open(OUTPUT + filename + ".cl-lex") as output:
    return output.read()

def bake_output(filename):
  """
    Lexes the file pointed to by the path in filename using the Bake lexer
    Returns a string contianing the output of the lexer
  """
  # Command that runs our lexer on the given file
  cmd = "{} {}".format(BAKE, CL_TEST_DIR + filename)

  return check_output(cmd, shell = True).decode("unicode_escape")

def main(args):
  cool_files = [f for f in os.listdir(CL_TEST_DIR) if f.endswith(".cl")] # Get all .cl files in the test directory

  for f in cool_files:
    print("----------- Testing {} -----------".format(f))
    bake_o = bake_output(f)
    ref_o = ref_output(f)

    if bake_o == ref_o:
      print("Match!")
    else:
      print("Don't match")
      
      if "-v" in args:
        for line in difflib.ndiff(bake_o, ref_o):
          if line[0] == '+':
            print("Reference lexer: {}".format(line))
          elif line[0] == '-':
            print("Bake: {}".format(line))

if __name__ == "__main__":
  main(sys.argv)