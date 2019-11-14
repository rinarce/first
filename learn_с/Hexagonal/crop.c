#include <stdio.h>
#include <math.h>
int main(){int s,d,q=0,r=0;char c;
scanf("%d\n",&s);
while(s--){scanf("%c %d\n", &c,&d);if(c=='X')r-=d;if(c=='Y'){q+=d;r-=d;}if(c=='Z')q+=d;}
printf("%d",(abs(q)+abs(q+r)+abs(r))/2);}