#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long sum_divisors(long long n){
  long long sum = 1;
  for (long long i = 2; i * i <= n; i++){
    if(n % i == 0){
      sum += i + (n / i);
    }
  }
  return sum;
}

int main(void){
  int t;
  scanf("%d", &t);
  while (t--){
    long long n;
    scanf("%lld", &n);
    printf("%lld\n", sum_divisors(n));
  }
  return 0;
}
