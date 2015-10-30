class Main inherits IO {

  s : Susie; 
  
  main() : Object {
      "hello"
  };
};

class Bob inherits Susie {
  test1() : Object {
      1+1
  };
};

class Susie inherits Object {
   a : Bob ;
   
};
