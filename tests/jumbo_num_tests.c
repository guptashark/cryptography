#include "jumbo_num.h"

#include <assert.h>

int main(void) {

  struct pfx_02_jumbo_num *jn = pfx_02_jumbo_num_new();
  pfx_02_jumbo_num_free(jn);

  return 0;
}
