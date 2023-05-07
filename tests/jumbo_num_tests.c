#include "jumbo_num.h"

#include <assert.h>
#include <stdio.h>

static int fn_add(int a, int b) { return a + b; }
static int fn_subt(int a, int b) { return a - b; }
static int fn_mult(int a, int b) { return a * b; }

static void test_binary_op
(
  int (*f)(int, int),
  int (*jn_fn)(
    struct pfx_02_jumbo_num *,
    struct pfx_02_jumbo_num *,
    struct pfx_02_jumbo_num *),
  int a,
  int b
) {
  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_02 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_03 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_04 = pfx_02_jumbo_num_new();

  pfx_02_jumbo_num_init(jn_01, 0);
  pfx_02_jumbo_num_init(jn_02, a);
  pfx_02_jumbo_num_init(jn_03, b);
  pfx_02_jumbo_num_init(jn_04, f(a, b));

  jn_fn(jn_01, jn_02, jn_03);
  assert(pfx_02_jumbo_num_eq(jn_01, jn_04));

  pfx_02_jumbo_num_free(jn_01);
  pfx_02_jumbo_num_free(jn_02);
  pfx_02_jumbo_num_free(jn_03);
  pfx_02_jumbo_num_free(jn_04);
}

// This function can't be abstracted away like the others right now.
static void test_add_str(char *a, char *b, char *expected) {
  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_02 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_03 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_04 = pfx_02_jumbo_num_new();

  pfx_02_jumbo_num_init(jn_01, 0);
  pfx_02_jumbo_num_init_str(jn_02, a);
  pfx_02_jumbo_num_init_str(jn_03, b);
  pfx_02_jumbo_num_init_str(jn_04, expected);

  pfx_02_jumbo_num_add(jn_01, jn_02, jn_03);
  assert(pfx_02_jumbo_num_eq(jn_01, jn_04));

  pfx_02_jumbo_num_free(jn_01);
  pfx_02_jumbo_num_free(jn_02);
  pfx_02_jumbo_num_free(jn_03);
  pfx_02_jumbo_num_free(jn_04);
}

static bool fn_eq(int a, int b) { return a == b; }
static bool fn_neq(int a, int b) { return a != b; }
static bool fn_gt(int a, int b) { return a > b; }
static bool fn_lt(int a, int b) { return a < b; }
static bool fn_geq(int a, int b) { return a >= b; }
static bool fn_leq(int a, int b) { return a <= b; }

static void test_relation
(
  bool (*f)(int, int),
  bool (*jn_f)(struct pfx_02_jumbo_num *, struct pfx_02_jumbo_num *),
  int a,
  int b
) {
  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_02 = pfx_02_jumbo_num_new();

  pfx_02_jumbo_num_init(jn_01, a);
  pfx_02_jumbo_num_init(jn_02, b);

  bool expected = f(a, b);
  bool actual = jn_f(jn_01, jn_02);
  assert(expected == actual);

  pfx_02_jumbo_num_free(jn_01);
  pfx_02_jumbo_num_free(jn_02);
}

static void test_copy(void) {
  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_02 = pfx_02_jumbo_num_new();

  pfx_02_jumbo_num_init(jn_01, 0);
  pfx_02_jumbo_num_init(jn_02, 345);

  assert(pfx_02_jumbo_num_neq(jn_01, jn_02));

  pfx_02_jumbo_num_copy(jn_01, jn_02);

  assert(pfx_02_jumbo_num_eq(jn_01, jn_02));

  pfx_02_jumbo_num_free(jn_01);
  pfx_02_jumbo_num_free(jn_02);
}

static void test_print(int n) {
  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  pfx_02_jumbo_num_init(jn_01, n);
  pfx_02_jumbo_num_print(jn_01);
  pfx_02_jumbo_num_free(jn_01);
}

int main(void) {

  test_copy();

  test_add_str("123", "456", "579");
  test_add_str("250", "251", "501");
  test_add_str("1", "100", "101");
  test_add_str("1", "899", "900");
  test_add_str("1",
      "999999999999999999999999999999999999999999999999999999",
      "1000000000000000000000000000000000000000000000000000000");

  for (int i = -100; i < 100; ++i) {
    for (int j = -100; j < 100; ++j) {
      test_relation(fn_eq, pfx_02_jumbo_num_eq, i, j);
      test_relation(fn_neq, pfx_02_jumbo_num_neq, i, j);
      test_relation(fn_gt, pfx_02_jumbo_num_gt, i, j);
      test_relation(fn_lt, pfx_02_jumbo_num_lt, i, j);
      test_relation(fn_geq, pfx_02_jumbo_num_geq, i, j);
      test_relation(fn_leq, pfx_02_jumbo_num_leq, i, j);
    }
  }

  for (int i = 0; i < 300; ++i) {
    for (int j = 0; j < 300; ++j) {
      test_binary_op(fn_add, pfx_02_jumbo_num_add, i, j);
      test_binary_op(fn_mult, pfx_02_jumbo_num_mult,i, j);
    }
  }

  test_binary_op(fn_subt, pfx_02_jumbo_num_subt, 333, 222);
  test_binary_op(fn_subt, pfx_02_jumbo_num_subt, 222, 333);

  test_print(5);
  test_print(-5);

  return 0;
}
