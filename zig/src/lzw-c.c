
struct singly_linked_list {
  struct singly_linked_list *next;
  int data;
};

void insert_append(struct singly_linked_list *anchor,
                   struct singly_linked_list *newlink) {
  newlink->next = anchor->next;
  anchor->next = newlink;
}


typedef struct elem {
  int data;
  struct elem *next;
} cell;

typedef cell *list;
void* malloc(unsigned long size);
void free(void *ptr);
#define NULL 0
int printf(const char *format, ...);
int scanf(const char* restrict format, ...);
int atoi(const char *str);

list addToList(list a, int num) {

  list iter, temp;
  int i = 0;

  if (a == NULL) {
    a = (list)malloc(sizeof(cell));
    a->data = num;
    a->next = NULL;
  } else {
    iter = a;

    while (iter->next != NULL) {
      iter = iter->next;
    }

    temp = (list)malloc(sizeof(cell));
    temp->data = num;
    temp->next = NULL;

    iter->next = temp;
  }
  return a;
}

list deleteFromList(list a, int pos) {

  int i = 1;
  list temp, iter;

  if (a != NULL) {
    iter = a;

    if (pos == 1) {
      a = a->next;
      iter->next = NULL;
      free(iter);
    }

    else {
      while (i++ != pos - 1)
        iter = iter->next;
      temp = iter->next;
      iter->next = temp->next;
      temp->next = NULL;
      free(temp);
    }
  }
  return a;
}

void printList(list a) {
  list temp = a;

  printf("List contains following elements : \n");

  while (temp != NULL) {
    printf("%d ", temp->data);
    temp = temp->next;
  }
}

int main(int argC, char *argV[]) {
  list a = NULL;
  int i;

  if (argC == 1)
    printf("Usage : %s <list of integers to be inserted into the list>",
           argV[0]);
  else {
    for (i = 2; i <= argC; i++)
      a = addToList(a, atoi(argV[i - 1]));

    printList(a);

    do {
      printf("\nEnter position of element to be removed (1-%d) : ", argC - 1);

      scanf("%d", &i);

      if (i > 0 && i <= argC - 1) {
        a = deleteFromList(a, i);
        printList(a);
      }
    } while (i > argC - 1 || i <= 0);
  }
  return 0;
}