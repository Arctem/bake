class Main inherits IO {
  a : Int;

  main() : Object {
    let b : Int8, c : Int64 <- 15, d : Float <- 5.2, e : SELF_TYPE in 
    {
      a + b;
      b - c;
      d * a;
      d / b;
      b + b;
      e <- self;
      1;
    }
  };
};