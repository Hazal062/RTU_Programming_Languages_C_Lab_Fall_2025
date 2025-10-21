// Hazal Guc 231ADB264
// Compile: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long i64;
typedef enum { T_NUM, T_PLUS, T_MINUS, T_STAR, T_END, T_INVALID } TokKind;
typedef struct {
  TokKind kind;
  i64 ival;
  size_t start;
} Token;
typedef struct {
  const char* buf;
  size_t len;
  size_t i;
  Token cur;
  int had_error;
  size_t err_pos;
} Lexer;

static void set_error(Lexer* L, size_t pos0) {
  if (!L->had_error) {
    L->had_error = 1;
    L->err_pos = pos0 + 1;
  }
}
static int is_digit(char c) { return c >= '0' && c <= '9'; }
static void skip_ws(Lexer* L) {
  while (L->i < L->len && isspace((unsigned char)L->buf[L->i])) L->i++;
}
static Token make_tok(TokKind k, size_t s) {
  Token t;
  t.kind = k;
  t.ival = 0;
  t.start = s;
  return t;
}

static Token next_token(Lexer* L) {
  skip_ws(L);
  if (L->i >= L->len) return make_tok(T_END, L->i);
  size_t s = L->i;
  char c = L->buf[L->i];
  if (is_digit(c)) {
    i64 v = 0;
    while (L->i < L->len && is_digit(L->buf[L->i])) {
      v = v * 10 + (L->buf[L->i] - '0');
      L->i++;
    }
    Token t = make_tok(T_NUM, s);
    t.ival = v;
    return t;
  }
  L->i++;
  switch (c) {
    case '+':
      return make_tok(T_PLUS, s);
    case '-':
      return make_tok(T_MINUS, s);
    case '*':
      if (L->i < L->len && L->buf[L->i] == '*')
        return make_tok(T_INVALID, L->i);
      return make_tok(T_STAR, s);
    default:
      return make_tok(T_INVALID, s);
  }
}

static void lex_init(Lexer* L, const char* buf, size_t len) {
  L->buf = buf;
  L->len = len;
  L->i = 0;
  L->had_error = 0;
  L->err_pos = 0;
  L->cur = next_token(L);
}

static i64 parse_expr(Lexer* L);
static void consume(Lexer* L, TokKind k) {
  if (L->cur.kind == k)
    L->cur = next_token(L);
  else
    set_error(L, L->cur.start);
}

static i64 parse_factor(Lexer* L) {
  if (L->had_error) return 0;
  if (L->cur.kind == T_NUM) {
    i64 v = L->cur.ival;
    L->cur = next_token(L);
    return v;
  }
  set_error(L, L->cur.start < L->len ? L->cur.start : L->len);
  return 0;
}

static i64 parse_term(Lexer* L) {
  i64 v = parse_factor(L);
  while (!L->had_error && L->cur.kind == T_STAR) {
    consume(L, T_STAR);
    i64 rhs = parse_factor(L);
    if (L->had_error) return 0;
    v = v * rhs;
  }
  return v;
}

static i64 parse_expr(Lexer* L) {
  i64 v = parse_term(L);
  while (!L->had_error && (L->cur.kind == T_PLUS || L->cur.kind == T_MINUS)) {
    TokKind op = L->cur.kind;
    if (op == T_PLUS)
      consume(L, T_PLUS);
    else
      consume(L, T_MINUS);
    i64 rhs = parse_term(L);
    if (L->had_error) return 0;
    v = (op == T_PLUS) ? v + rhs : v - rhs;
  }
  return v;
}

static char* read_all(const char* path, size_t* out_len) {
  FILE* f = fopen(path, "rb");
  if (!f) return NULL;
  fseek(f, 0, SEEK_END);
  long n = ftell(f);
  if (n < 0) n = 0;
  fseek(f, 0, SEEK_SET);
  char* buf = (char*)malloc((size_t)n + 1);
  if (!buf) {
    fclose(f);
    return NULL;
  }
  size_t rd = fread(buf, 1, (size_t)n, f);
  fclose(f);
  buf[rd] = '\0';
  if (out_len) *out_len = rd;
  return buf;
}

static void make_out_name(const char* in, char* out, size_t cap) {
  const char *base = in, *slash = strrchr(in, '/');
#ifdef _WIN32
  const char* bslash = strrchr(in, '\\');
  if (!slash || (bslash && bslash > slash)) slash = bslash;
#endif
  if (slash) {
    base = slash + 1;
  }
  size_t L = 0;
  while (base[L] && base[L] != '.' && L + 1 < cap) {
    out[L] = base[L];
    L++;
  }
  const char* suf = "_Hazal_Guc_231ADB264.txt";
  for (size_t i = 0; suf[i] && L + 1 < cap; ++i) out[L++] = suf[i];
  out[L] = '\0';
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input.txt>\n", argv[0]);
    return 1;
  }

  size_t len = 0;
  char* buf = read_all(argv[1], &len);
  if (!buf) {
    fprintf(stderr, "Cannot read file: %s\n", argv[1]);
    return 1;
  }

  Lexer L;
  lex_init(&L, buf, len);
  i64 result = parse_expr(&L);
  if (!L.had_error && L.cur.kind != T_END) set_error(&L, L.cur.start);

  char outname[512];
  make_out_name(argv[1], outname, sizeof(outname));
  FILE* out = fopen(outname, "wb");
  if (!out) {
    fprintf(stderr, "Cannot open output file: %s\n", outname);
    free(buf);
    return 1;
  }

  if (L.had_error)
    fprintf(out, "ERROR:%zu\n", L.err_pos);
  else
    fprintf(out, "%lld\n", (long long)result);

  fclose(out);
  free(buf);
  return 0;
}
