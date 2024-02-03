#ifdef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
RGB_MATRIX_EFFECT(GRADIENT_UP_DOWN_FRAMED)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//Desaturation Algorithm by KodaichiZero.
//i = led index, r_in = supplied RGB value, sat = amount of saturation to maintain. 255 = full color, 0 = grayscale.
void desaturate(uint8_t i, RGB r_in, int sat) {
    uint8_t fr = r_in.r;
    uint8_t fg = r_in.g;
	uint8_t fb = r_in.b;
	uint8_t av = ((fr + fg + fb) / (uint8_t)3);
	fr = (uint8_t)(((fr * sat) + (av * (255 - sat))) / 255);
    fg = (uint8_t)(((fg * sat) + (av * (255 - sat))) / 255);
	fb = (uint8_t)(((fb * sat) + (av * (255 - sat))) / 255);
    rgb_matrix_set_color(i, fr, fg, fb);
}

//This is mostly the same as the existing GRADIENT_UP_DOWN except that large sections are desaturated by a specific amount.
bool GRADIENT_UP_DOWN_FRAMED(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV     hsv   = rgb_matrix_config.hsv;
    uint8_t scale = scale8(64, rgb_matrix_config.speed);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        // The y range will be 0..64, map this to 0..4
        // Relies on hue being 8-bit and wrapping
		hsv.h = rgb_matrix_config.hsv.h + ((scale * g_led_config.point[i].y) >> 4);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);

		if ((i >= 6 && i <= 10) || (i >= 13 && i <= 17) || (i >= 18 && i <= 22) || (i >= 40 && i <= 44) || (i >= 47 && i <= 51) || (i >= 52 && i <= 56)) {
            desaturate(i, rgb, 50);
		} else {
			rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
		}
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN_FRAMED
