#include "jumbo_num.h"

#include <stdlib.h>

struct pfx_02_jumbo_num {
  int x;
};

struct pfx_02_jumbo_num *
pfx_02_jumbo_num_new(void) {
  struct pfx_02_jumbo_num *jn = malloc(sizeof(struct pfx_02_jumbo_num));
  jn->x = 0;
  return jn;
}

int pfx_02_jumbo_num_init
(struct pfx_02_jumbo_num *jn, int n) {
  jn->x = n;
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
(struct pfx_02_jumbo_num *jn_01, struct pfx_02_jumbo_num *jn_02) {
  jn_01->x += jn_02->x;
  return 0;
}

int pfx_02_jumbo_num_mult
(struct pfx_02_jumbo_num *jn_01, struct pfx_02_jumbo_num *jn_02) {
  jn_01->x *= jn_02->x;
  return 0;
}

void pfx_02_jumbo_num_free
(struct pfx_02_jumbo_num *jn) {
  free(jn);
}
