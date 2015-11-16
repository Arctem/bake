class Main inherits IO {
  main() : Object {
    out_string("Hi World!\n")
  };
};

class ThingParent {
  foo() : Int {
    4
  };
};

class Thing1 inherits Lol {
  func() : Int {
    foo()
  };
};
