#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int int_comp(const void *a, const void *b);
void merge(void *out, const void *pa, size_t na, const void *pb,
           size_t nb, size_t elem_size, int (*cmp)(const void *, const void *));

void merge_sort(void *base, size_t n_memb, size_t elem_size,
                int (*cmp)(const void *, const void *));

void print_arr(int* arr, int n);

int main()
{
    
  int arr[] = {25, 23, 17, 29, 7, 16, 33, 21};


  merge_sort(arr, 8, sizeof(int), int_comp);

  print_arr(arr, 8);
    
  return 0;
}


/* Subroutine to merge two input arrays into an output array. */
void merge(void *out, const void *pa, size_t na, const void *pb,
           size_t nb, size_t elem_size, int (*cmp)(const void *, const void *))
{
  while (na != 0 || nb != 0)
  {
    if (na == 0 || (nb != 0 && cmp(pa, pb) > 0))
    {
      memcpy(out, pb, elem_size);
      pb = (const char *)pb + elem_size;
      nb--;
    }
    else
    {
      memcpy(out, pa, elem_size);
      pa = (const char *)pa + elem_size;
      na--;
    }
    out = (char *)out + elem_size;
  }
}

/* Merge sort an array. Function modified from*/
void merge_sort(void *base, size_t n_memb, size_t elem_size,
                int (*cmp)(const void *, const void *))
{
  size_t n_bottom;
  size_t n_top;
  void *mid_p;
  void *bottom;
  void *top;

  //print_arr(base, n_memb);
  

  if (n_memb <= 1)
  {
    /* Too small to sort. */
    return;
  }
  /* Sort the bottom half and the top half. */
  n_bottom = n_memb / 2;
  n_top = n_memb - n_bottom;
  mid_p = (char *)base + (n_bottom * elem_size);
  merge_sort(base, n_bottom, elem_size, cmp);
  merge_sort(mid_p, n_top, elem_size, cmp);
  /* Make temporary copies of the sorted bottom half and top half. */
  bottom = malloc(n_bottom * elem_size);
  top = malloc(n_top * elem_size);
  memcpy(bottom, base, n_bottom * elem_size);
  memcpy(top, mid_p, n_top * elem_size);
  /* Do a sorted merge of the copies into the original. */
  merge(base, bottom, n_bottom, top, n_top, elem_size, cmp);
  /* Free temporary copies. */
  free(bottom);
  free(top);
}

/* Compares the s data for merge sort */
int int_comp(const void *a, const void *b)
{
  int val1 = *(int*)a;
  int val2 = *(int*)b;


  return ( val1 - val2 ); 
}


void print_arr(int* arr, int n)
{

  for(int i = 0 ; i< n; i++)
  {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}