#include "transactions.h"
#include <stdio.h>

#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_KZ_EXPANDING_CIRCLES)
RGB_MATRIX_EFFECT(KZ_EXPANDING_CIRCLES)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

const int16_t kbx = 224; //Width of the keyboard.
const int16_t kby = 64; //Height of the keyboard.
const uint8_t qhue = 40; //How much the hue needs to change by.
const uint8_t qtime = 16; //The width of the interpolation gradient.

static int16_t cx = 0; //Circle expansion center X.
static int16_t cy = 0; //Circle expansion center Y.
static uint8_t cc = 0; //New color to interpolate towards.
static uint8_t prevTime; //Keeps track of time to identify a new cycle.

typedef struct _master_to_slave_t {
    uint8_t m2s_data;
} master_to_slave_t;

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    cx = (int16_t)m2s->m2s_data;
}

void user_sync_b_slave_handler(uint8_t in_buflen, const void* in_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    cy = (int16_t)m2s->m2s_data;
}

void user_sync_c_slave_handler(uint8_t in_buflen, const void* in_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    cx = m2s->m2s_data;
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
    transaction_register_rpc(USER_SYNC_B, user_sync_b_slave_handler);
    transaction_register_rpc(USER_SYNC_C, user_sync_c_slave_handler);
}

bool KZ_EXPANDING_CIRCLES(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) { //Initialize the state of the frame buffer.
        memset(g_rgb_frame_buffer, rgb_matrix_config.hsv.h, sizeof(g_rgb_frame_buffer));
    }

    //Whether or not it's time to generate new random colors.
    uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
    if(time < prevTime) {

        //Pick a random index of the list of LEDs
        int keys = sizeof(g_led_config.point) / sizeof(g_led_config.point[0]);
        int led = random8_max(keys);

        //Pull the X and Y coordinates from that.
        cx = g_led_config.point[led].x;
        cy = g_led_config.point[led].y;

        //Also get a new random hue value, based on the current hue setting.
        memset(g_rgb_frame_buffer, cc, sizeof(g_rgb_frame_buffer));
        //cc = cc + qhue + random8_max(qsub8(255, qhue));
        cc = rgb_matrix_config.hsv.h + random8_max(qsub8(128, qhue));

        master_to_slave_t m2s_a = (master_to_slave_t){(uint8_t)cx};
        master_to_slave_t m2s_b = (master_to_slave_t){(uint8_t)cy};
        master_to_slave_t m2s_c = (master_to_slave_t){cc};
        transaction_rpc_send(USER_SYNC_A, sizeof(m2s_a), &m2s_a);
        transaction_rpc_send(USER_SYNC_B, sizeof(m2s_b), &m2s_b);
        transaction_rpc_send(USER_SYNC_C, sizeof(m2s_c), &m2s_c);
    }
    prevTime = time;


    //Main loop: process for every key on the board.
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv1 = (HSV){rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v};

        //Do math to determine the circle center.
        int16_t dx = g_led_config.point[i].x - cx;
        int16_t dy = g_led_config.point[i].y - cy;
        uint8_t dist = sqrt16(dx * dx + dy * dy);
        uint8_t j = i % 10;
        uint8_t k = i / 10;

        //Blend colors together based on time and distance from effect center.
        if(qsub8(time, dist) <= qtime) { //If time is over the max difference, the color is totally replaced.
            hsv1.h = g_rgb_frame_buffer[j][k];
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv1);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else if(qsub8(time, dist) >= mul8(qtime, 2)) { //If time is under the minimum difference, the color is not replaced.
            hsv1.h = cc;
            g_rgb_frame_buffer[j][k] = cc;
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv1);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else { //Otherwise, the color is linearly interpolated.
            //New code linearly interpolating RGB values.
            hsv1.h = g_rgb_frame_buffer[j][k];
            HSV hsv2 = (HSV){cc, hsv1.s, hsv1.v};
            RGB rgb1 = rgb_matrix_hsv_to_rgb(hsv1);
            RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv2);
            uint8_t diff = qmul8(qsub8(qsub8(time, dist), qtime), 16);
            uint8_t r = blend8(rgb1.r, rgb2.r, diff);
            uint8_t g = blend8(rgb1.g, rgb2.g, diff);
            uint8_t b = blend8(rgb1.b, rgb2.b, diff);
            rgb_matrix_set_color(i, r, g, b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // RGB_MATRIX_FRAMEBUFFER_EFFECTS && ENABLE_RGB_MATRIX_KZ_EXPANDING_CIRCLES
