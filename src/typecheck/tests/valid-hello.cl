class Main inherits IO {
  x : Int <- 34;

  main() : Object {
    {
      let a : Int, b : Int <- 12, c : Float in {
        a <- b + let a : Int in { 4; };
      };
      out_string("Hi World!\n");
    }
  };
};

class Thing inherits IO {
  main() : Object {
    out_string("Hello, world!\n")
  };

  func(a : Int, b : Float) : Int {
    a
  };
};
