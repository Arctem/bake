class Main inherits IO{
  b : B <- new B;
  main() : Object{
    case (b <- new C) of
      c : C => out_string("c");
      d : B => {
        b = d;
        out_string("b");
      };
      a : A => out_string("a");
      o : Object => out_string("Object");
    esac

  };
};

class A {

};

class B inherits A {

};

class C inherits B {

};
