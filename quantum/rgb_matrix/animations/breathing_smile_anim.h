#ifdef ENABLE_RGB_MATRIX_BREATHING_SMILE
RGB_MATRIX_EFFECT(BREATHING_SMILE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool BREATHING_SMILE(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV      hsv  = rgb_matrix_config.hsv;
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
		RGB_MATRIX_TEST_LED_FLAGS();
		if (i == 1 || i == 4 || (i >= 13 && i <= 16) || i == 20 || i == 21) {
			rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
		} else if (i == 35 || i == 38 || (i >= 47 && i <= 50) || i == 54 || i == 55) {
			rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
		} else {
			rgb_matrix_set_color(i, (uint8_t)0, (uint8_t)0, (uint8_t)0);
		}
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_BREATHING_SMILE
