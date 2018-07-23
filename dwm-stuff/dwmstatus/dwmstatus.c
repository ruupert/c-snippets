#define _BSD_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <wchar.h>
#include <locale.h>

#include <X11/Xlib.h>

//char *tzutc = "UTC"
char *tzhelsinki = "Europe/Helsinki";

static Display *dpy;

char *
smprintf(char *fmt, ...)
{
  va_list fmtargs;
  char *ret;
  int len;

  va_start(fmtargs, fmt);
  len = vsnprintf(NULL, 0, fmt, fmtargs);
  va_end(fmtargs);

  ret = malloc(++len);
  if (ret == NULL) {
	perror("malloc");
	exit(1);
  }

  va_start(fmtargs, fmt);
  vsnprintf(ret, len, fmt, fmtargs);
  va_end(fmtargs);

  return ret;
}

void
settz(char *tzname)
{
  setenv("TZ", tzname, 1);
}

char *
mktimes(char *fmt, char *tzname)
{
  char buf[129];
  time_t tim;
  struct tm *timtm;

  memset(buf, 0, sizeof(buf));
  settz(tzname);
  tim = time(NULL);
  timtm = localtime(&tim);
  if (timtm == NULL) {
	perror("localtime");
	exit(1);
  }

  if (!strftime(buf, sizeof(buf)-1, fmt, timtm)) {
	fprintf(stderr, "strftime == 0\n");
	exit(1);
  }

  return smprintf("%s", buf);
}

void
setstatus(char *str)
{
  XStoreName(dpy, DefaultRootWindow(dpy), str);
  XSync(dpy, False);
}

char *
loadavg(void)
{
  double avgs[3];

  if (getloadavg(avgs, 3) < 0) {
	perror("getloadavg");
	exit(1);
  }

  return smprintf("%.2f %.2f %.2f", avgs[0], avgs[1], avgs[2]);
}

char *
batterylife(void) {

  int state, time, life;
  size_t len;
  char *res;
  res = malloc(sizeof(char)*20);
  len = sizeof(int);
  sysctlbyname("hw.acpi.battery.state", &state, &len, NULL, 0);
  sysctlbyname("hw.acpi.battery.time", &time, &len, NULL, 0);
  sysctlbyname("hw.acpi.battery.life", &life, &len, NULL, 0);
  
  if (state == 0) {
	if (life >= 84) {
	  sprintf(res, "%lc %lc", (wint_t)128267, 0x2587);
	  
	} else if (life < 84 && life >= 68) {
	  sprintf(res, "%lc %lc", (wint_t)128267, 0x2586);
	  
	} else if (life < 68 && life >= 52) {
	  sprintf(res, "%lc %lc", (wint_t)128267, 0x2585);

	} else if (life < 52 && life >= 36) {
	  sprintf(res, "%lc %lc", (wint_t)128267, 0x2583);
	  
	} else if (life < 36 && life >= 16) {
	  sprintf(res, "%lc %lc", (wint_t)128267, 0x2582);
	  
	} else if (life < 16) {
	  sprintf(res, "%lc %lc", (wint_t)128267, 0x2581);
	  
	}
	
  } else {
	sprintf(res, "%lc %time min", (wint_t)128267, time);
  }
  
  
  return (char*) res;  
}

int
main(void)
{
  setlocale(LC_ALL, "");

  char *status;
  char *avgs;
  //	char *tmar;
  //	char *tmutc;
  char *tmhki;
  char *battery;
  
  if (!(dpy = XOpenDisplay(NULL))) {
	fprintf(stderr, "dwmstatus: cannot open display.\n");
	return 1;
  }
	
  for (;;sleep(90)) {
	avgs = loadavg();
	battery = batterylife();
	//		tmar = mktimes("%H:%M", tzargentina);
	// tmutc = mktimes("%H:%M", tzutc);
	tmhki = mktimes("%Y-%m-%d %H:%M", tzhelsinki);
	  
	status = smprintf("%s, L:%s, %s",
					  battery, avgs, tmhki);
	setstatus(status);
	free(avgs);
	free(battery);
	free(tmhki);
	free(status);
  }
	
  XCloseDisplay(dpy);
	
  return 0;
}

