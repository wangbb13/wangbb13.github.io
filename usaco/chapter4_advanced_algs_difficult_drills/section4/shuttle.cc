#include <stdio.h>

#define MAXS 32

int size;  /* `size' of board, in terms of number of black marbles */
int bsize; /* real size of board, in terms of holes */
int eloc;  /* location of empty hole */

FILE *fout, *fin;

void outmove(int i)
 {
  static int mcnt = 0;
  if (i == -1) /* possible newline needed at the end */
   {
    if (mcnt) fprintf (fout, "\n");
    return;
   }

  eloc = i;
  fprintf (fout, "%i", i+1); /* output the answer */
  /* handle spacing and newlines */
  if (++mcnt < 20) fprintf (fout, " ");
  else
   { 
    fprintf (fout, "\n");
    mcnt = 0;
   }
 }

int main(int argc, char **argv)
 {
  int lv, lv2;

  if ((fin = fopen("shuttle.in", "r")) == NULL)
   {
    perror ("fopen fin");
    exit(1);
   }
  if ((fout = fopen("shuttle.out", "w")) == NULL)
   {
    perror ("fopen fout");
    exit(1);
   }

  fscanf (fin, "%d", &size);

  eloc = size;
  bsize = 2*size+1;

  /* expansion phase of pattern */
  for (lv = 0; lv <= size; lv++)
   {
    if (lv % 2 == 0) /* even moves left */
     {
      for (lv2 = 0; lv2 < lv; lv2++)
        outmove(eloc-2);
      /* expand by one step */
      if (eloc-1 >= 0) outmove(eloc-1);
     } else { /* odd moves right */
      for (lv2 = 0; lv2 < lv; lv2++)
        outmove(eloc+2);
      /* expand by one step */
      if (eloc+1 < bsize) outmove(eloc+1);
     }
   }

  /* contraction phase of pattern */
  for (lv = size-1; lv >= 0; lv--)
   {
    if (eloc < size) /* if eloc is to left of center, move right */
     {
      outmove(eloc+1); /* contract by one step */
      for (lv2 = 0; lv2 < lv; lv2++)
        outmove(eloc+2);
     } else { /* if eloc is to the right of center, move left */
      outmove(eloc-1); /* contract by one step */
      for (lv2 = 0; lv2 < lv; lv2++)
        outmove(eloc-2);
     }
   }
  outmove(-1); /* clean-up newlines */
  return 0;
 }
