class Main inherits IO {
  main() : Object {
    out_string("Hi World!\n")
  };

  foo() : String {
    4
  };
};

class ThingParent {
  
};

class Twiddledee inherits ThingParent {
  foo() : String {
    4
  };
};

class Thing1 {
  func(x : Twiddledee) : Int {
    x@ThingParent.foo()
  };
};
