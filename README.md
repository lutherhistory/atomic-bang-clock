# Atomic Bang Clock

> A *clock* program that can use on your machine.

## About

The idea of trying replace Google timer instead of mine.

## Features

- [ ] Basic Feats
	- [ ] ⏰ ***Alarm***
	- [ ] ⏱️ ***Countdown*** timer
	- [ ] 📅 ***Progress Deadline***

- [ ] ***Plugins System***
- [ ] ***Obsidian Integration*** Connect with your `Obsidian` vaults which can to know about your condition

## Screenshots

<div align="center">
  <img width="800" alt="docs/showcase1.png" src="docs/latest.png" />
  <br/>
  <em>Overview</em>
  <br/><br/>
</div>

## Requirments

- **C Compiler** (GCC recommended)
- **GTK4** (GIMP Toolkit)
- **Make** (build system)
- **pkg-config** (dependency management)

### Install Dependencies

**Ubuntu/Debian:**
```Bash
sudo apt install build-essential libgtk-4-dev pkg-config
```

**Fedora:**
```Bash
sudo dnf install gcc gtk4-devel pkg-config
```

**Arch:**
```Bash
sudo pacman -S gcc gtk4 pkg-config
```

## Installation

### Build from Source
```Bash
# Clone this repository
git clone https://github.com/lutherhistory/atomic-bang-clock.git
cd atomic-bang-clock

# Build this project
make

# Run the application
make run
```

## Project
```
atomic-bang-clock/
├── build/					# Build output
│   ├── atomic-clock		# Executable binary
│   └── obj/				# Object files
│       └── main.o
├── docs/					# Documentation & screenshots
│   ├── showcase1.png
│   ├── showcase2.png
│   └── showcase3.png
├── http/					# Web assets (CSS, etc.)
│   └── style.css           # Custom stylesheet
├── inc/					# Header files
├── src/					# Source code
│   └── main.c
├── compile_commands.json	# For LSP support
├── Makefile
└── README.md
```

## Customization

### Styling

You can modify the look and feel by editing http/style.css:

```CSS
/* Example: Change clock color */
label {
    color: #00ff41;  /* Matrix green */
    font-size: 80px;
    /* Add your own styles here! */
}
```
