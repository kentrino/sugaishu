int power(int x, unsigned int y, int p)
{
  int res = 1;
  x = x % p;
  while (y > 0)
  {
    if (y & 1)
      res = (res * x) % p;

    y = y >> 1;
    x = (x * x) % p;
  }
  return res;
}

bool millerTest(int d, int n)
{
  return false;
}

int isPrime(int n)
{
  return n * 3;
}
