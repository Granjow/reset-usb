#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

auto ARG_RESET = "--reset";
auto ARG_DONTRUN = "-n";

void printUsage() {
    std::cout << "Usage:" << std::endl
              << ARG_RESET << " <path>\tReset USB device at path, on the Raspi 4 usually /dev/bus/usb/001/002" << std::endl
              << ARG_DONTRUN << "\tDon't actually execute anything" << std::endl;
}

void resetUsbDevice(const char *path, bool really) {

    unsigned long USBDEVFS_RESET = 21780;

    std::cout << "Resetting " << path << "." << std::endl;

    if (really) {
        auto usbDev = open(path, O_WRONLY | O_NONBLOCK);
        ioctl(usbDev, USBDEVFS_RESET, 0);
        close(usbDev);
    } else {
        std::cout << "(not really)" << std::endl;
    }
}

enum {
    ArgAny,
    ArgReset,
} nextArg = ArgAny;

enum {
    CmdNone,
    CmdHelp,
    CmdReset,
} commandToRun = CmdNone;

int main(int argc, char const *argv[]) {

    std::vector<std::string_view> args(argv + 1, argv + argc);

    bool really = true;
    std::string_view resetPath;

    if (args.empty()) {
        std::cerr << "No arguments given." << std::endl;
        printUsage();
        return 1;
    }

    for (auto arg: args) {
        switch (nextArg) {
            case ArgAny:
                if (arg == ARG_DONTRUN) {
                    really = false;
                } else if (arg == ARG_RESET) {
                    commandToRun = CmdReset;
                    nextArg = ArgReset;
                } else if (arg == "-h" || arg == "--help") {
                    commandToRun = CmdHelp;
                }
                break;
            case ArgReset:
                resetPath = arg;
                nextArg = ArgAny;
                break;
        }
    }

    if (nextArg != ArgAny) {
        std::cerr << "Argument missing." << std::endl;
        printUsage();
        return 1;
    }

    switch (commandToRun) {
        case CmdNone:
            std::cout << "No command specified, not doing anything. (Check --help.)" << std::endl;
            return 0;
        case CmdHelp:
            printUsage();
            return 0;
        case CmdReset:
            resetUsbDevice(std::string(resetPath).c_str(), really);
            return 0;
    }
}
