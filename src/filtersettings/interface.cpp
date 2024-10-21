#include "api.h"
#include "filtersettings/filterconfig.hpp"
#include "filtersettings/interface.hpp"
#include "config.h"
#include "liblvgl/core/lv_event.h"

// testing settings
int sliderWidth = 200;

lv_obj_t * redlowLabel;
lv_obj_t * redhighLabel;
lv_obj_t * bluelowLabel;
lv_obj_t * bluehighLabel;

static void redlowSliderEventHandler(lv_event_t * e) {
    lv_obj_t * slider = lv_event_get_current_target(e);
    redlow = lv_slider_get_value(slider);
    lv_label_set_text_fmt(redlowLabel, "Red Lower Bound: %.5f", redlow);
}
static void redhighSliderEventHandler(lv_event_t * e) {
    lv_obj_t * slider = lv_event_get_current_target(e);
    redhigh = lv_slider_get_value(slider);
    lv_label_set_text_fmt(redhighLabel, "Red Upper Bound: %.5f", redhigh);
}
static void bluelowSliderEventHandler(lv_event_t * e) {
    lv_obj_t * slider = lv_event_get_current_target(e);
    bluelow = lv_slider_get_value(slider);
    lv_label_set_text_fmt(bluelowLabel, "Blue Lower Bound: %.5f", bluelow);
}
static void bluehighSliderEventHandler(lv_event_t * e) {
    lv_obj_t * slider = lv_event_get_current_target(e);
    bluehigh = lv_slider_get_value(slider);
    lv_label_set_text_fmt(bluehighLabel, "Blue Upper Bound: %.5f", bluehigh);
}
static void savebuttonEventHandler(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        writeSettings();
    }
}


void create_ui() {
    // screen
    lv_obj_t * scr = lv_scr_act();  // load active object as screen

    // red low
    lv_obj_t * redlowSlider = lv_slider_create(scr);  // create lvgl object red low bound slider with parent obj screen
    lv_slider_set_range(redlowSlider, 0, 360);  // set range of slider (0-360 for color sensor)
    lv_slider_set_value(redlowSlider, redlow, LV_ANIM_OFF);  // set initial value of slider to stored value
    lv_obj_set_width(redlowSlider, sliderWidth);  // set width of obj 
    lv_obj_set_pos(redlowSlider, 10, 20);  // set position of obj
    lv_obj_add_event_cb(redlowSlider, redlowSliderEventHandler, LV_EVENT_VALUE_CHANGED, NULL);  // add callback for slider

    redlowLabel = lv_label_create(scr);  // initialize label for slider value
    lv_obj_set_pos(redlowLabel, 220 , 20);  // set label position

    // red high
    lv_obj_t * redhighSlider = lv_slider_create(scr);  
    lv_slider_set_range(redhighSlider, 0, 360);  
    lv_slider_set_value(redhighSlider, redhigh, LV_ANIM_OFF);  
    lv_obj_set_width(redhighSlider, sliderWidth);  
    lv_obj_set_pos(redhighSlider, 10, 70);  
    lv_obj_add_event_cb(redhighSlider, redhighSliderEventHandler, LV_EVENT_VALUE_CHANGED, NULL);

    redhighLabel = lv_label_create(scr);
    lv_obj_set_pos(redhighLabel, 220 , 70);

    // blue low
    lv_obj_t * bluelowSlider = lv_slider_create(scr);  
    lv_slider_set_range(bluelowSlider, 0, 360);  
    lv_slider_set_value(bluelowSlider, redhigh, LV_ANIM_OFF);  
    lv_obj_set_width(bluelowSlider, sliderWidth);  
    lv_obj_set_pos(bluelowSlider, 10, 120);  
    lv_obj_add_event_cb(bluelowSlider, bluelowSliderEventHandler, LV_EVENT_VALUE_CHANGED, NULL);

    bluelowLabel = lv_label_create(scr);
    lv_obj_set_pos(bluelowLabel, 220 , 120);  

    // blue high  
    lv_obj_t * bluehighSlider = lv_slider_create(scr);  
    lv_slider_set_range(bluehighSlider, 0, 360);  
    lv_slider_set_value(bluehighSlider, redhigh, LV_ANIM_OFF);  
    lv_obj_set_width(bluehighSlider, sliderWidth);  
    lv_obj_set_pos(bluehighSlider, 10, 170);  
    lv_obj_add_event_cb(bluehighSlider, bluehighSliderEventHandler, LV_EVENT_VALUE_CHANGED, NULL);

    bluehighLabel = lv_label_create(scr);
    lv_obj_set_pos(bluehighLabel, 220 , 170);

    // save button
    lv_obj_t * saveButton = lv_btn_create(scr);
    lv_obj_set_pos(saveButton, 100, 220);
    lv_obj_set_size(saveButton, 80, 40);
    lv_obj_add_event_cb(saveButton, savebuttonEventHandler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * saveLabel = lv_label_create(saveButton);
    lv_label_set_text(saveLabel, "save");
    lv_obj_center(saveLabel);
}