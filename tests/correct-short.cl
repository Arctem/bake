class Main inherits IO {
  main() : Object {
    out_string("Hello, world!\n")

    Int int <- 0;

    if(int = 2)
      int <- 10.0;
    else
      int <- 1;
    fi

    while(true)
    loop
      int <- int + int;
    pool

  };
};
