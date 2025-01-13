#!/bin/bash
# Script to set the LED for mic mute

LED_USER="/usr/local/bin/led_set"
LED_NAME="platform::micmute"
LED_BRIGHTNESS=0

if [[ -x "$LED_USER" ]]; then
    $LED_USER "$LED_NAME" "$LED_BRIGHTNESS"
else
    echo "Error: $LED_USER not found or not executable" >&2
fi

