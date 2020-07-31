#ifndef NLE_H
#define NLE_H

#include <stdio.h>

#include <fcontext/fcontext.h>

/* TODO: Fix this. */
#undef SIG_RET_TYPE
#define SIG_RET_TYPE void (*)(int)

typedef struct nle_globals {
    fcontext_stack_t stack;
    fcontext_t returncontext;
    fcontext_t generatorcontext;

    boolean done;

    FILE *ttyrec;
    char outbuf[BUFSIZ];
    char *outbuf_write_ptr;
    char *outbuf_write_end;
} nle_ctx_t;

/*
 * Would like to annotate this with __thread, but that causes
 * the MacOS dynamic linker to not unload the library on dlclose().
 */
nle_ctx_t *current_nle_ctx;

nle_ctx_t *nle_start(FILE *);
nle_ctx_t *nle_step(nle_ctx_t *, int, boolean *);
void nle_reset(nle_ctx_t *);
void nle_end(nle_ctx_t *);

#endif /* NLE_H */
