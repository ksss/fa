#include <stdio.h>
#include <string.h>
#include "fa-icon-list.h"

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int levenshtein(const char *s1, const char *s2) {
  unsigned int s1len, s2len, x, y, lastdiag, olddiag;
  s1len = strlen(s1);
  s2len = strlen(s2);
  unsigned int column[s1len+1];
  for (y = 1; y <= s1len; y++)
  column[y] = y;
  for (x = 1; x <= s2len; x++) {
    column[0] = x;
    for (y = 1, lastdiag = x-1; y <= s1len; y++) {
      olddiag = column[y];
      column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
      lastdiag = olddiag;
    }
  }
  return(column[s1len]);
}

void
print_list() {
  size_t count = sizeof(icon_list) / sizeof(struct icon);
  printf("id\tunicode\tcode\n");
  for (int i = 0; i < count; i++) {
    printf("%s\t%s\t%s\n", icon_list[i].id, icon_list[i].unicode, icon_list[i].code);
  }
}

const struct icon *
find_icon(const char *id) {
  size_t count = sizeof(icon_list) / sizeof(struct icon);
  for (int i = 0; i < count; i++) {
    if (strcmp(icon_list[i].id, id) == 0) {
      return &icon_list[i];
    }
  }
  return NULL;
}

#define USAGE "fa [option] [id]\n" \
              "option:\n" \
              "  -l,--list print all icon list as tsv\n"

int
main (int argc, char **argv) {
  switch (argc) {
    case 1:
      break;
    case 2:
      if (argv[1][0] == '-') {
        if (argv[1][1] == 'l') {
          print_list();
          return 0;
        } else if (argv[1][1] == '-') {
          if (strcmp(argv[1], "--list") == 0) {
            print_list();
            return 0;
          }
        }
      } else {
        const struct icon *icon = find_icon(argv[1]);
        if (icon == NULL) {
          size_t count = sizeof(icon_list) / sizeof(struct icon);
          int i = 0;
          int c = 0;
          struct icon icons[3];
          for (i = 0; i < count; i++) {
            if (levenshtein(argv[1], (const char *)icon_list[i].id) < 3) {
              icons[c++] = icon_list[i];
              if (c == 3) break;
            }
          }
          fprintf(stderr, "'%s' is not icon id.\nsee `fa --list`\n", argv[1]);
          if (0 < c)
            fprintf(stderr, "did you mean?\n");
          for (i = 0; i < c; i++) {
            fprintf(stderr, "  %s\n", icons[i].id);
          }
          return 1;
        }
        printf("%s", icon->unicode);
        return 0;
      }
      break;
    default:
      break;
  }
  printf(USAGE);
  return 0;
}
