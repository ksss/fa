#include <stdio.h>
#include <string.h>
#include "fa-icon-list.h"

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
          fprintf(stderr, "'%s' is not icon id.\nsee `fa --list`\n", argv[1]);
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
