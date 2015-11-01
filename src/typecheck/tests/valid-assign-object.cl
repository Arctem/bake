class Main inherits IO {
  main() : Object {
    out_string("Hi World!\n")
  };
};

class Thing1 {

};

class Thing2 inherits Thing1 {
  
};

class Thing3 inherits Thing2 {
  
};

class Twiddledum {
  z : Thing1;

  foo(x : Thing3) : Thing1 {
    z <- x
  };
};