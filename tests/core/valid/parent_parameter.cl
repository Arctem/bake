class Main {
  main() : Object {
    func(new B, new B)
  };

  func(x : A, y : A) : A {
    x
  };
};

class A {
};

class B inherits A {
};