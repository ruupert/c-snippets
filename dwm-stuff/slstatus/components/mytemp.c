/* See LICENSE file for copyright and license details. */
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sysctl.h>

#include "../util.h"

const char *
mytemp_perc(const char *bat)
{

  int temp;
  size_t len;
  char *res;
  res = malloc(sizeof(char)*20);
  len = sizeof(int);
  sysctlbyname("hw.acpi.thermal.tz0.temperature", &temp, &len, NULL, 0);
  sprintf(res, "%dC", temp);
  return (char*) res;  
}

