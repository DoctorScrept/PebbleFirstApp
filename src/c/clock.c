#include <pebble.h>
#include "clock.h"


TextLayer *clock_text_layer;

static char time_format[] = "00:00";

void clock_on_time_change(struct tm *myTick, TimeUnits units_changed)
{
   strftime(time_format, sizeof(time_format), "%H:%M", myTick);
   text_layer_set_text(clock_text_layer, time_format);
}

void clock_init(Layer *parent)
{
//-----------------------------------------TIME--------------------------------------------------↓↓↓↓↓-----------//  
   clock_text_layer = text_layer_create(GRect(115, 0, 30, 15));                                                                                
   tick_timer_service_subscribe(MINUTE_UNIT, clock_on_time_change); 
   // ПОМЕНЯТЬ ШРИФТ (для часов) !!!                             ↓↓↓↓↓    
   text_layer_set_font(clock_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
                   
   layer_add_child(parent, text_layer_get_layer(clock_text_layer));
 //-----------------------------------------TIME--------------------------------------------------↑↑↑↑↑-----------//
}   

void clock_clear() {
   text_layer_destroy(clock_text_layer);
}