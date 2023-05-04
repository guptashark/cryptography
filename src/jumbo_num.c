#include "jumbo_num.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define PFX_02_BIGNUM_DEFAULT_CAPACITY 8

// TODO: Add in error cases...
// Ie, what happens if string is too big?
// What error codes to return?
static size_t pfx_02_strlen_safe(char *s, size_t n) {
  (void)n;
  size_t i = 0;
  while (s[i] != '\0') i++;
  return i;
}

struct pfx_02_jumbo_num {
  int *n;
  int8_t sign;
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

// TODO: Currently we just assume that this works, when the malloc
// might actually fail. Testable by creating a custom allocator.
static int pfx_02_jumbo_num_reserve
(
  struct pfx_02_jumbo_num *jn,
  size_t capacity
) {
  if (jn->capacity >= capacity) {
    // Uhh, should we do a goto?
    return 0;
  }

  jn->capacity = capacity;
  int *m = malloc(sizeof(int) * jn->capacity);

  for (size_t i = 0; i < jn->capacity; ++i) m[i] = jn->n[i];
  free(jn->n);
  jn->n = m;

  return 0;
}

int pfx_02_jumbo_num_init
(struct pfx_02_jumbo_num *jn, int n) {

  // TODO: Can we do Single Entry Single Exit? (SESE)
  if (n == 0) {
    jn->size = 1;
    jn->n[0] = 0;
    jn->sign = 1;
    return 0;
  }

  if (n > 0) {
    jn->sign = 1;
  } else {
    jn->sign = -1;
    n *= -1;
  }

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

int pfx_02_jumbo_num_init_str
(struct pfx_02_jumbo_num *jn, char *s) {

  // TODO Need to actually parse the string to check for negative.
  // For now, assume it's a positive number.
  jn->sign = 1;

  // TODO: Is this possibly dangerous?
  // Maybe have a limit on the size of s, for bn apps?
  // TODO: Pick a limit vs just 64.
  size_t s_len = pfx_02_strlen_safe(s, 64);

  // TODO: Reserve by multiples of 8.
  pfx_02_jumbo_num_reserve(jn, s_len);
  for (size_t i = 0; i < s_len; ++i) {
    jn->n[i] = s[s_len - i - 1] - '0';
  }

  jn->size = s_len;

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

int pfx_02_jumbo_num_copy
(
  struct pfx_02_jumbo_num *jn_dst,
  struct pfx_02_jumbo_num *jn_src
) {

  // For now, the rule is that size can be the same as capacity
  if (jn_dst->capacity < jn_src->size) {
    pfx_02_jumbo_num_reserve(jn_dst, jn_src->size);
  }

  for (size_t i = 0; i < jn_src->size; ++i) jn_dst->n[i] = jn_src->n[i];
  jn_dst->size = jn_src->size;
  jn_dst->sign = jn_src->sign;
  return 0;
}

int pfx_02_jumbo_num_add
(
  struct pfx_02_jumbo_num *jn_01,
  struct pfx_02_jumbo_num *jn_02,
  struct pfx_02_jumbo_num *jn_03
) {

  size_t size = 0;
  if (jn_02->size > jn_03->size) {
    size = jn_02->size;
  } else {
    size = jn_03->size;
  }

  // TODO: Reserve by multiples of 8...
  pfx_02_jumbo_num_reserve(jn_01, size + 1);

  int carry = 0;

  for (size_t i = 0; i < size; ++i) {
    int d = 0;

    if (i < jn_02->size) d += jn_02->n[i];
    if (i < jn_03->size) d += jn_03->n[i];
    d += carry;

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

  jn_01->sign = 1;

  return 0;
}

int pfx_02_jumbo_num_mult
(
  struct pfx_02_jumbo_num *jn_01,
  struct pfx_02_jumbo_num *jn_02,
  struct pfx_02_jumbo_num *jn_03
) {

  // If either number is zero, we can shortcut.
  // Would be nice to do Single Entry Single Exit.
  if (pfx_02_jumbo_num_eq_zero(jn_02) || pfx_02_jumbo_num_eq_zero(jn_03)) {
    pfx_02_jumbo_num_init_zero(jn_01);
    return 0;
  }

  pfx_02_jumbo_num_reserve(jn_01, jn_02->size + jn_03->size);

  // Special case where we have to zero out the memory.
  for (size_t i = 0; i < jn_02->size + jn_03->size; ++i) jn_01->n[i] = 0;

  for (size_t i = 0; i < jn_02->size; ++i) {
    for (size_t j = 0; j < jn_03->size; ++j) {
      jn_01->n[i + j] += jn_02->n[i] * jn_03->n[j];
    }
  }

  // Now take care of overflows.
  int carry = 0;

  for (size_t i = 0; i < jn_02->size + jn_03->size; ++i) {
    int d = (jn_01->n[i] + carry) % 10;
    carry = (jn_01->n[i] + carry) / 10;
    jn_01->n[i] = d;
  }

  if (jn_01->n[jn_02->size + jn_03->size - 1] == 0) {
    jn_01->size = jn_02->size + jn_03->size - 1;
  } else {
    jn_01->size = jn_02->size + jn_03->size;
  }

  jn_01->sign = 1;

  return 0;
}

int pfx_02_jumbo_num_subt
(
  struct pfx_02_jumbo_num *jn_01,
  struct pfx_02_jumbo_num *jn_02,
  struct pfx_02_jumbo_num *jn_03
) {

  // For now, assume the following:
  //  * jn_02.size == jn_03.size
  //  * jn_02 > jn_03
  //  * jn_02->n[i] > jn_03->n[i]

  pfx_02_jumbo_num_reserve(jn_01, jn_02->size);
  for (size_t i = 0; i < jn_02->size; ++i) {
    jn_01->n[i] = jn_02->n[i] - jn_03->n[i];
  }

  jn_01->size = jn_02->size;

  return 0;
}

bool pfx_02_jumbo_num_eq
(struct pfx_02_jumbo_num *jn_01, struct pfx_02_jumbo_num *jn_02) {

  bool matching = true;
  if (jn_01->size != jn_02->size) matching = false;
  if (jn_01->sign != jn_02->sign) matching = false;

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

bool pfx_02_jumbo_num_eq_zero
(struct pfx_02_jumbo_num *jn) {
  if (jn->size == 1 && jn->n[0] == 0) {
    return true;
  } else {
    return false;
  }
}

bool pfx_02_jumbo_num_gt
(
  struct pfx_02_jumbo_num *jn_01,
  struct pfx_02_jumbo_num *jn_02
) {
  // TODO Implement for when the numbers have signs.
  if (jn_01->size < jn_02->size) return false;
  if (jn_01->size > jn_02->size) return true;

  size_t i = jn_01->size;

  int diff = 0;
  while (i > 0 && diff == 0) {
    diff = jn_01->n[i] - jn_02->n[i];
    i--;
  }

  if (diff > 0) {
    return true;
  } else {
    return false;
  }
}

void pfx_02_jumbo_num_print
(struct pfx_02_jumbo_num *jn) {
  if (jn->sign == -1) printf("-");
  for (size_t i = jn->size; i > 0; --i) printf("%d", jn->n[i - 1]);
  printf("\n");
}

void pfx_02_jumbo_num_free
(struct pfx_02_jumbo_num *jn) {
  free(jn);
}
