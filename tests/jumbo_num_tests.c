#include "jumbo_num.h"

#include <assert.h>


int main(void) {

  struct pfx_02_jumbo_num *jn_01 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_02 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_03 = pfx_02_jumbo_num_new();
  struct pfx_02_jumbo_num *jn_04 = pfx_02_jumbo_num_new();

  pfx_02_jumbo_num_init(jn_01, 5);
  pfx_02_jumbo_num_init(jn_02, 5);
  pfx_02_jumbo_num_init(jn_03, 6);
  pfx_02_jumbo_num_init(jn_04, 123456);

  assert(pfx_02_jumbo_num_eq(jn_01, jn_02));
  assert(pfx_02_jumbo_num_neq(jn_01, jn_03));

  pfx_02_jumbo_num_print(jn_01);
  pfx_02_jumbo_num_print(jn_02);
  pfx_02_jumbo_num_print(jn_03);
  pfx_02_jumbo_num_print(jn_04);

  return 0;
}
