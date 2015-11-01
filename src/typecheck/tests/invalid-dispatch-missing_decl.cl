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

class Thing1 inherits ThingParent {
  func() : Int {
    foo()
  };
};

class Thing2 inherits Thing1 {
  func() : Int {
    bar()
  };
};
