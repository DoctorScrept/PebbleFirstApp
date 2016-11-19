#include <pebble.h>
#include "text_factory.h"

void set_text_by_row(int row, TextLayer * text_layer)
{
    switch(row){
     case 0:
         text_layer_set_text(text_layer, "First text");
      break;
      case 1:
          text_layer_set_text(text_layer, "This Layer type is a bit more complex to set up than the other Layers, in that it requires a large amount of information about how it will look and behave before it can be instantiated. This information is given to the MenuLayer via the use of a number of callbacks. When the MenuLayer is redrawn or reloaded, it calls these functions to get the relevant data. The advantage of this approach is that the MenuLayer rows can be filled with data that can be changed at any time, such as with Wristponder or Pebble Tube Status (shameless plugs!) ");
      break;
         case 2:
         text_layer_set_text(text_layer, "The API documentation describes all the possible MenuLayerCallbacks that can be associated with a MenuLayer, but the ones we will be using for a simple example will be:");
      break;
         case 3:
         text_layer_set_text(text_layer, "For the draw_row_handler(), we will need to be able to alter what is drawn in the row depending on which row it is. This can be done by switching the cell_index->row property. You can use the presented GContext however you like for any of the SDK drawing functions, but to keep things simple we will use the pre-made drawing functions provided by the SDK. With these two last points combined, the draw_row_callback() function transforms into this beast:");
      break;
         case 4:
         text_layer_set_text(text_layer, "So that’s how to setup a basic MenuLayer. An extended application like those mentioned previously will use char[] buffers to store each row’s text, modified in a in_received signature AppMessage callback, and calling menu_layer_reload_data() in that AppMessage callback, thus updating the MenuLayer with the new data.");
      break;
      }
}

//=======================================================================================================
void draw_row_callback (GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
   //Which row is it? 
   switch(cell_index->row)
      {
      case 0:
         menu_cell_basic_draw(ctx, cell_layer, "1.LOX", "Green and crispy!", NULL);
         break;
      case 1:
         menu_cell_basic_draw(ctx, cell_layer, "2.Orange", "Peel first!", NULL);
         break;
      case 2:
         menu_cell_basic_draw(ctx, cell_layer, "3.Banana", "Can be a gun =)", NULL);
         break;
      case 3:
         menu_cell_basic_draw(ctx, cell_layer, "4.Tomato", "Exstremely versatile!", NULL);
         break;
      case 4:
         menu_cell_basic_draw(ctx, cell_layer, "5.Pear", "Teardrop shaped!", NULL);
         break;
      case 5:
         menu_cell_basic_draw(ctx, cell_layer, "6.Grape", "Bunches of 'em!'", NULL);
         break;
      case 6:
         menu_cell_basic_draw(ctx, cell_layer, "7.Melon", "Only three left!", NULL);
         break;
      
      }
}