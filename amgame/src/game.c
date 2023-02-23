#include <game.h>

struct
{
  int x;
  int y;
  int w;
  int h;
  uint32_t color;
} my_rec = {5,5,10,20, 0xFFFFFF};

void draw_my_rec() {
  draw_rectangle(my_rec.x, my_rec.y, my_rec.w, my_rec.h, my_rec.color);
}

void erase_my_rec() {
  draw_rectangle(my_rec.x, my_rec.y, my_rec.w, my_rec.h, 0);
}


void move_up() {
  erase_my_rec();
  my_rec.y -= 1;
  draw_my_rec();
}

void move_down() {
  erase_my_rec();
  my_rec.y += 1;
  draw_my_rec();
}

void move_left() {
  erase_my_rec();
  my_rec.x -= 1;
  draw_my_rec();
}

void move_right() {
  erase_my_rec();
  my_rec.x += 1;
  draw_my_rec();
}

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
    if (strcmp(key, "W") == 0) {
      move_up();
    } else if (strcmp(key, "S") == 0) {
      move_down();
    } else if (strcmp(key, "A") == 0) {
      move_left();
    } else if (strcmp(key, "D") == 0) {
      move_right();
    }
  }
  return 0;
}
