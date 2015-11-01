class Main inherits IO {
  main() : Object {
    out_string("Hi World!\n")
  };
};

class ThingParent {
  foo() : String {
    4
  };
};

class Twiddledee inherits ThingParent {

};

class Thing1 {
  func(x : Twiddledee) : Int {
    x@ThingParent.foo()
  };
};
