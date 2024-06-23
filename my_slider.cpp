
#include "lvgl/lvgl.h"
#include "my_slider.h"


lv_obj_t* label;
int bg_color = 0xFFFFFF;
//uint16_t bg_color = 0xFFFF;

static void my_event_cb(lv_event_t* event);
static void slider_event_cb(lv_event_t* e);


void slider_create(void) {
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(bg_color), 0);

    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, 3);

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style, LV_OPA_40);
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&style, 8);
    lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_ofs_y(&style, 8);

    lv_style_set_outline_opa(&style, LV_OPA_COVER);
    lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 10);

    //создание кнопки
    lv_obj_t* btn = lv_btn_create(lv_scr_act());
    lv_obj_add_style(btn, &style, 0);
    lv_obj_align(btn, LV_ALIGN_TOP_MID,0,20);
    lv_obj_set_style_bg_color(btn, lv_palette_main(LV_PALETTE_DEEP_PURPLE), 0);
    lv_obj_add_event_cb(btn, my_event_cb, LV_EVENT_CLICKED, NULL);
    
    //текст кнопки
    lv_obj_t* label_b = lv_label_create(btn);
    lv_label_set_text(label_b, "Button");
    lv_obj_center(label_b);

    //создание ползунка
    lv_obj_t* slider = lv_slider_create(lv_scr_act());
    lv_obj_center(slider);
    lv_slider_set_range(slider, 0, 8245000);
    lv_obj_set_style_bg_color(slider, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_set_style_bg_color(slider, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider, lv_palette_main(LV_PALETTE_BROWN), LV_PART_KNOB);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    //стиль для текста
    static lv_style_t style_text;
    lv_style_set_text_color(&style_text, lv_color_white());

    //текст под ползунком
    label = lv_label_create(lv_scr_act());
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_add_style(label, &style_text, 0);
    lv_label_set_text(label, "My text");
    
}


static void my_event_cb(lv_event_t* event)
{
    lv_obj_set_style_bg_color(lv_scr_act(), lv_palette_main(LV_PALETTE_LIME), 0);
}


static void slider_event_cb(lv_event_t* e)
{
    lv_obj_t* slider = lv_event_get_target_obj(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d", (uint64_t)lv_slider_get_value(slider));
    lv_label_set_text(label, buf);
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex((uint64_t)lv_slider_get_value(slider)), 0);
}

