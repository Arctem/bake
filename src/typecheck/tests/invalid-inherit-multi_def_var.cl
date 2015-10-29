class Main inherits IO {
  main() : Object {
    out_string("Hi World!\n")
  };
};

class ThingParent {
  y : Int <- 4;
};

class Thing1 inherits ThingParent {
  z : Int <- 4;
  func() : Int {
    foo()
  };
};

class Thing2 inherits Thing1 {
  y : Int <- 4;
};