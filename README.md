# Multi-Partition SPIFFS for ESP32

Adapted from the build-in SPIFFS lib, this version allows using multiple SPIFFS partitions.

## Why?

Let's pretend you need to store some calibration data on the internal flash. That works. But what if you want to update some config files by uploading them from your PC? Your calibration data is gone, since the whole partition has been flashed.

Would be cool if you could use multiple partitions. But the build-in library to work with SPIFFS partitions always uses the first partition with the subtype `spiffs`. That's where this lib comes in.

## What?

The main change in comparison to the build-in lib is the option to specify a partition label with `Spiffs.begin(...)`. Additional important changes:

- Renamed header to `mpspiffs.hpp` to avoid confusion with `SPIFFS.h`.
- Renamed class `SPIFFSFS` to `SPIFFS` since the `FS` in `SPIFFS` already means filesystem.
- Renamed global object `SPIFFS` to `Spiffs` to avoid conflict with renamed class.

## Notes

- This was only tested on an ESP32. It probably won't work with an ESP8266 due to the threading functions called in `format()`.
- This was only tested with platformio.
- Uploading a FS image with platformio always writes to the last partition marked as `spiffs`.
- The underlying FS functions don't properly work with multiple partitions mounted at the same time. In order to avoid errors, a check was added to only allow mounting one partition at a time.
