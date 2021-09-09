EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
ENCODER_ENABLE = yes

OLED_ENABLE = no
RGBLIGHT_ENABLE = no

EXTRAFLAGS += -flto

SRC += encoder.c \
	   #oled.c \
	   

