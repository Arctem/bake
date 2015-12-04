class Main inherits IO {
  x : Bool <- true;

  main() : Object {
    while x loop
      x <- false
    pool
  };
};
