#include "autonselector.h"
#include "main.h"
#include <vector>

using namespace pros;

int selected_auton_id = -1;
static std::vector<lv_obj_t*> btn_list;
static lv_obj_t* scroll_container = nullptr;

lv_obj_t* lbl_battery = nullptr;
lv_obj_t* lbl_status  = nullptr;
lv_obj_t* lbl_xyh     = nullptr;
lv_obj_t* lbl_temps   = nullptr;

static lv_style_t style_btn;
static lv_style_t style_btn_selected;
static lv_style_t style_telebar;

const char* AUTON_NAMES[11] = {
    "R3MID4LONG", "R4LONGRUSH", "R7LONGRUSH", "R9LONGRUSH", "L3MID4LONG", "L4LONGRUSH", "L7LONGRUSH", "L9LONGRUSH", "SOLO AWP", "DEFENSE" , "SKILLS"
};



static void init_styles() {
    lv_color_t red_main = lv_palette_main(LV_PALETTE_RED);
    lv_color_t red_dark = lv_palette_darken(LV_PALETTE_RED, 3);
    lv_color_t red_light = lv_palette_lighten(LV_PALETTE_RED, 1);

    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 8);
    lv_style_set_border_width(&style_btn, 2);
    lv_style_set_border_color(&style_btn, red_light);
    lv_style_set_text_color(&style_btn, lv_color_white());

    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn, red_main);          
    lv_style_set_bg_grad_color(&style_btn, red_dark);     
    lv_style_set_bg_grad_dir(&style_btn, LV_GRAD_DIR_VER); 

    lv_style_init(&style_btn_selected);
    lv_style_set_radius(&style_btn_selected, 8);
    lv_style_set_border_width(&style_btn_selected, 3);
    lv_style_set_border_color(&style_btn_selected, lv_color_white()); 
    lv_style_set_text_color(&style_btn_selected, lv_color_white());

    lv_style_set_bg_opa(&style_btn_selected, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn_selected, red_dark);
    lv_style_set_bg_grad_color(&style_btn_selected, lv_color_hex(0x660000)); 
    lv_style_set_bg_grad_dir(&style_btn_selected, LV_GRAD_DIR_VER);

    lv_style_init(&style_telebar);
    lv_style_set_bg_opa(&style_telebar, LV_OPA_COVER);
    lv_style_set_bg_color(&style_telebar, lv_color_hex(0x220000));
    lv_style_set_bg_grad_color(&style_telebar, red_dark);
    lv_style_set_bg_grad_dir(&style_telebar, LV_GRAD_DIR_VER);
}

static void refresh_button_styles() {
    for (int i = 0; i < (int)btn_list.size(); i++) {
        lv_obj_t* b = btn_list[i];
        lv_obj_remove_style(b, &style_btn, 0);
        lv_obj_remove_style(b, &style_btn_selected, 0);
        lv_obj_add_style(b, (i == selected_auton_id) ? &style_btn_selected : &style_btn, 0);
    }
}

static void btn_event_cb(lv_event_t* e) {
    lv_obj_t* btn = (lv_obj_t*)lv_event_get_target(e);
    for (int i = 0; i < (int)btn_list.size(); i++) {
        if (btn_list[i] == btn) {
            selected_auton_id = i;
            refresh_button_styles();
            break;
        }
    }
}

static void scroll_up_cb(lv_event_t* e) {
    if (scroll_container) lv_obj_scroll_by(scroll_container, 0, -160, LV_ANIM_ON);
}

static void scroll_down_cb(lv_event_t* e) {
    if (scroll_container) lv_obj_scroll_by(scroll_container, 0, 160, LV_ANIM_ON);
}

