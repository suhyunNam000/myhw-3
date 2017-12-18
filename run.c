#include <sys/types.h>
#include <limits.h>

#include "run.h"
#include "util.h"

void *base = 0;

p_meta head = 0;
p_meta tail = 0;

p_meta find_meta(p_meta *last, size_t size) {
  p_meta index = base;
  p_meta result = base;

  switch(fit_flag){
    case FIRST_FIT:
    {
      if((*last) == 0) {  return 0; }  //if no metadata

      index = (*last)->prev;

      while(index) {
        if((index->free == 0) || (index->size < size)) {
          index = index->prev;
        } else {
          result = index;
          break;
        }
      }

    }
    break;

    case BEST_FIT:
    {
      if((*last) == 0) {  return 0; }


    }
    break;

    case WORST_FIT:
    {
      //WORST_FIT CODE
    }
    break;

  }
  return result;
}

void *m_malloc(size_t size) {
  p_meta new = base;
  p_meta prev = base;
  p_meta next = base;
  p_meta temp = base;

  if(new = find_meta(&tail, size)) {
    if((new->size) > (size + META_SIZE)) {
      next = new->next;
      temp->next = next;
      temp->prev = new;
      temp->size = (new->size) - META_SIZE;
      temp->free = 1;
      new->next = temp;
      next->prev = temp;

    }
    (new->free) = 0;
    return (new + META_SIZE);
  } else  {
    new = sbrk(META_SIZE);
    sbrk(size);

    temp = tail->prev;
    tail = sbrk(0);

    new->prev = temp;
    new->next = tail;
    temp->next = new;
    tail->prev = new;
    new->size = size;
    new->free = 0;
    return (new+META_SIZE);
  }
}

void m_free(void *ptr) {
  p_meta remov = base;
  p_meta prev = base;
  p_meta next = base;
  
  remov->prev = ptr;
  	  
  remov->next = tail;
  remov->free = 1;
}

void*
m_realloc(void* ptr, size_t size)
{

}
