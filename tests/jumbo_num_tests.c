#include "jumbo_num.h"

#include <assert.h>

static void test_add(int a, int b, int expected) {
  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_02 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_03 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_04 = pfx_02_jumbo_num_new();

  pfx_02_jumbo_num_init(jn_01, 0);
  pfx_02_jumbo_num_init(jn_02, a);
  pfx_02_jumbo_num_init(jn_03, b);
  pfx_02_jumbo_num_init(jn_04, expected);

  pfx_02_jumbo_num_add(jn_01, jn_02, jn_03);
  assert(pfx_02_jumbo_num_eq(jn_01, jn_04));

  pfx_02_jumbo_num_free(jn_01);
  pfx_02_jumbo_num_free(jn_02);
  pfx_02_jumbo_num_free(jn_03);
  pfx_02_jumbo_num_free(jn_04);
}

int main(void) {

  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_02 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_03 = pfx_02_jumbo_num_new();

  pfx_02_jumbo_num_init(jn_01, 5);
  pfx_02_jumbo_num_init(jn_02, 5);
  pfx_02_jumbo_num_init(jn_03, 6);

  assert(pfx_02_jumbo_num_eq(jn_01, jn_02));
  assert(pfx_02_jumbo_num_neq(jn_01, jn_03));

  test_add(123, 456, 579);
  test_add(250, 251, 501);
  test_add(1, 100, 101);
  test_add(1, 899, 900);

  return 0;
}