void create_selector_ui() {
    init_styles();
    lv_obj_t* scr = lv_screen_active();

    lv_obj_t* tabview = lv_tabview_create(scr);
    lv_tabview_set_tab_bar_position(tabview, LV_DIR_TOP); 
    lv_obj_set_size(tabview, 480, 272);


    lv_obj_t* tab_bar = lv_tabview_get_tab_bar(tabview);
    lv_obj_set_style_bg_color(tab_bar, lv_palette_darken(LV_PALETTE_RED, 4), 0);
    lv_obj_set_style_text_color(tab_bar, lv_color_white(), 0);
    lv_obj_set_style_border_width(tab_bar, 0, 0);

    lv_obj_t* content = lv_tabview_get_content(tabview);
    lv_obj_add_style(content, &style_telebar, 0);

    lv_obj_t* tab_tele = lv_tabview_add_tab(tabview, "i forgot what these are called");
    lv_obj_t* tab_auton = lv_tabview_add_tab(tabview, "Auton Selector");

    lv_obj_set_style_bg_opa(tab_tele, LV_OPA_TRANSP, 0);
    lv_obj_set_style_bg_opa(tab_auton, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(tab_tele, 0, 0);
    lv_obj_set_style_border_width(tab_auton, 0, 0);

    lv_obj_set_flex_flow(tab_tele, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(tab_tele, 15, 0);
    lv_obj_set_style_pad_row(tab_tele, 10, 0);

    lbl_battery = lv_label_create(tab_tele);
    lv_label_set_text(lbl_battery, "Battery: 100%");
    lv_obj_set_style_text_font(lbl_battery, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(lbl_battery, lv_color_white(), 0);

    lbl_status = lv_label_create(tab_tele);
    lv_label_set_text(lbl_status, "Selected: None (Waiting)");
    lv_obj_set_style_text_font(lbl_status, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(lbl_status, lv_color_white(), 0);

    lbl_xyh = lv_label_create(tab_tele);
    lv_label_set_text(lbl_xyh, "X: 0.0  Y: 0.0  H: 0.0");
    lv_obj_set_style_text_color(lbl_xyh, lv_color_hex(0x00FF00), 0);
    lv_obj_set_style_text_font(lbl_xyh, &lv_font_montserrat_16, 0);

    lbl_temps = lv_label_create(tab_tele);
    lv_label_set_text(lbl_temps, "Drive: --F | Intake: --F");
    lv_obj_set_style_text_font(lbl_temps, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(lbl_temps, lv_palette_lighten(LV_PALETTE_GREY, 2), 0);


    lv_obj_set_flex_flow(tab_auton, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_all(tab_auton, 8, 0);

    scroll_container = lv_obj_create(tab_auton);
    lv_obj_set_size(scroll_container, 360, 190);
    lv_obj_set_flex_flow(scroll_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scrollbar_mode(scroll_container, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_style_bg_opa(scroll_container, LV_OPA_TRANSP, 0); 
    lv_obj_set_style_border_width(scroll_container, 0, 0);

    int auton_count = sizeof(AUTON_NAMES) / sizeof(AUTON_NAMES[0]);
    btn_list.clear();
    for (int i = 0; i < auton_count; i++) {
        lv_obj_t* btn = lv_button_create(scroll_container);
        lv_obj_set_size(btn, 330, 45);
        lv_obj_add_style(btn, &style_btn, 0);
        lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, nullptr);

        lv_obj_t* label = lv_label_create(btn);
        lv_label_set_text(label, AUTON_NAMES[i]);
        lv_obj_center(label);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_16, 0);

        btn_list.push_back(btn);
    }

    lv_obj_t* arrows = lv_obj_create(tab_auton);
    lv_obj_set_size(arrows, 80, 190);
    lv_obj_set_style_border_width(arrows, 0, 0);
    lv_obj_set_style_bg_opa(arrows, LV_OPA_TRANSP, 0);
    lv_obj_set_flex_flow(arrows, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(arrows, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_gap(arrows, 10, 0);

    lv_obj_t* up = lv_button_create(arrows);
    lv_obj_set_size(up, 60, 75);
    lv_obj_add_style(up, &style_btn, 0);
    lv_obj_add_event_cb(up, scroll_up_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_t* lu = lv_label_create(up); lv_label_set_text(lu, "↑"); lv_obj_center(lu);

    lv_obj_t* down = lv_button_create(arrows);
    lv_obj_set_size(down, 60, 75);
    lv_obj_add_style(down, &style_btn, 0);
    lv_obj_add_event_cb(down, scroll_down_cb, LV_EVENT_CLICKED, nullptr);
    lv_obj_t* ld = lv_label_create(down); lv_label_set_text(ld, "↓"); lv_obj_center(ld);

    refresh_button_styles();
}
lv_obj_t* get_scroll_container() {
    return scroll_container;
}