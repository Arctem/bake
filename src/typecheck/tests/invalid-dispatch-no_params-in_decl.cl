class Main inherits IO {
  main() : Object {
    3
  };
};

class ThingParent {
  foo() : Int {
    4
  };
};

class Thing1 inherits ThingParent {
  func() : Int {
    foo(4)
  };
};
