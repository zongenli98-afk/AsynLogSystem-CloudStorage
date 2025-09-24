# AsynLogSystem-CloudStorage

## Project Overview
This project implements a file upload service based on the `libevent` network library. It supports file upload, download, and display functionalities and accommodates multiple storage tiers. The system also features an asynchronous logging system with support for backup of critical logs and multi-threaded concurrent log writing.

The `src/client` directory contains an optional Windows client, so you can interact with the server directly via the web frontend.

---

## Environment Setup

### Prerequisites
- Operating System: Ubuntu 22.04 LTS
- Compiler: `g++`
- Shell: `bash`

Install basic tools:

```bash
sudo apt update
sudo apt install g++
```

---

## Logging

1. jsoncpp

Install jsoncpp:

```bash
sudo apt-get install libjsoncpp-dev
```

When compiling with `g++`, link with `-ljsoncpp`. Header files are located at `/usr/include/jsoncpp/json`, and the dynamic library is at `/usr/lib/x86_64-linux-gnu/libjsoncpp.so`.

---

## Storage (Server)

### 1. libevent
Linux installation steps:

```bash
sudo apt-get update
sudo apt-get install build-essential autoconf automake libssl-dev
wget https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz
tar xvf libevent-2.1.12-stable.tar.gz
cd libevent-2.1.12-stable
./configure
make
sudo make install
```

Verification:

```bash
cd sample
./hello-world
```

Open another terminal and run:

```bash
nc 127.1 9995
```

If successful, the terminal will return `Hello, World!`.

### 2. jsoncpp
(Already covered in Logging section.)

### 3. bundle
Source: https://github.com/r-lyeh-archived/bundle

Clone the repository and include `bundle.cpp` and `bundle.h` in your project.

### 4. cpp-base64
```bash
git clone https://github.com/ReneNyffenegger/cpp-base64.git
```

Copy `base64.h` and `base64.cpp` from the cloned repository into the `src/server/` directory of your project.

---

## Web Frontend
Access the service by navigating to `http://<ip>:<port>` in your browser.

---

## Windows Client (Optional)
Implementing the client on Windows can be complex. Required tools:

- libevent: Download 2.1.12-stable from libevent.org.
- Visual Studio 2019
- OpenSSL (source)
- Perl
- nasm

High-level Windows build steps:

1. Open the x64_x86 Cross Tools Command Prompt for VS 2019 as administrator.
2. Build and install OpenSSL:

```bash
perl Configure VC-WIN32 --prefix=D:\software\openssl_output
nmake
nmake install
```

3. Add OpenSSL to system PATH.
4. Build libevent with OpenSSL:

```bash
nmake /f Makefile.nmake OPENSSL_DIR=D:\software\openssl_output
```

Verify installation by running `regress.exe` in the `test/` directory.

In Visual Studio:
- Set platform to x86.
- Add libevent include directory to Project Properties > C/C++ > General > Additional Include Directories.
- Add libevent library directory to Linker > General > Additional Library Directories.
- Add `libevent.lib;ws2_32.lib;` to Linker > Input > Additional Dependencies.

---

## How to Run

### Configure the Server
Edit the `Storage.conf` file located at `Kama-AsynLogSystem-CloudStorage/src/server/`. Replace `server_ip` and `server_port` with your server's IP address and desired port.

Example `Storage.conf` JSON:

```json
{
  "server_port" : 8081,
  "server_ip" : "127.0.0.1"
}
```

If using a cloud server, ensure the port is open in your security group / firewall rules.

### Configure Log Backup (Optional)
Edit the `config.conf` file in `Kama-AsynLogSystem-CloudStorage/log_system/logs_code/`. Set `backup_addr` and `backup_port` to the address and port of your backup log server. If these fields are not configured, backup functionality will be disabled but the logging system will still work normally.

Example `config.conf` JSON:

```json
{
  "backup_addr" : "47.116.22.222",
  "backup_port" : 8080
}
```

### Start the Backup Log Server
Copy `ServerBackupLog.cpp` and `.hpp` from `log_system/backlog/` to another server (or the same machine in a different directory). Compile and run:

```bash
g++ ServerBackupLog.cpp
./a.out <PORT_NUMBER>
```

The port number must match `backup_port` in `config.conf`.

### Run the Main Server
In `Kama-AsynLogSystem-CloudStorage/src/server/`:

```bash
make
./test
```

### Access the Service
Open a browser and go to:

```
http://<your_server_ip>:<your_server_port>
```

Or run the optional Windows client and upload files to trigger uploads.

---

## Notes & Tips
- Use `sudo` to install packages or run commands that need elevated privileges.
- If the server fails to bind to a port, check with `ss`, `netstat`, or `lsof` for processes using the port.
- Keep copies of `base64` and `bundle` source files inside `src/server/` as instructed.

---

## Project Structure (high level)
- `src/server/` — server source, `Storage.conf`, build `Makefile`
- `src/client/` — optional Windows client / web frontend assets
- `log_system/logs_code/` — logging configuration (`config.conf`)
- `log_system/backlog/` — backup log server sources (`ServerBackupLog.cpp`, `.hpp`)

---

If you want, I can:
- Save this generated Markdown into `README.md` in your repo and create a commit.
- Or produce a shorter or translated Chinese version.
