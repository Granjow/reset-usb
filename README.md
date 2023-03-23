# USB Hub Reset

Background: https://forums.raspberrypi.com/viewtopic.php?t=305993

CP210x USB-UART converters can disconnect if more than one converter is attached.
This is fixed in Linux kernel version 5.12. Before that, the USB hub needs to be
disconnected and connected again.

On a Raspberry Pi 4, the internal USB 2.0 hub is `/dev/bus/usb/001/002`. If a
USB-UART converter is connected to an external USB hub, this hub has its own
path which can be found with `lsusb` (use `lsusb -v` for more information). If
it is not obvious which one needs to be reset, simply test resetting each of
them.

Code adapted from https://github.com/mcarans/resetusb/blob/master/reset_usb.py

```text
[20130.924827] cp210x ttyUSB4: failed set request 0x0 status: -110
[20130.924865] cp210x ttyUSB4: cp210x_open - Unable to enable UART
```
