#ifdef ENABLE_RGB_MATRIX_KZ_CUSTOM
RGB_MATRIX_EFFECT(KZ_CUSTOM)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//Absolute maximum brightness
static const uint16_t vmax = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
//Ratio of minimum brightness compared to max.
static const uint16_t vmin = (uint16_t)(vmax / 3);

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
    hsv.h = 170 + (((hsv.h / (uint8_t)8) - (uint8_t)16) * row_offset);

    //We define local maxes and mins, based on current hsv value.
    uint16_t max_brite = hsv.v;
    uint16_t min_brite = (uint8_t)(((uint16_t)hsv.v * vmin) / vmax);

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
