#ifdef ENABLE_RGB_MATRIX_KZ_CUSTOM
RGB_MATRIX_EFFECT(KZ_CUSTOM)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//Absolute maximum brightness
static const uint16_t vmax = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
//Ratio of minimum brightness compared to max.
static const uint16_t vmin = (uint16_t)(vmax / 3);
static const uint16_t vmid = (uint16_t)((vmax * 2) / 3);

static HSV KZ_CUSTOM_math(HSV hsv, uint8_t i, uint8_t time) {

    //Next we gotta figure out what row our keys are on.
    uint8_t row_offset = 0;
    if((i >= 6 && i <= 11) || (i >= 40 && i <= 45)) {
        row_offset = 1;
    } else if((i >= 12 && i <= 17) || (i >= 46 && i <= 51)) {
        row_offset = 2;
    } else if((i >= 18 && i <= 23) || (i >= 52 && i <= 57) || (i >= 28 && i <= 33) || (i >= 62 && i <= 67)) {
        row_offset = 3;
    } else if((i >= 24 && i <= 27) || (i >= 58 && i <= 61)) {
        row_offset = 4;
    }

    //Special color cases for different layers
    bool briter = false;
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 1:
            //When the LOWER layout is active, we highlight the virtual numpad and the cursor keys.
            if(i == 8 || i == 14 || i == 15 || i == 16 || i == 36 || i == 37 || i == 38 || i == 41 || i == 42 || i == 43 || i == 48 || i == 49 || i == 50 || i == 53) {
                hsv.h = 90;
                briter = true;
                break;
            } else if(i == 9 || i == 7 || i == 54 || i == 55) {
                hsv.h = 90;
                hsv.s = hsv.s / (uint8_t)2;
                briter = true;
                break;
            }
            hsv.h = 155 + (((hsv.h / (uint8_t)8) - (uint8_t)16) * row_offset);
            break;
        case 2:
            //This is for the Raise layout where we highlight the RGB effect keys.
            if(i == 39) { //On/Off Switch.
                hsv.s = 0;
                briter = true;
                break;
            } else if(i == 38) { //Plain Color Switch.
                hsv.h = 170;
                hsv.s = hsv.s / 2;
                break;
            } else if(i == 37) { //Shift Pattern Backward
                hsv.h = 230;
                briter = true;
                break;
            } else if(i == 36) { //Shift Pattern Forwards
                hsv.h = 210;
                briter = true;
                break;
            } else if(i == 35) { //Pattern Speed Up
                hsv.h = 170;
                time = time * 3;
                briter = true;
                break;
            } else if(i == 34) { //Pattern Speed Down
                hsv.h = 170;
                time = time * 2;
                briter = true;
                break;
            } else if(i == 40 || i == 41) { //Hue Shift Keys
                hsv.h = time;
                return hsv;
            } else if(i == 42 || i == 43) { //Saturation Shift Keys
                hsv.h = 170;
                hsv.s = time;
                return hsv;
            } else if(i == 44 || i == 45) { //Value Shift Keys
                hsv.h = 170;
                hsv.s = 0;
                hsv.v = (uint8_t)(((uint16_t)sin8_C(time - g_led_config.point[i].x - (row_offset * (uint8_t)16) - 16 ) * hsv.v) / (uint16_t)255);
                return hsv;
            } else if(i >= 13 && i <= 16) { //Caps, Num, Scroll, Insert.
                hsv.h = 220;
                briter = true;
                break;
            }
            hsv.h = 185 + (((hsv.h / (uint8_t)8) - (uint8_t)16) * row_offset);
            break;
        case 3:
            if(i == 52) { //Alt+F4
                hsv.h = 0;
                briter = true;
                break;
            } else if(i == 53) { //Alt+Tab
                hsv.h = 20;
                briter = true;
                break;
            } else if(i == 54) { //Win+D
                hsv.h = 30;
                briter = true;
                break;
            } else if(i == 51) { //Win+Shift+S
                hsv.h = 160;
                briter = true;
                break;
            } else if(i == 50) { //Alt+Enter
                hsv.h = 50;
                briter = true;
                break;
            } else if(i == 49) { //Win+L
                hsv.h = 115;
                briter = true;
                break;
            }
            hsv.h = 170;
            hsv.s = hsv.s / (uint8_t)2;
            break;
        default:
            hsv.h = 170 + (((hsv.h / (uint8_t)8) - (uint8_t)16) * row_offset);
            break;
    }

    //We define local maxes and mins, based on current hsv value.
    uint16_t max_brite = hsv.v;
    uint16_t min_brite;
    if(briter) {
        min_brite = (uint8_t)(((uint16_t)hsv.v * vmid) / vmax);
    } else {
        min_brite = (uint8_t)(((uint16_t)hsv.v * vmin) / vmax);
    }

    //Now we make the cool cycling value wave happen.
    if(i <= 23 || (i >= 29 && i <= 33)) {
        hsv.v = (uint8_t)((((uint16_t)sin8_C(time - g_led_config.point[i].x - (row_offset * (uint8_t)16) - 16 ) * (max_brite - min_brite)) / (uint16_t)255) + min_brite);
    } else if ((i >= 34 && i <= 57) || (i >= 63 && i <= 67)) {
        hsv.v = (uint8_t)((((uint16_t)sin8_C(time + g_led_config.point[i].x - (row_offset * (uint8_t)16)) * (max_brite - min_brite)) / (uint16_t)255) + min_brite);
    } else {
        if(i == 25 || i == 59) {
            hsv.s = 0;
        } if(i == 27 || i == 61) {
            hsv.h = 12;
        } else {
            hsv.h = 28;
        }
    }

    return hsv;
}

bool KZ_CUSTOM(effect_params_t* params) {
    return effect_runner_i(params, &KZ_CUSTOM_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN_FRAMED
