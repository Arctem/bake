class Main inherits Loops{
  main() : Int {{
     if(loops())
     then 1
     else 2
     fi;
  }};
};

class Loops{
  x : Object;
  a : String;
  b : Bool;

  loops() : Bool {{
    x <- while not true
         loop a.concat("hello")
         pool;

    b <- isvoid x;
    not b;
  }};

};
