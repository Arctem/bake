class Main inherits IO {
  main() : Object {
    out_string("Hi World!\n")
  };

  foo(x : String) : Int {
    2
  };
};

class ThingParent inherits Main {
  foo(x : Int) : Int {
    4
  };
};