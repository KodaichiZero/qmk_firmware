#ifdef ENABLE_RGB_MATRIX_KZ_CUSTOM
RGB_MATRIX_EFFECT(KZ_CUSTOM)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//The magic string of numbers that defines the shape of the hexagons.
static const bool pat[14] = {1,1,0,0,0,0,0,1,1,0,1,1,1,0};
static const uint8_t spacing = 8;
static const uint8_t grad = 4;

/*
bool KZ_CUSTOM(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV     hsv   = rgb_matrix_config.hsv;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        // The y range will be 0..64, map this to 0..4
        // Relies on hue being 8-bit and wrapping
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
		rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}
*/

static HSV KZ_CUSTOM_math(HSV hsv, uint8_t i, uint8_t time) {
    uint8_t v = grad;
    for(uint8_t c = 0; c < grad; c++) {
        uint8_t index = (time + c + (g_led_config.point[i].x / 2) + ((g_led_config.point[i].y / 3))) % (sizeof(pat) * spacing);
        if(pat[index / spacing]) v++;
    }
    hsv.v = (uint8_t)(((int)hsv.v * v) / (grad * 2));
    return hsv;
}

bool KZ_CUSTOM(effect_params_t* params) {
    return effect_runner_i(params, &KZ_CUSTOM_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN_FRAMED
