#pragma once

void set_text_by_row(int row, TextLayer * text_layer);
void draw_row_callback (GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context);