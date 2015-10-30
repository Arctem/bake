class Main inherits IO {
  a : A;
  main() : Object {
    out_string("Hi!\n")
  };
};

class A inherits B {
};

class B inherits C {
};

class C inherits A {
};
