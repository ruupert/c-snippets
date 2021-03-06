/* See LICENSE file for copyright and license details. */
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sysctl.h>

#include "../util.h"

const char *
mybattery_perc(const char *bat)
{

  int state, time, life;
  size_t len;
  char *res;
  res = malloc(sizeof(char)*20);
  len = sizeof(int);
  sysctlbyname("hw.acpi.battery.state", &state, &len, NULL, 0);
  sysctlbyname("hw.acpi.battery.time", &time, &len, NULL, 0);
  sysctlbyname("hw.acpi.battery.life", &life, &len, NULL, 0);
  
  //  if (state == 0) {
  // 	sprintf(res, "%lc %lc", (wint_t)128267, 0x2587);
  // }
  
  if (life >= 84) {
	sprintf(res, "%lc", 0x2587);
	  
  } else if (life < 84 && life >= 68) {
	sprintf(res, "%lc", 0x2586);
	  
  } else if (life < 68 && life >= 52) {
	sprintf(res, "%lc", 0x2585);

  } else if (life < 52 && life >= 36) {
	sprintf(res, "%lc", 0x2583);
	  
  } else if (life < 36 && life >= 16) {
	sprintf(res, "%lc", 0x2582);
	  
  } else if (life < 16) {

	sprintf(res, "%lc", 0x2581);
	  
  }
  
  return (char*) res;  
}

const char *
mybattery_power(void)
{
  return "";
  /*	int watts;
	char path[PATH_MAX];

	snprintf(path, sizeof(path), "%s%s%s", "/sys/class/power_supply/", bat, "/power_now");
	return (pscanf(path, "%i", &watts) == 1) ?
	bprintf("%d", (watts + 500000) / 1000000) : NULL;*/
}

const char *
mybattery_state(void)
{
  /*	struct {
		char *state;
		char *symbol;
	} map[] = {
		{ "Charging",    "+" },
		{ "Discharging", "-" },
		{ "Full",        "=" },
		{ "Unknown",     "/" },
	};
	size_t i;
	char path[PATH_MAX], state[12];

	snprintf(path, sizeof(path), "%s%s%s", "/sys/class/power_supply/", bat, "/status");
	if (pscanf(path, "%12s", state) != 1) {
		return NULL;
	}

	for (i = 0; i < LEN(map); i++) {
		if (!strcmp(map[i].state, state)) {
			break;
		}
	}
	return (i == LEN(map)) ? "?" : map[i].symbol;*/
  return "";
}
