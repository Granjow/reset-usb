#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    unsigned long USBDEVFS_RESET = 21780;
    auto path = "/dev/bus/usb/001/002";

    std::cout << "Resetting " << path << "." << std::endl;

    auto usbDev = open(path, O_WRONLY | O_NONBLOCK);
    ioctl(usbDev, USBDEVFS_RESET, 0);
    close(usbDev);

    return 0;
}
