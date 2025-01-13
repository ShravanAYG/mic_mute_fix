#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char sysfs_led_path[] = "/sys/class/leds/";
const char sysfs_file_brightness[] = "/brightness";

struct led_sys
{
	char name[32];
	unsigned int brightness;
};

char *cat_path(const char *name, const char *suffix) {
	size_t len = strlen(name) + strlen(sysfs_led_path) + strlen(suffix) + 1;
	char *r = calloc(len, sizeof(char));

	snprintf(r, len, "%s%s%s", sysfs_led_path, name, suffix);

	return r;
}

int led_get_brightness(struct led_sys *led) {
	unsigned int brightness = 0;
	char *brightness_file = cat_path(led->name, sysfs_file_brightness);
	FILE *led_fp = fopen(brightness_file, "r");

	if (!led_fp || fscanf(led_fp, "%u", &brightness) != 1) {
		free(brightness_file);
		return 0;
	}
	fclose(led_fp);
	free(brightness_file);
	led->brightness = brightness;

	return 1;
}

int led_set_brightness(unsigned int brightness, struct led_sys *led) {
	char *brightness_file = cat_path(led->name, sysfs_file_brightness);
	FILE *led_fp = fopen(brightness_file, "w");

	if (!led_fp || fprintf(led_fp, "%u", brightness) != 1) {
		free(brightness_file);
		return 0;
	}
	fclose(led_fp);
	free(brightness_file);
	led->brightness = brightness;

	return 1;
}

int main(int argc, char *argv[]) {
	struct led_sys led;
	int brightness = 0;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <LED_NAME> <BRIGHTNESS_VALUE>\n", argv[0]);
		return EXIT_FAILURE;
	}

	strncpy(led.name, argv[1], sizeof(led.name) - 1);
	led.name[sizeof(led.name) - 1] = '\0';

	char *endptr;
	brightness = strtol(argv[2], &endptr, 10);
	if (*endptr != '\0' || brightness < 0) {
		fprintf(stderr, "Invalid brightness value: %s\n", argv[2]);
		return EXIT_FAILURE;
	}

	if (led_set_brightness(brightness, &led)) {
		printf("Brightness of %s set to: %u\n", led.name, led.brightness);
	}
	else {
		fprintf(stderr, "Failed to set brightness for %s\n", led.name);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

