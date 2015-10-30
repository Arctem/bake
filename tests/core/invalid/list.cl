class Main {
  main(): Cons{
      (new Cons).init(1,new Nil)
  };
};

class Cons inherits List {
  xcar : Int;
  xcdr : List;
  isNil() : Bool { false };
  init(hd : Int, tl : List) : Cons {
    {
      xcar <- hd;
      xcdr <- tl;
      self;
    }

 };
 };

 class List inherits Nil{

 };

 class Nil {} ;
