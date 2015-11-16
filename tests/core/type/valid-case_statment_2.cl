class Main inherits IO{
  b : B <- new B;
  f : IO;
  main() : Object{
    f <- case (b <- new C) of
      i : Int => out_string("int");
      c : C => case (true) of
              bol: Bool => out_string("bool");
              asdf: C => asdf;
              esac;
      d : B => out_string("b");
      a : A => out_string("a");
      o : Object => out_string("Object");
    esac

  };
};

class A {

};

class B inherits A{


};

class C inherits B{

};
