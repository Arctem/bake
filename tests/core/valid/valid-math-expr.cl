class Test {
  test1() : Object {
      {
          isvoid a;
          a + a;
          b - b;
          c * c;
          d / d;
          ~f;

          a <- a + b - c * d / ~f;
          a <- ~f / d * c - b + a; 
      }
  };
};
