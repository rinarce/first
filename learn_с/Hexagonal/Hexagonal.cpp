// Hexagonal.c

#include <stdio.h>
//#include <math.h>

// https://acmp.ru/index.asp?main=task&id_task=256

// идеи https://www.redblobgames.com/grids/hexagons/

#define INPUT_FILE   "INPUT.TXT"
#define OUTPUT_FILE "OUTPUT.TXT"

#pragma warning(disable:4996)   // for use scanf in VisualStudio


int main() {
  FILE* inp_file;
  FILE* out_file;
  // int error;

  int num_steps, delta, dist;
  char coord;
  int q = 0 , r = 0;
  
  if (NULL == (inp_file =  fopen(INPUT_FILE, "r")))    return 1;
  if (NULL == (out_file = fopen(OUTPUT_FILE, "w")))    return 2;
  
  fscanf_s(inp_file, "%d\n", &num_steps);
  while (num_steps--) {
    fscanf(inp_file, "%c %d\n", &coord, &delta);
    
    if      (coord == 'X') {  r -= delta;   }
    else if (coord == 'Y') {  q += delta;  r -= delta; }
    else if (coord == 'Z') {  q += delta;   }

//    printf("coord %c %d >>> r=%d q=%d\n", coord, delta, r, q);
  }
  
  
  dist = (abs(q) + abs(q + r) + abs(r)) / 2;


  fprintf(out_file, "%d", dist);
  
  fclose(inp_file);
  fclose(out_file);

  return 0;
}

/*
#include <stdio.h>
#include <math.h>

int main(){
int s,d,q=0,r=0;char c;
scanf("%d\n",&s);

while(s--)
{scanf("%c %d\n", &c,&d);
if(c=='X')r-=d;
if(c=='Y'){q+=d;r-=d;}
if(c=='Z')q+=d;}

printf("%d",(abs(q)+abs(q+r)+abs(r))/2);}
*/
