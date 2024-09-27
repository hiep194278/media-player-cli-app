# Media Player CLI Application

This project is a C++ media player application. The following instructions will guide you through cloning the project, building it, and setting it up to run from anywhere on your Ubuntu system.

## Prerequisites

- **Linux Operating System**: I'm using currently using Ubuntu 24.04.1
- **Git**: For cloning the repository.
- **g++**: The GNU C++ compiler.
- **Make**: For building the project.

### Install Prerequisites 

Run the following commands to install Git, g++, and Make if they are not already installed:

```bash
sudo apt update
sudo apt install git g++ make
```

## Setup Instructions

### Step 1: Clone the Repository

First, clone the repository from GitHub using the following command:

```bash
git clone https://github.com/hiep194278/media-player-cli-app.git
```

### Step 2: once the repository is cloned, navigate into the project directory:

```bash
cd media-player-cli-app
```
### Step 3: Build the Project

To compile the source files and build the project, use the make command:

```bash
make
```

### Step 4: Move the Executable to a Directory in Your <span style="background-color:grey">PATH</span>

To run the program from anywhere in your terminal, move the compiled executable to a directory that's in your system's PATH, such as <span style="background-color:grey">/usr/local/bin</span>:

```bash
sudo mv media_player_cli_app /usr/local/bin/
```

You can verify if the directory is in your PATH by running:

```bash
echo $PATH
```

### Step 5: Run the Program from any directories

Now, you can run the program from any location in the terminal by typing:

```bash
media_player_cli_app
```

### Optional: 
**To stop the program from running from anywhere**, remove the executable from <span style="background-color:grey">/usr/local/bin</span>:

```bash
sudo rm /usr/local/bin/media_player_cli_app
```

**To clean the project directory**, you can remove all compiled object files and the build/ directory by running:

```bash
make clean
```