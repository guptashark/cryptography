#include "jumbo_num.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define PFX_02_BIGNUM_DEFAULT_CAPACITY 8

struct pfx_02_jumbo_num {
  int *n;
  size_t capacity;
  size_t size;
};

struct pfx_02_jumbo_num *
pfx_02_jumbo_num_new(void) {
  struct pfx_02_jumbo_num *jn = malloc(sizeof(struct pfx_02_jumbo_num));
  if (jn == NULL) {
    // log an error.
    return NULL;
  }

  jn->capacity = PFX_02_BIGNUM_DEFAULT_CAPACITY;
  jn->n = malloc(sizeof(int) * jn->capacity);
  if (jn->n == NULL) {
    // log an error.
    free(jn);
    return NULL;
  }

  jn->size = 0;

  return jn;
}

int pfx_02_jumbo_num_init
(struct pfx_02_jumbo_num *jn, int n) {

  int i = 0;
  while (n > 0) {
    int d = n % 10;
    n /= 10;

    jn->n[i] = d;
    i++;
  }

  jn->size = i;

  return 0;
}

int pfx_02_jumbo_num_init_one
(struct pfx_02_jumbo_num *jn) {
  return pfx_02_jumbo_num_init(jn, 1);
}

int pfx_02_jumbo_num_init_zero
(struct pfx_02_jumbo_num *jn) {
  return pfx_02_jumbo_num_init(jn, 0);
}

int pfx_02_jumbo_num_add
(
  struct pfx_02_jumbo_num *jn_01,
  struct pfx_02_jumbo_num *jn_02,
  struct pfx_02_jumbo_num *jn_03
) {

  // Assume that we don't need to add capacity.
  size_t size = 0;
  if (jn_02->size > jn_03->size) {
    size = jn_02->size;
  } else {
    size = jn_03->size;
  }

  int carry = 0;

  for (size_t i = 0; i < size; ++i) {
    int d = jn_02->n[i] + jn_03->n[i] + carry;
    carry = 0;
    if (d > 9) carry = 1;
    d %= 10;

    jn_01->n[i] = d;
  }

  if (carry == 1) {
    jn_01->n[size] = 1;
    jn_01->size = size + 1;
  } else {
    jn_01->size = size;
  }

  return 0;
}

int pfx_02_jumbo_num_mult
(struct pfx_02_jumbo_num *jn_01, struct pfx_02_jumbo_num *jn_02) {
  (void)jn_01;
  (void)jn_02;
  return 0;
}

bool pfx_02_jumbo_num_eq
(struct pfx_02_jumbo_num *jn_01, struct pfx_02_jumbo_num *jn_02) {

  bool matching = true;
  if (jn_01->size != jn_02->size) matching = false;

  size_t i = 0;
  while (i < jn_01->size && matching) {
    if (jn_01->n[i] != jn_02->n[i]) matching = false;
    i++;
  }

  return matching;
}

bool pfx_02_jumbo_num_neq
(struct pfx_02_jumbo_num *jn_01, struct pfx_02_jumbo_num *jn_02) {
  return !pfx_02_jumbo_num_eq(jn_01, jn_02);
}

void pfx_02_jumbo_num_print
(struct pfx_02_jumbo_num *jn) {
  for (size_t i = jn->size; i > 0; --i) printf("%d", jn->n[i - 1]);
  printf("\n");
}

void pfx_02_jumbo_num_free
(struct pfx_02_jumbo_num *jn) {
  free(jn);
}
