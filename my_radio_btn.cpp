
#include "lvgl/lvgl.h"
#include "my_radio_btn.h"


static lv_style_t style_radio;
static lv_style_t style_radio_chk;
static uint32_t active_index = 0;

lv_obj_t* label2;
char text[3][20] = { "Rus", "English", "Deutch" };

static void radio_event_handler(lv_event_t* e);
static void radiobutton_create(lv_obj_t* parent, const char* txt);


void radio_create(void) {
    /**
     * Checkboxes as radio buttons
     */

     /* The idea is to enable `LV_OBJ_FLAG_EVENT_BUBBLE` on checkboxes and process the
      * `LV_EVENT_CLICKED` on the container.
      * A variable is passed as event user data where the index of the active
      * radiobutton is saved */

    lv_style_init(&style_radio);
    lv_style_set_radius(&style_radio, LV_RADIUS_CIRCLE);

    lv_style_init(&style_radio_chk);
    lv_style_set_bg_img_src(&style_radio_chk, NULL);

    char array[3][20] = { "Rus", "English", "Deutch" };

    char buf[16];

    lv_obj_t* cont2 = lv_obj_create(lv_scr_act());
    lv_obj_set_flex_flow(cont2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_size(cont2, lv_pct(40), lv_pct(40));
    //  lv_obj_set_x(cont2, lv_pct(50));
    lv_obj_add_event_cb(cont2, radio_event_handler, LV_EVENT_CLICKED, &active_index);

    uint8_t i;

    for (i = 0; i < 3; i++) {
        lv_snprintf(buf, sizeof(buf), array[i]);
        radiobutton_create(cont2, buf);
    }

    /*Make the first checkbox checked*/
    lv_obj_add_state(lv_obj_get_child(cont2, 0), LV_STATE_CHECKED);

    //стиль для текста
    static lv_style_t style_text;
    lv_style_set_text_color(&style_text, lv_color_black());


    label2 = lv_label_create(lv_scr_act());
    lv_obj_set_pos(label2, 50, 150);
    lv_obj_add_style(label2, &style_text, 0);
    lv_label_set_text(label2, text[active_index]);
}



static void radiobutton_create(lv_obj_t* parent, const char* txt)
{
    lv_obj_t* obj = lv_checkbox_create(parent);
    lv_checkbox_set_text(obj, txt);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_style(obj, &style_radio, LV_PART_INDICATOR);
    lv_obj_add_style(obj, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);
}


static void radio_event_handler(lv_event_t* e)
{
    uint32_t* active_id = (uint32_t*)lv_event_get_user_data(e);
    lv_obj_t* cont = lv_event_get_current_target_obj(e);
    lv_obj_t* act_cb = lv_event_get_target_obj(e);
    lv_obj_t* old_cb = lv_obj_get_child(cont, *active_id);

    /*Do nothing if the container was clicked*/
    if (act_cb == cont) return;

    lv_obj_clear_state(old_cb, LV_STATE_CHECKED);   /*Uncheck the previous radio button*/
    lv_obj_add_state(act_cb, LV_STATE_CHECKED);     /*Uncheck the current radio button*/

    *active_id = lv_obj_get_index(act_cb);

    lv_label_set_text(label2, text[active_index]);
    
    LV_LOG_USER("Selected radio buttons: %d", (int)active_index);
}
