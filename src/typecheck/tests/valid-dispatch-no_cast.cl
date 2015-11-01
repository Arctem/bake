class Main inherits IO {
  main() : Object {
    out_string("Hi World!\n")
  };

  foo() : Int {
    4
  };
};

class ThingParent inherits Main {
  
};

class Thing1 inherits ThingParent {
  func() : Int {
    foo()
  };
};
