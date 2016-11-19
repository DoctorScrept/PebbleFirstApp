#include <pebble.h>
 
Window* window, *window1;//, *window2;
MenuLayer* menu_layer;
TextLayer* myTextLayer, *text_timeL;
static ScrollLayer *s_scroll_layer;
static char time_format[] = "00:00";

void tick_handler1(struct tm *myTick, TimeUnits units_changed){
   
   strftime(time_format, sizeof(time_format), "%H:%M", myTick);
   text_layer_set_text(text_timeL, time_format);
   
}

uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context){
   return 7;
}

void draw_row_callback (GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context){
   //Which row is it? 
   switch(cell_index->row)
      {
      case 0:
         menu_cell_basic_draw(ctx, cell_layer, "1.Apple", "Green and crispy!", NULL);
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

void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
   
//    window_stack_push(window2, false); 
   
   Layer *window_layer1 = window_get_root_layer(window1);
  
   s_scroll_layer = scroll_layer_create(GRect(0, 16, 144, 168));
   scroll_layer_set_click_config_onto_window(s_scroll_layer, window1);
   
   myTextLayer = text_layer_create(GRect(0, 16, 144, 2000));
   text_timeL = text_layer_create(GRect(115, 0, 30, 15));                                                                                
   tick_timer_service_subscribe(MINUTE_UNIT, tick_handler1);                          
             
   
 //layer_add_child(window_get_root_layer(window1), text_layer_get_layer(myTextLayer));
   
 //-----------------------------------------TIME--------------------------------------------------↓↓↓↓↓-----------//  
      // ПОМЕНЯТЬ ШРИФТ (для часов) !!!                             ↓↓↓↓↓    
   text_layer_set_font(text_timeL, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
                       
 //-----------------------------------------TIME--------------------------------------------------↑↑↑↑↑-----------//
   
      int which = cell_index->row; 
      switch(which){
     case 0:
         text_layer_set_text(myTextLayer, "First text");
      break;
      case 1:
          text_layer_set_text(myTextLayer, "This Layer type is a bit more complex to set up than the other Layers, in that it requires a large amount of information about how it will look and behave before it can be instantiated. This information is given to the MenuLayer via the use of a number of callbacks. When the MenuLayer is redrawn or reloaded, it calls these functions to get the relevant data. The advantage of this approach is that the MenuLayer rows can be filled with data that can be changed at any time, such as with Wristponder or Pebble Tube Status (shameless plugs!) ");
      break;
         case 2:
         text_layer_set_text(myTextLayer, "The API documentation describes all the possible MenuLayerCallbacks that can be associated with a MenuLayer, but the ones we will be using for a simple example will be:");
      break;
         case 3:
         text_layer_set_text(myTextLayer, "For the draw_row_handler(), we will need to be able to alter what is drawn in the row depending on which row it is. This can be done by switching the cell_index->row property. You can use the presented GContext however you like for any of the SDK drawing functions, but to keep things simple we will use the pre-made drawing functions provided by the SDK. With these two last points combined, the draw_row_callback() function transforms into this beast:");
      break;
         case 4:
         text_layer_set_text(myTextLayer, "So that’s how to setup a basic MenuLayer. An extended application like those mentioned previously will use char[] buffers to store each row’s text, modified in a in_received signature AppMessage callback, and calling menu_layer_reload_data() in that AppMessage callback, thus updating the MenuLayer with the new data.");
      break;
      }
                   scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(myTextLayer));
                   layer_add_child(window_layer1, scroll_layer_get_layer(s_scroll_layer));
   
                              GSize max_size;
                                 max_size.w =144;
                                 max_size.h = text_layer_get_content_size(myTextLayer).h+150;
                              text_layer_set_size(myTextLayer, max_size);
                              scroll_layer_set_content_size(s_scroll_layer, GSize(144, max_size.h));
                                   
   
   layer_add_child(window_layer1, text_layer_get_layer(text_timeL));
   
    window_stack_push(window1, true);
     
   
}

       
 static void window_load(Window *window)
                           {
    APP_LOG(APP_LOG_LEVEL_INFO, "(DS)window_load");
                               // Create it - 12 is approx height of the top bar
                              menu_layer = menu_layer_create(GRect(0, 16, 144, 152));
                              
                              //Let it receive clicks
                              menu_layer_set_click_config_onto_window(menu_layer, window);
                              
                         //=============================================================

                              
                              //Give it it's callback
                              MenuLayerCallbacks callbacks = {
                                 .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
                                 .get_num_rows =(MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
                                 .select_click =(MenuLayerSelectCallback) select_click_callback
                              };
                              menu_layer_set_callbacks(menu_layer, NULL, callbacks);

                              
                              //Add to window
                              layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu_layer));
                           
                               
                           }
                            
 static void window_unload(Window *window)
                           {
                            menu_layer_destroy(menu_layer);
  //                           scroll_layer_destroy(s_scroll_layer);
    
    APP_LOG(APP_LOG_LEVEL_INFO, "(DS)window_unload");
                           }

                    static void selected_window_load(Window *window) {
                      // Layer *window_layer = window_get_root_layer(window);
                      // GRect bounds = layer_get_bounds(window_layer);

                      // s_menu_layer = menu_layer_create(bounds);
                      // menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
                      //   .get_num_rows = get_sections_count_callback,
                      //   .get_cell_height = PBL_IF_ROUND_ELSE(get_cell_height_callback, NULL),
                      //   .draw_row = draw_row_handler,
                      //   .select_click = select_callback
                      // }); 
                      // menu_layer_set_click_config_onto_window(s_menu_layer, window);
                      // layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
                       
                       APP_LOG(APP_LOG_LEVEL_INFO, "(DS)selected_window_load");
                    } 
                                static void selected_window_unload(Window *window) {
                                  // menu_layer_destroy(s_menu_layer);
                                  // text_layer_destroy(s_error_text_layer);
//                                    if (window == window1) {
                                      
                                      APP_LOG(APP_LOG_LEVEL_INFO, "(DS)selected_window_unload");
                                      
                                      text_layer_destroy(myTextLayer);
                                      scroll_layer_destroy(s_scroll_layer);
                                      
//                                       window_destroy(window);
//                                    }
                                }                                              
void init()
                           {
                               
                                      
                                 window = window_create();
                                 window1 = window_create();
                                 
                               window_set_window_handlers(window, (WindowHandlers) {
                                  .load = window_load, 
                                  .unload = window_unload});

//                                window2 = window_create();
                               window_set_window_handlers(window1, (WindowHandlers){
                                .load =selected_window_load,
                                .unload =selected_window_unload,
                               });


   
                                 window_stack_push(window, true);
                             

                           }

 
                                                         void deinit()
                                                         {
//                                                             text_layer_destroy(myTextLayer);
                                                            text_layer_destroy(text_timeL);
                                                            window_destroy(window1);
                                                             window_destroy(window);
                                                             tick_timer_service_unsubscribe();
//                                                              scroll_layer_destroy(s_scroll_layer);
                                                         }
                                                          
                                                         int main(void)
                                                         {
                                                            APP_LOG(APP_LOG_LEVEL_INFO, "zalupa");
                                                             init();
                                                             app_event_loop();
                                                             deinit();
                                                         }
