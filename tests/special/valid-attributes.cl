class Main inherits IO {
  x : Int32 <- 34;
  y : Bool <- true;
  z : Float <- 34;

  bar(k : Float, z : Bool) : Int {{
    let a : Float, z : Int64 <- 12, c : Float in {
      a <- k + let a : Int in { 4; };
    };
  }};

  main() : Object {
    {
      out_string("Hi World!\n");
    }
  };

  foo(k : Float) : Int {{
    4 + 4;
  }};
};

class Baz inherits Main {
  bar(k : Float, z : Bool) : Int {{
    out_string("Baz\n");
  }};
};