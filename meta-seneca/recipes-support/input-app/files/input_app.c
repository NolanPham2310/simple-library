#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main() {

const char *device_path = "/dev/input/event0";
int fd = open(device_path, O_RDONLY);
if (fd ==-1) {
perror("Error opening device");
exit(EXIT_FAILURE);
}
struct input_event ev;
while (1) {
ssize_t bytesRead = read(fd, &ev, sizeof(struct input_event));
if (bytesRead ==-1) {
perror("Error reading event");
break;
}
if (bytesRead == sizeof(struct input_event)) {
printf("Event type: %d, code: %d, value: %d\n", ev.type, ev.code, ev.value);
}
}
close(fd);
return 0;
}
