# ESP32 LeetCode Statistics Dashboard

A real-time LeetCode statistics dashboard built with ESP32 and TFT display. This project fetches your LeetCode profile data and displays it on a beautiful TFT screen with animated progress arcs.

## 🚀 Features

- **Real-time LeetCode Stats**: Fetches and displays your current LeetCode statistics
- **Beautiful UI**: Custom-designed interface with smooth arc progress indicators
- **WiFi Integration**: Connects to your WiFi network to fetch data from LeetCode API
- **Auto-refresh**: Updates statistics every 30 seconds
- **Error Handling**: Graceful handling of network errors and user not found scenarios

## 📊 Display Information

The dashboard shows:
- **Username**: Your LeetCode username
- **Ranking**: Your current LeetCode ranking
- **Rating**: Your reputation/rating
- **Submissions**: Total number of submissions
- **Problem Statistics**: 
  - Total problems solved (with progress arc)
  - Easy problems solved
  - Medium problems solved  
  - Hard problems solved

## 🛠️ Hardware Requirements

- **ESP32 Development Board** (ESP32 DevKit, NodeMCU-32S, etc.)
- **TFT Display** (compatible with TFT_eSPI library)
- **USB Cable** for programming and power
- **WiFi Network** for internet connectivity

## 📋 Software Requirements

- **PlatformIO** (recommended) or Arduino IDE
- **Required Libraries**:
  - `TFT_eSPI` (v2.5.43 or higher)
  - `ArduinoJson` (v6.21.4 or higher)

## 🔧 Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/esp_dash.git
cd esp_dash
```

### 2. Configure Your Settings

Edit `src/main.cpp` and update the following constants:

```cpp
#define USERNAME "YourLeetCodeUsername"
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"
```

### 3. TFT Display Configuration

Configure your TFT display settings in the TFT_eSPI library configuration file. The project uses:
- Screen rotation: 3 (landscape)
- Resolution: 320x240 (adjust based on your display)

### 4. Build and Upload

Using PlatformIO:
```bash
pio run --target upload
```

Using Arduino IDE:
1. Open `src/main.cpp` in Arduino IDE
2. Install required libraries from Library Manager
3. Select your ESP32 board
4. Upload the code

## 🔌 Pin Connections

Connect your TFT display to the ESP32 according to your display's specifications. Common connections include:

- **VCC** → 3.3V
- **GND** → GND
- **SCK** → GPIO18
- **MOSI** → GPIO23
- **CS** → GPIO5
- **DC** → GPIO2
- **RST** → GPIO4

*Note: Pin assignments may vary based on your specific TFT display model.*

## 🌐 API Integration

The project uses the LeetCode API hosted at `leetcodestat.vercel.app` to fetch user statistics. The API endpoint format is:
```
https://leetcodestat.vercel.app/api/leetcode/{username}
```

## 📱 Usage

1. **Power On**: Connect the ESP32 to power via USB
2. **WiFi Connection**: The device will attempt to connect to your configured WiFi network
3. **Data Fetching**: Once connected, it will fetch your LeetCode statistics
4. **Display**: Your stats will be displayed on the TFT screen with animated progress arcs
5. **Auto-refresh**: Statistics update automatically every 30 seconds

## 🎨 UI Components

- **Progress Arcs**: Visual representation of solved problems vs total problems
- **Color Coding**: 
  - Green: Total problems and general stats
  - Blue: Easy problems
  - Orange: Medium problems
  - Red: Hard problems
- **Error Screens**: Informative error messages for network issues and user not found

## 🔧 Customization

### Update Interval
Change the refresh interval by modifying:
```cpp
#define FETCH_INTERVAL 30000  // 30 seconds in milliseconds
```

### Display Colors
Customize colors in `src/ui.cpp`:
```cpp
#define green 0x6e28
#define easyCol 0x063f
#define mediumCol 0xffc0
#define hardCol 0xf980
```

### Problem Counts
Adjust the total problem counts for accurate progress calculation:
```cpp
int medQue = 2000;    // Total medium problems
int hardQue = 900;    // Total hard problems
int easyQue = 900;    // Total easy problems
int totalQue = 3600;  // Total problems
```

## 🐛 Troubleshooting

### WiFi Connection Issues
- Verify your WiFi credentials in the code
- Check if your WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)
- Ensure the WiFi signal is strong enough

### Display Issues
- Check TFT display connections
- Verify TFT_eSPI library configuration
- Adjust screen rotation if needed

### API Issues
- Verify your LeetCode username is correct
- Check internet connectivity
- The API may have rate limits

## 📝 License

This project is open source and available under the [MIT License](LICENSE).

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📞 Support

If you encounter any issues or have questions:
1. Check the troubleshooting section above
2. Open an issue on GitHub
3. Ensure you're using the latest version of the code

## 🙏 Acknowledgments

- [TFT_eSPI Library](https://github.com/Bodmer/TFT_eSPI) for display functionality
- [ArduinoJson Library](https://github.com/bblanchon/ArduinoJson) for JSON parsing
- LeetCode for providing the statistics API

---

**Happy Coding! 🚀** 