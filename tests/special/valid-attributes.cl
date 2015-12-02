class Main inherits IO {
  x : Int32 <- 34;
  y : Bool <- true;

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

  z : Float <- 34;

  foo(k : Float) : Int {{
    4 + 4;
  }};
};

class Baz inherits Main {
  antiZombieSquad : String;

  bar(k : Float, z : Bool) : Int {{

    let theZombie : Int in { 4; };

    out_string("Baz\n");
    4;
  }};
};

class ATaleOfAMouseAndAClock {
  baz : Baz <- new Baz;
  story : String <- "The mouse ran up the clock\n";

  bar(j : Bool) : String {{
    story;
  }};
};