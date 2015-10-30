class Main inherits IO {
  main() : Object {
    out_string("Hi World!\n")
  };
};

class ThingParent {
  x : Int <- 4;

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


  foo() : String {
    {
      let x : Int <- 3 in {
        4;
      };
    }
  };
};