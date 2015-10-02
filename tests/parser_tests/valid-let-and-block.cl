class Test {
  test1() : Object {

    {
      let d : String in d <- a;

      let b : String, d : String in b <- d;
    }

  };

  test2() : Object {

    {
      let b : String, d : String in
      b <- d;

      let d : String
      in d <- a;
    }
  };

  test3() : Object {

    {
      let d : String <- "hello" in
      d <- a;

      let b : String <- "hello", d : String <-"world" in
      b <- d;
    }
  };

  test4() : Object {

    {
      let b : String <- "hello", d : String <- "world" in
      b <- d;

      let d : String <- "hello" in
      d <- a;
    }
  };

  test5() : Object {

    {
      let b : String <- "hello", d : String in
      b <- d;
    }
  };

  test5() : Object {

     {
        let b : String, d : String <- "world" in
        b <- d;

      }
  };

};
