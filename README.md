# Roubamonte - C++20 Card Game Framework

A modern C++20 implementation of the Brazilian card game "Roubamonte" demonstrating advanced object-oriented design patterns, comprehensive testing, and extensible game engine architecture.

## Overview

This project showcases **enterprise-level C++ development** through a reusable card game framework designed for extensibility. The architecture enables rapid development of diverse card-based games through inheritance and composition patterns.

## Architecture

**Core Design Principles:**
- **Modern C++20** with RAII, exception safety, and STL integration
- **Extensible architecture** using inheritance and polymorphism
- **Comprehensive testing** with Boost Test framework

**8 Core Classes:**
- **`card`** - Immutable card entity with rank/suit properties
- **`stack`** - LIFO container using STL stack
- **`deck`** - Auto-shuffled card collection with Fisher-Yates algorithm
- **`selection_container`** - Abstract base for selectable card containers
- **`hand`** - Player's cards with selection and discard capabilities
- **`tray`** - Central shared card pool
- **`player`** - Game participant with hand management and stealing logic
- **`table`** - Game state coordinator

## Technical Features

- **Modern C++20** - STL containers, RAII patterns, exception safety
- **Professional Testing** - 57+ test cases with Boost Test framework  
- **Intelligent Build System** - Advanced Makefile with 24+ targets
- **Clean Architecture** - Abstract base classes with proven inheritance patterns

## Testing

**Comprehensive test suite with 57+ test cases:**

- **QA Tests** (`qa_*`) - Professional validation using Boost Test framework
- **Interactive Tests** (`show_*`) - Visual demonstrations with user interaction
- **100% Coverage** - All 8 core classes fully tested

**Test Structure:**
```
test_suite/
├── interactive/           # Visual demos (show_*.cpp) with user interaction
├── automated/
│   ├── qa/                # Professional QA tests (qa_*.cpp) using Boost Test
│   └── tdd/               # Specification tests (tdd_*.cpp) for new features
├── build/                 # Compilation artifacts  
└── bin/                   # Test executables
```

## 🔧 Prerequisites & Dependencies

### System Requirements
- **C++20 Compatible Compiler** (GCC 10+, Clang 10+, MSVC 2019+)
- **GNU Make** or equivalent build system
- **Boost Test Library** for QA testing framework

### Dependency Installation

#### **Linux Distributions**

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential g++ make libboost-test-dev
```

**Fedora/RHEL/CentOS:**
```bash
sudo dnf install gcc-c++ make boost-devel
# Or for older versions:
sudo yum install gcc-c++ make boost-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel gcc make boost
```

**openSUSE:**
```bash
sudo zypper install gcc-c++ make boost-devel
```

**Alpine Linux:**
```bash
sudo apk add build-base g++ make boost-dev
```

#### **macOS**

**Using Homebrew (Recommended):**
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install gcc make boost
```

**Using MacPorts:**
```bash
sudo port install gcc10 +universal boost +universal
```

#### **Windows**

**Using MSYS2 (Recommended for Windows):**
```bash
# Install MSYS2 first from https://www.msys2.org/
# Then in MSYS2 terminal:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-boost

# Add the bin directory (e.g., C:\mingw-w64\bin) to your system PATH
# Add the bin directory (e.g., C:\msys64\usr\bin) to your system PATH
```

**⚠️ PATH Configuration Required:**
1. Add MSYS2 to Windows PATH:
   - Open "Environment Variables" (Windows + R → `sysdm.cpl` → Advanced → Environment Variables)
   - In "System variables", select "Path" → Edit → New
   - Add: `C:\msys64\mingw64\bin`
   - Add: `C:\msys64\usr\bin`
2. Restart Command Prompt/PowerShell
3. Test: `g++ --version` should work in regular Windows terminal

**Using Visual Studio:**
```bash
# Install Visual Studio 2019+ with C++ workload
# Install vcpkg package manager
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install boost-test:x64-windows
```

**⚠️ PATH Configuration Required:**
1. Add vcpkg and VS tools to PATH:
   - Add: `C:\path\to\vcpkg` (your vcpkg location)
   - Add: `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\[version]\bin\Hostx64\x64`
2. Use "Developer Command Prompt for VS" instead of regular terminal
3. Or set up environment: `call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"`

**Using Chocolatey:**
```powershell
# Install Chocolatey first, then:
choco install mingw make
# Boost installation varies, recommend MSYS2 approach
```

**⚠️ PATH Configuration Required:**
1. Chocolatey usually handles PATH automatically, but verify:
   - MinGW location: `C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\bin`
   - Make location: `C:\ProgramData\chocolatey\bin`
2. If commands not found, manually add these paths to Windows PATH
3. Restart terminal and test: `g++ --version` and `make --version`

**🔧 Windows Troubleshooting:**
- **"command not found" errors**: Always restart terminal after PATH changes
- **Permission denied**: Run terminal as Administrator for PATH modifications
- **Multiple compiler conflicts**: Use `where g++` to check which compiler is being used
- **MSYS2 vs MinGW paths**: Ensure you're using the correct mingw64 paths, not the msys2 paths
- **Spaces in paths**: Use quotes around paths with spaces when adding to PATH

#### **Embedded Platforms**

**Raspberry Pi (Raspberry Pi OS):**
```bash
sudo apt update
sudo apt install build-essential g++ make libboost-test-dev
# For older Pi models, compilation may be slower but fully supported
```

**Cross-compilation setup (if targeting embedded ARM):**
```bash
sudo apt install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
# Modify Makefile CC variable for cross-compilation
```

#### **Container/Docker Setup**

**Ubuntu-based container:**
```dockerfile
FROM ubuntu:22.04
RUN apt update && apt install -y build-essential g++ make libboost-test-dev
WORKDIR /roubamonte
COPY . .
RUN make -C test_suite all
```

### Verification Commands

**Verify installation:**
```bash
# Check C++20 support
g++ --version
g++ -std=c++20 -E -x c++ - </dev/null >/dev/null && echo "C++20 supported" || echo "C++20 not supported"

# Check Make
make --version

# Check Boost Test (compile simple test)
echo '#include <boost/test/included/unit_test.hpp>' | g++ -x c++ -c - && echo "Boost Test available" || echo "Boost Test missing"
```

**Minimum version requirements:**
- **GCC**: 10.0+ (for full C++20 support)
- **Clang**: 10.0+ (for full C++20 support)  
- **MSVC**: 2019+ (Visual Studio 16.0+)
- **Boost**: 1.70+ (for modern test framework features)

## 🛠️ Build System

### Technical Requirements Summary
- **Compiler**: G++ with C++20 support
- **Build Tool**: GNU Make
- **Testing Framework**: Boost Test library for QA tests
- **Standards**: C++20, Wall, Pedantic flags enabled

### Smart Build Architecture
The build system features intelligent target management with separate compilation and execution phases:

**Essential Commands:**
```bash
cd test_suite

# Main targets
make test          # Build and run all tests
make interactive   # Run visual demonstrations  
make qa            # Run QA validation tests
make clean         # Remove build artifacts
make help          # Show all available targets

# Individual tests available: show_*, qa_* for each component
```

**Advanced Features:**
- Dynamic test discovery and intelligent target management
- Professional help system with automatic categorization

---

*A modern C++20 framework demonstrating extensible architecture, comprehensive testing, and professional development practices.*