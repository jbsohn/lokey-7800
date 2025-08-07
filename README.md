# LOKEY-Pokey-7800

> ⚠️ **Early-stage hardware/firmware project. Unstable, experimental, and *loud*.**  
> You found this before it’s even “alpha”—welcome, intrepid hacker.

**LOKEY-Pokey-7800** is the missing link between our portable POKEY audio core (**liblokey**)—already running on the Raspberry Pi Pico—and real Atari 7800 hardware.

- **liblokey** runs accurate POKEY emulation on the RP2040 (Pico), combining the best of Atari800 and OpenEmu ProSystem 7800 Core codebases.
- **This project** adapts and deploys that engine *as a real hardware add-on*—a cartridge-ready sound solution for the Atari 7800, plus future support for tracker formats like MOD/XM.

**Best of all: the RP2040 costs just a few bucks per cart.**  
*No more hoarding rare chips. Modern sound—affordably—for every new game.*

---

## Architecture

- **liblokey:**  
  Portable, embeddable POKEY/audio library with a clean C/C++ API.  
  Runs and tested on the Pico (RP2040), desktop, and web.  
  Core audio engine here: [liblokey](https://github.com/YOURNAME/liblokey)
- **This project:**  
  Firmware and hardware “glue” for the 7800.  
  Brings everything together:
    - Emulates POKEY audio (using code from Atari800 and OpenEmu ProSystem 7800 Core)
    - Handles 7800 cartridge bus comms
    - Outputs audio via pin 38 (POKEY_OUT)
    - Plans for MOD/XM tracker support (via [libxm](https://github.com/Artefact2/libxm))
    - Host/desktop SDL test harness for rapid dev

---

## Features (In Progress)

- **POKEY audio emulation on real hardware** (tested on Pico via liblokey)
- **MOD/XM tracker support** (coming soon)
- **Cartridge-compatible design**
    - 27C256 EPROM + RP2040 on a single board
    - Pin 38 = audio, pin 36 = ground
    - Dev and release on the same hardware!
- **Low cost:**
    - RP2040 is cheap, hobbyist-friendly, and in-production now
    - Goodbye, expensive/hard-to-find POKEY chips!
- **Desktop/host test apps** (SDL)
- **All code GPLv2**

---

## Why?

- POKEY chips are rare—homebrew shouldn’t depend on 1980s silicon supply chains.
- Let 7800 homebrew have *real* music and new effects.
- Fast dev iteration: same board for testing and production.
- **Affordable:** New “sound chip” for every cart, just a few bucks each.
- Futureproof: tracker formats, more advanced engines, whatever you invent next.

---

## Status

- **Proven:** liblokey runs on Pico; POKEY audio works!
- **This repo:** Now wiring it up for full 7800 support—hardware, firmware, and integration in progress.
- Old files are being cleared; new structure rolling out.
- Expect noise, hacks, and hot glue (metaphorically and maybe literally).
- 7800 homebrew nerds, join us!

---

## AI-Assisted Development

This project wouldn’t exist—at least not as a one-person, evenings-and-weekends effort—without real, practical help from AI. ChatGPT and related tools have made it possible to tackle firmware, C++ refactors, embedded hardware, and documentation at a speed that just isn’t realistic solo.

If you’re curious about my broader take on how AI is reshaping software development, check out my blog post:  
👉 [What AI Is Doing to Software Development](https://johnsmusicandtech.com/posts/what-ai-is-doing-to-software-development/)

---

## Credits

- **liblokey:** Portable POKEY core ([liblokey](https://github.com/YOURNAME/liblokey)),  
  based on [Atari800](https://github.com/atari800/atari800) and [OpenEmu ProSystem 7800 Core](https://github.com/OpenEmu/ProSystem-Core).
- **libxm:** MOD/XM playback ([Artefact2/libxm](https://github.com/Artefact2/libxm))

---

## License

GPLv2 (see [LICENSE](LICENSE)).

---

🏗️ This project is a moving target. Pull requests and snark welcome.
