class Main inherits IO {
  main() : Object {
    3
  };
};

class ThingParent {
  foo(x : Int, y : String) : Int {
    4
  };
};

class Thing1 inherits ThingParent {
  func() : Int {
    foo("hi", 1)
  };
};
