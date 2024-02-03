#ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT_QUARTER
RGB_MATRIX_EFFECT(CYCLE_LEFT_RIGHT_QUARTER)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
static HSV CYCLE_LEFT_RIGHT_QUARTER_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = hsv.h + (sin8_C((uint8_t)g_led_config.point[i].x - time) / 4);
    return hsv;
}

bool CYCLE_LEFT_RIGHT_QUARTER(effect_params_t* params) {
    return effect_runner_i(params, &CYCLE_LEFT_RIGHT_QUARTER_math);
}
#    endif
#endif     // ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT_QUARTER

#ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT_THIRD
RGB_MATRIX_EFFECT(CYCLE_LEFT_RIGHT_THIRD)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
static HSV CYCLE_LEFT_RIGHT_THIRD_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = hsv.h + (sin8_C((uint8_t)g_led_config.point[i].x - time) / 3);
    return hsv;
}

bool CYCLE_LEFT_RIGHT_THIRD(effect_params_t* params) {
    return effect_runner_i(params, &CYCLE_LEFT_RIGHT_THIRD_math);
}
#    endif
#endif     // ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT_THIRD

#ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT_HALF
RGB_MATRIX_EFFECT(CYCLE_LEFT_RIGHT_HALF)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
static HSV CYCLE_LEFT_RIGHT_HALF_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = hsv.h + (sin8_C((uint8_t)g_led_config.point[i].x - time) / 2);
    return hsv;
}

bool CYCLE_LEFT_RIGHT_HALF(effect_params_t* params) {
    return effect_runner_i(params, &CYCLE_LEFT_RIGHT_HALF_math);
}
#    endif
#endif     // ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT_HALF
