# ThunderFix

**ThunderFix** is a high-performance, low-latency C++ FIX protocol library designed for high-frequency trading, real-time market data parsing, and order management in financial systems. This library provides a modular design with support for risk management, load balancing, logging, message replay, dynamic resource management, and other advanced features, making it ideal for demanding high-load environments.

## Features

1. **Multi-Version Support**: Supports different versions of the FIX protocol (e.g., 4.0, 4.2, 4.4) to accommodate diverse requirements.
2. **Low-Latency Design**: Utilizes `asio` for asynchronous I/O, optimized memory management for efficient message processing.
3. **Modular Structure**: Core and extension modules are separated for ease of maintenance and expandability.
4. **Advanced Risk Management**: Includes multi-level risk controls, such as order limits, daily position limits, and loss limits.
5. **Dynamic Load Management**: Multi-session support and load balancing module for efficient resource allocation.
6. **Logging and Auditing**: Supports dynamic logging levels with latency monitoring and audit logs to meet compliance requirements.
7. **Data Compression**: Compression module for low-bandwidth environments.
8. **Message Replay and Recovery**: Ensures message integrity with message replay in cases of disconnection or message loss.
9. **Configuration Management**: Configuration file to define risk control, logging, networking parameters, and more.

## Getting Started

### 1. Prerequisites

- C++17 or higher
- [Asio](https://think-async.com/Asio/) - Asynchronous networking library
- [JsonCpp](https://github.com/open-source-parsers/jsoncpp) - JSON parsing library

### 2. Build Instructions

In the project root directory, execute the following commands to build the project:

```bash
mkdir build
cd build
cmake ..
make
```

### 3. Running Examples

After building the project, you can run the examples found in the `examples` folder:

```bash
# Basic usage example
./BasicUsageExample

# Advanced usage example with risk control, load balancing, heartbeat, etc.
./AdvancedUsageExample
```

## Usage Guide

### Configuration File (`config/config.json`)

The `config.json` file defines settings for risk management, logging, network connections, rate limiting, and more:

```json
{
    "risk": {
        "maxOrderAmount": 1000000,
        "maxPosition": 5000000,
        "maxDailyLoss": 50000
    },
    "logging": {
        "level": 2  // 0=INFO, 1=WARNING, 2=ERROR, 3=DEBUG
    },
    "connection": {
        "host": "example.fixserver.com",
        "port": "5000",
        "heartbeatInterval": 30
    },
    "rateLimiter": {
        "maxOrdersPerMinute": 60
    }
}
```

- **risk**: Risk parameters, including order size limits, position limits, and daily loss limit.
- **logging**: Logging settings, defining the output log level.
- **connection**: Network parameters, including server address, port, and heartbeat interval.
- **rateLimiter**: Rate limiting, defining the maximum number of orders allowed per minute.

### Module Descriptions

#### Core Modules

- **FIXParser**: Parses and builds FIX messages, extracting fields and verifying format.
- **FIXSession**: Manages session state, sequencing, and heartbeat, handling message reception and transmission.
- **FIXConnection**: Responsible for asynchronous communication with the server.
- **Logger**: Dynamic logging with support for performance monitoring.
- **ConfigurationLoader**: Loads the `config.json` configuration file and applies settings to modules.

#### Extension Modules

- **RiskControl**: Ensures trades comply with preset risk limits.
- **LoadBalancer**: Load balancing across sessions, dynamically choosing the best connection based on latency.
- **OrderRateLimiter**: Limits order submission rate to avoid exceeding frequency limits.
- **MessageReplay**: Message replay for session disconnection and message loss.
- **AuditLog**: Records all significant events and trade information for auditing purposes.

### Example Code

Below is a basic usage example showing how to use the library to parse messages, establish connections, and perform simple risk control.

#### Example: `examples/BasicUsageExample.cpp`

```cpp
#include "ThunderFix.h"
#include <iostream>

int main() {
    // Initialize configuration and session
    ConfigurationLoader configLoader;
    configLoader.loadConfig("config/config.json");

    FIXSession session(FIXVersion::FIX_4_2, asio::io_context());
    session.start();

    // Parse a message
    FIXParser parser(FIXVersion::FIX_4_2);
    parser.parseMessage("8=FIX.4.2|35=D|55=AAPL|54=1|38=100|");

    // Extract fields
    std::string symbol = parser.getField("55").data();
    int side = std::stoi(parser.getField("54").data());

    Logger::log(LogLevel::INFO, "Parsed Symbol: " + symbol);
    Logger::log(LogLevel::INFO, "Parsed Side: " + std::to_string(side));

    return 0;
}
```

#### Example: `examples/AdvancedUsageExample.cpp`

```cpp
#include "ThunderFix.h"
#include <iostream>

int main() {
    // Load configuration
    ConfigurationLoader configLoader;
    configLoader.loadConfig("config/config.json");

    asio::io_context ioContext;
    FIXSession session(FIXVersion::FIX_4_2, ioContext);
    session.start();

    // Set up risk control
    RiskControl riskControl;
    if (!riskControl.checkOrderLimits(150000)) {
        Logger::log(LogLevel::WARNING, "Order amount exceeds limit.");
    }

    // Rate limiter example
    OrderRateLimiter rateLimiter(60);
    if (rateLimiter.canSendOrder()) {
        Logger::log(LogLevel::INFO, "Order allowed.");
    } else {
        Logger::log(LogLevel::WARNING, "Order rate limit exceeded.");
    }

    ioContext.run();
    return 0;
}
```

## Testing

The `tests` directory contains unit tests for each core and extension module. The tests use the [Google Test (gtest)](https://github.com/google/googletest) framework to ensure reliability.

To run the tests:

```bash
# Run in the build directory
make test
```

### Test Coverage

- **FIXParserTest.cpp**: Tests FIX message parsing and field extraction.
- **FIXSessionTest.cpp**: Tests session management, sequencing, and heartbeat.

## Deployment and Customization

To deploy ThunderFix in a production environment, customize the configuration file (`config.json`) to match specific operational requirements. The configuration file allows for easy tuning of risk limits, logging levels, connection settings, and more.

## Future Enhancements

Potential future extensions to this library include:

1. **Smart Order Routing**: Implement order routing strategies based on market conditions, liquidity, and execution efficiency.
2. **Integration with Trading Algorithms**: Support trading strategies such as VWAP and TWAP, integrated directly within the FIX sessions.
3. **Distributed Architecture**: Enable distributed session management across nodes for scalability in ultra-high-frequency environments.
4. **Enhanced Risk Management**: Dynamic risk controls based on market volatility and significant events.

---

## License

This project is licensed under the Apache-2.0 License. See the [LICENSE](LICENSE) file for details.

---

## Contributing

Contributions are welcome! Please submit issues, fork the repository, and create pull requests. For significant changes, please discuss with the repository maintainers beforehand to ensure alignment with the project goals.
```
