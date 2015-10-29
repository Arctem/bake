class Main inherits IO{
  x : Int;
  main() : Object{{
     x <- (case(true) of
            b: Bool => 1;
            o: Object => 10;
           esac
          ) + ( case (new B) of
            a : A => case(false) of bool: Bool => 1000; esac;
            o : Object => 200;
            esac
          );

     x <- if(case(out_string("hello\n")) of
            i : IO => true; esac )
          then
            {44; 22;}
          else
            33
          fi + x;
      out_int(x);
  }};
};

class A {

};

class B inherits A {

};
