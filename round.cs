namespace Round
{
  class Round
  {
    public static double TruncateTowardZero(double x) => Math.Truncate(x);

    public static double TruncateAwayFromZero(double x)
    {
      return Math.Sign(x) == 1 ? Math.Ceiling(x) : Math.Floor(x);
    }
    public static double TruncateDown(double x) => Math.Floor(x);
    public static double TruncateUp(double x) => Math.Ceiling(x);

    public static double RoundToZero(double x)
    {
      return Math.Round(x - (Math.Sign(x) * 1E-15 ),MidpointRounding.AwayFromZero);
    }

    public static double RoundAwayFromZero(double x) => Math.Round(x, MidpointRounding.AwayFromZero);

    public static double RoundDownward(double x)
    {
      return Math.Sign(x) == 1 ? RoundToZero(x) : Math.Round(x,MidpointRounding.AwayFromZero);
    }

    public static double RoundUpward(double x)
    {
      return Math.Sign(x) == 1 ? Math.Round(x,MidpointRounding.AwayFromZero) : RoundToZero(x);
    }

    public static double RoundToEven(double x) => Math.Round(x, MidpointRounding.ToEven);

    public static double RoundToOdd(double x)
    {
      return Math.Round(x + 1, MidpointRounding.ToEven) - 1;
    }
  }
}
