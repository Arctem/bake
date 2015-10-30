class Main {
  a : Int64 <- ConvertInt64(2147483647);
  b : Int8 <- ConvertInt8(90);
  x : Int;

  main() : Object{{
    x <- ConvertInt(a);
    x <- ConvertIn32(a);
    x <- ConvertInt(b);
    x <- CovertInt32(b);
  }};
};
