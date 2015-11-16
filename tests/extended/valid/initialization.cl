class Main {
  a : Int64 <- Convert.toInt64(2147483647);
  b : Int8 <- Convert.toInt8(90);
  x : Int;

  main() : Object{{
    x <- Convert.toInt(a);
    x <- Convert.toInt32(a);
    x <- Convert.toInt(b);
    x <- Convert.toInt32(b);
  }};
};
