#include "jumbo_num.h"

#include <assert.h>

static void test_add() {

  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_02 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_03 = pfx_02_jumbo_num_new();

  pfx_02_jumbo_num_init(jn_01, 123);
  pfx_02_jumbo_num_init(jn_02, 456);
  pfx_02_jumbo_num_init(jn_03, 579);

  pfx_02_jumbo_num_print(jn_01);
  pfx_02_jumbo_num_print(jn_02);
  pfx_02_jumbo_num_print(jn_03);

  pfx_02_jumbo_num_add(jn_01, jn_02);
  pfx_02_jumbo_num_eq(jn_01, jn_03);

  pfx_02_jumbo_num_print(jn_01);
  pfx_02_jumbo_num_print(jn_02);
  pfx_02_jumbo_num_print(jn_03);
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

  test_add();

  return 0;
}
