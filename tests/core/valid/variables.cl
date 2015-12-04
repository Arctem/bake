class Main {
  a : Int <- 2;
  b : Int <- 2;

  main() : Object {
    func(1 , b)
  };

  func(x : Int, y : Int) : Int {
      let c : Int <- 0 in {
          a;
          b;
          x;
          y;
          c;

      }
  };
};
