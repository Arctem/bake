class Main {
  a : Int <- 2;
  b : Int <- 2;

  main() : Object {{
    add(1 , b);

  }};

  add(x : Int, y : Int) : Int {{
     a <- 1 + 2;
     b <- x + y;
     x <- a + b;
  }};
};
