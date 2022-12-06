#include QMK_KEYBOARD_H


#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

void triple_tap_dance_pair_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 3) {
        // immediately finish on third press
        register_code16(pair->kc2);
        state->finished = true;
    }
}

void triple_tap_dance_pair_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        register_code16(pair->kc1);
    } else if (state->count == 2) {
        // tap plus hold
        tap_code16(pair->kc1);
        register_code16(pair->kc1);
    } else if (state->count == 3) {
        register_code16(pair->kc2);
    }
}

void triple_tap_dance_pair_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1 || state->count == 2) {
        // 1-tap and 2-tap both result in `kc1` pressed so release it
        unregister_code16(pair->kc1);
    } else if (state->count == 3) {
        unregister_code16(pair->kc2);
    }
}

#define TRIPLE_TAP_DANCE_DOUBLE(kc1, kc2)  { .fn = {triple_tap_dance_pair_on_each_tap, triple_tap_dance_pair_finished, triple_tap_dance_pair_reset}, .user_data = (void *)&((qk_tap_dance_pair_t){kc1, kc2}), }

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
};

//Enum Tap Dance//
enum {
  MI_EQL = 0,
  LA_GUI,
  C_HME,
  C_END,
  C_Z,
  C_X,
  C_C,
  C_V,
  G_S_S
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [MI_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
  [LA_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
  [C_HME] = TRIPLE_TAP_DANCE_DOUBLE(KC_U, LCTL(KC_HOME)),
  [C_END] = TRIPLE_TAP_DANCE_DOUBLE(KC_O, LCTL(KC_END)),
  [C_Z]  = TRIPLE_TAP_DANCE_DOUBLE(KC_Z, LCTL(KC_Z)),
  [C_X]  = TRIPLE_TAP_DANCE_DOUBLE(KC_X, LCTL(KC_X)),
  [C_C]  = TRIPLE_TAP_DANCE_DOUBLE(KC_C, LCTL(KC_C)),
  [C_V]  = TRIPLE_TAP_DANCE_DOUBLE(KC_V, LCTL(KC_V)),
  [G_S_S] = TRIPLE_TAP_DANCE_DOUBLE(KC_S, LGUI(LSFT(KC_S)))
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_LAYER0] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,     KC_8,    KC_9,    KC_0, TD(MI_EQL),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,  TD(C_HME), KC_I,  TD(C_END), KC_P,   KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_A,  TD(G_S_S), KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, TD(C_Z), TD(C_X), TD(C_C), TD(C_V),  KC_B,   LT(2,KC_DEL),     KC_BSPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                              TD(LA_GUI), KC_SPC, LT(1,KC_ENT),              KC_SPC, KC_LEFT, KC_RGHT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LAYER1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                            KC_TRNS, KC_HOME,  KC_UP,   KC_END, KC_PGUP, KC_LBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLU, KC_MPLY, KC_MNXT,                            KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_MSTP, KC_MPRV, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LAYER2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_NUM, KC_CALC, KC_PSLS, KC_PAST, KC_PMNS, KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_HUI, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS,                            KC_WH_U,  KC_P7,   KC_P8,   KC_P9,  KC_PPLS, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_M_X, RGB_HUD, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,                            KC_WH_D,  KC_P4,   KC_P5,   KC_P6,  KC_PCMM, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_SAI, RGB_SAD, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS,          TG(3),  KC_TRNS,  KC_P1,   KC_P2,   KC_P3,  KC_PENT, KC_TRNS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    RGB_RMOD,RGB_MOD, KC_TRNS,                    KC_SPC,  KC_P0,   KC_PDOT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LAYER3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_LBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_G,            TG(3),    KC_N,    KC_M,  KC_COMM,  KC_DOT, KC_SLSH, KC_SFTENT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_TAB,  KC_M,  KC_SPC,                    KC_SPC, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LAYER0:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LAYER0);
      }
      return false;
      break;
    case LAYER1:
      if (record->event.pressed) {
        layer_on(_LAYER1);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      } else {
        layer_off(_LAYER1);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      }
      return false;
      break;
    case LAYER2:
      if (record->event.pressed) {
        layer_on(_LAYER2);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      } else {
        layer_off(_LAYER2);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      }
      return false;
      break;
    case LAYER3:
      if (record->event.pressed) {
        layer_on(_LAYER3);
      } else {
        layer_off(_LAYER3);
      }
      return false;
      break;
  }
  return true;
}