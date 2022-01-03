OLED_ENABLE = no   # Enables the use of OLED displays
ENCODER_ENABLE = no       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
KEY_OVERRIDE_ENABLE = yes # Enable key overrides from JonasGessner (PR #11422)
MOUSEKEY_ENABLE = no     # Enable mouse keys

SRC += oneshot.c
SRC += swapper.c