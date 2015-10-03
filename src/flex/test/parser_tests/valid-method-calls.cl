class Test {
  test1() : Object {

    "string".c()
    "string".c(d)
    "string".c(d, c <- 1)

    "string"@Object.c()
    "string"@Object.c(d)
    "string"@Object.c(d, c <- 1)

    .c()
    .c(d)
    .c(d, c <- 1)
  };
};
