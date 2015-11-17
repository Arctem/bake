class Main inherits IO {
  x : Int32 <- 34;
  y : Bool <- true;
  z : Float <- 34;

  main() : Object {
    {
      let a : Int64, b : Int64 <- 12, c : Float in {
        a <- b + let a : Int in { 4; };
      };
      out_string("Hi World!\n");
    }
  };
};