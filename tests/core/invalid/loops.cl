class Main inherits Loops{
  main() : Int {{
     if(loops())
     then 1
     else 2
     fi;
  }};
};

class Loops{
  x : Int;
  a : String;
  b : Bool;

  loops() : Bool {{
    x <- while false
         loop a.concat("a")
         pool;

    b <- isvoid x;
  }};

};
