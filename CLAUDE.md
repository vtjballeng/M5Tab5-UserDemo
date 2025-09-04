# Claude Code Build Notes for M5Tab5-UserDemo

## Build Environment Requirements

### ESP-IDF Version
**IMPORTANT:** This project requires ESP-IDF v5.4.1 for proper functionality, especially for touchscreen support.

- **Required Version:** ESP-IDF v5.4.1
- **Target:** ESP32-P4

### Known Issues with Other Versions
- ESP-IDF v5.5.x causes touchscreen functionality to fail (GT911 touchscreen controller compatibility issues)
- Component API changes in v5.5.x may require code modifications

## Build Instructions

### 1. Install ESP-IDF v5.4.1
```bash
cd ~
git clone -b v5.4.1 --recursive https://github.com/espressif/esp-idf.git esp-idf-v5.4.1
cd esp-idf-v5.4.1
./install.sh esp32p4
```

### 2. Clean Build Environment
Before building, ensure a clean environment:
```bash
cd /path/to/M5Tab5-UserDemo/platforms/tab5
rm -rf build CMakeCache.txt managed_components
```

### 3. Build the Project
```bash
export IDF_PATH=/home/$USER/esp-idf-v5.4.1
source $IDF_PATH/export.sh
idf.py build
```

### 4. Flash to Device

#### Option A: Using IDF Tool (Recommended for development)
```bash
idf.py flash
```

#### Option B: Using esptool directly
```bash
python -m esptool --chip esp32p4 -b 460800 --before default_reset --after hard_reset write_flash \
  --flash_mode dio --flash_size 16MB --flash_freq 80m \
  0x2000 build/bootloader/bootloader.bin \
  0x8000 build/partition_table/partition-table.bin \
  0x10000 build/m5stack_tab5.bin
```

#### Option C: Using ESP Flash Download Tool (Windows GUI)
For Windows users who prefer a GUI tool, use the [ESP Flash Download Tool](https://www.espressif.com/en/support/download/other-tools):

1. Download and run the ESP Flash Download Tool
2. Select **ESP32-P4** as the chip type
3. Configure the following files and addresses:

| File Path (relative to build/) | Address | Required |
|--------------------------------|---------|----------|
| `bootloader/bootloader.bin` | 0x2000 | Yes |
| `partition_table/partition-table.bin` | 0x8000 | Yes |
| `m5stack_tab5.bin` | 0x10000 | Yes |

**Flash Settings:**
- **SPI SPEED:** 80MHz
- **SPI MODE:** DIO
- **FLASH SIZE:** 16MB (128Mbit)
- **BAUD:** 460800 (can be increased to 921600 for faster flashing)

4. Connect your M5Tab5 to the PC via USB-C
5. Select the correct COM port
6. Click **START** to begin flashing

**Note:** The flash_args file in the build directory contains these exact parameters and can be used as reference.

## Component Dependencies
The project uses the following key components (as defined in dependencies.lock):
- LVGL v8.4.0 (GUI framework)
- ESP LCD Touch GT911 v1.1.3 (touchscreen driver)
- ESP Codec Dev v1.3.4 (audio codec support)
- ESP H264 v1.0.4 (video encoding)

## Troubleshooting

### Touchscreen Not Working
- Ensure you're using ESP-IDF v5.4.1, not v5.5.x
- Check that the GT911 touchscreen driver is properly initialized in the BSP

### Build Errors with ESP-IDF v5.5.x
If you accidentally use v5.5.x and encounter build errors:
1. The ES7120_SEL_MIC constants have been renamed to ES7210_SEL_MIC in newer esp_codec_dev versions
2. Component dependencies may need updating via `idf.py update-dependencies`
3. However, this may break touchscreen functionality - reverting to v5.4.1 is recommended

### CMake Cache Issues
If you encounter CMake cache errors when switching between ESP-IDF versions or between Windows and WSL:
```bash
rm -rf build CMakeCache.txt CMakeFiles/
```

## Build Output
- Binary size: ~5.7 MB
- Flash size: 16 MB
- Free space after flashing: ~45%

## Testing Commands
To verify the build and installation:
```bash
# Check ESP-IDF version
export IDF_PATH=/home/$USER/esp-idf-v5.4.1
source $IDF_PATH/export.sh
idf.py --version  # Should show: ESP-IDF v5.4.1

# Monitor serial output
idf.py monitor
```

## Notes for Future Development
- Always clean build artifacts when switching ESP-IDF versions
- The project includes hardware tests for various M5Tab5 components (touchscreen, audio, camera, etc.)
- The main demo application can be found in `/app/apps/app_launcher/`