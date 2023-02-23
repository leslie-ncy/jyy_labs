#include <game.h>

// Operating system is a C program!
int main(const char *args) {
  ioe_init();

  puts("mainargs = \"");
  puts(args); // make run mainargs=xxx
  puts("\"\n");

  // splash();
  draw_rectangle(0, 0, 20, 10, 0xFFFFFF);

  puts("Press any key to see its key code...\n");
  while (1) {
    const char* key = print_key();
    if (key) puts(key);
  }
  return 0;
}
