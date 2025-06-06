/*
(x, y) indicates top left corner of cursor
*/

int prev_x = 0; //cursors previous x position
int prev_y = 0; //cursors previous y position

 int buffer = 5; //buffer between kinda edge of screen

// Function to set up the cursor
void setup_cursor(struct Cursor* cursor, int x, int y, int size, unsigned int color) {
    cursor->x = x;
    cursor->y = y;
    cursor->size = size;
    cursor->color = color;
}

void paint_cursor(struct Cursor* c){
  tft.drawRect(prev_x, prev_y, c->size, c->size, BASE_BG);
  tft.drawRect(c->x, c->y, c->size, c->size, c->color);
}

/* Moves cursor desired shift (if inside screen bounds) 
shift_x : positive x is in positive x screen direction
shift_y : positive y is in positive y screen direction
*/
void move_cursor(struct Cursor* c, int shift_x, int shift_y){
  int new_x = c->x;
  int new_y = c->y;
  prev_x = c->x;
  prev_y = c->y;
  bool ok = true; //okay to move cursor actually

  //x-bound SCREEN_HEIGHT
  if(c->x + c->size + shift_x > (SCREEN_HEIGHT - buffer)){
    new_x = SCREEN_HEIGHT - buffer - c->size;
    ok = false;

  //x-bound 0
  } else if(c->x + shift_x < buffer){
    new_x = buffer;
    ok = false;
  
  //x is okay
  } else {
    prev_x = c->x;
    new_x = prev_x + shift_x;
  } 
  
  //y-bound SCREEN_WIDTH
  if(c->y + c->size + shift_y > (SCREEN_WIDTH - buffer)){
    new_y = SCREEN_WIDTH - buffer - c->size;
    ok = false;

  //y-bound 0
  } else if(c->y + shift_y < buffer){
    new_y = buffer;
    ok = false;
  
  //y is okay
  } else {
    prev_y = c->y;
    new_y = prev_y + shift_y;
  } 

  c->x = new_x;
  c->y = new_y;
}