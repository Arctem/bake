class Main {
  a : Int64 <- (new Convert).toInt64(2147483647);
  b : Int8 <- (new Convert).toInt8(90);
  x : Int;

  main() : Object{{
    x <- (new Convert).toInt(a);
    x <- (new Convert).toInt32(a);
    x <- (new Convert).toInt(b);
    x <- (new Convert).toInt32(b);
  }};
};
