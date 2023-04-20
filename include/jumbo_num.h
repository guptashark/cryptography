#ifndef JUMBO_NUM_H
#define JUMBO_NUM_H

struct pfx_02_jumbo_num;

struct pfx_02_jumbo_num *
pfx_02_jumbo_num_new(void);

int pfx_02_jumbo_num_init
(struct pfx_02_jumbo_num *jn, int n);

int pfx_02_jumbo_num_init_one
(struct pfx_02_jumbo_num *jn);

int pfx_02_jumbo_num_init_zero
(struct pfx_02_jumbo_num *jn);

/* num add. */
int pfx_02_jumbo_num_add
(struct pfx_02_jumbo_num *jn_01, struct pfx_02_jumbo_num *jn_02);

/* num mult. */
int pfx_02_jumbo_num_mult
(struct pfx_02_jumbo_num *jn_01, struct pfx_02_jumbo_num *jn_02);

void pfx_02_jumbo_num_free
(struct pfx_02_jumbo_num *jn);

#endif
