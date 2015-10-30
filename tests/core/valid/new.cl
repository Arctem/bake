class Main {
  x : Int <- new Int;
  a : Bool <- new Bool;
  s : String <- new String;
  b : B <- new B;
  c : B <- new C;

  main() : Object {
      (new Object).copy()
  };
};

class B{
};

class C inherits B {};
