# LOKEY-Pokey-7800

> ⚠️ **Early-stage hardware/firmware project. Unstable, experimental, and *loud*.**

**LOKEY-Pokey-7800** goal is to be the missing link between our portable POKEY audio core (**liblokey**)—already running
on the
Raspberry Pi Pico—and real Atari 7800 hardware.

- **[liblokey](https://github.com/jbsohn/liblokey)** runs accurate POKEY emulation on the RP2040 (Pico), combining the
  best of Atari800 and OpenEmu ProSystem
  7800 Core codebases.
- **[YMFM](https://github.com/aaronsgiles/ymfm) YM2151** emulation now integrated for future dual-chip audio projects.
- **This project** adapts and deploys those engines *as a real hardware add-on*—a cartridge-ready sound solution for the
  Atari 7800, plus planned tracker support.

**Best of all: the RP2040 costs just a few bucks per cart.**  
*No more hoarding rare chips. Modern sound—affordably—for every new game.*

---

## Architecture Goals

- **liblokey:**  
  Portable, embeddable POKEY/audio library with a clean C/C++ API.  
  Runs and tested on the Pico (RP2040) and desktop.
- **YMFM YM2151:**  
  High-accuracy FM synthesis core now included for YM-based 7800+ projects.
- **This project:**  
  Firmware and hardware “glue” for the 7800.  
  Brings everything together:
    - Emulates POKEY audio (Atari800 and ProSystem 7800 cores)
    - Emulates YM2151 audio via Nuked-OPM
    - Handles 7800 cartridge bus comms
    - Outputs audio via pin 38 (POKEY_OUT)

---

## Features (In Progress)

- **POKEY audio emulation on real hardware** (tested on Pico via liblokey)
- **YM2151 FM synthesis emulation** (via YMFM)
- **MOD/XM tracker support** — *planned but on hold* (via [libxm](https://github.com/Artefact2/libxm))
- **Cartridge-compatible design**
    - 27C256 EPROM + RP2040 on a single board
    - Pin 38 = audio, pin 36 = ground
- **Low cost:**
    - RP2040 is cheap, hobbyist-friendly, and in-production now
- **Desktop/host test apps** (SDL)
- **All code GPLv2**

---

## Status

- **Proven:** liblokey runs on Pico; POKEY audio works!
- **YM2151 integration started** — first host SDL audio output confirmed.
- **libxm integration on hold** until core chip work is finalized.
- This repo: Wiring up for full 7800 support—hardware, firmware, and integration in progress.

---

## AI-Assisted Development

This project wouldn’t exist—at least not as a one-person, evenings-and-weekends effort—without real, practical help from
AI. ChatGPT and related tools have made it possible to tackle firmware, C++ refactors, embedded hardware, and
documentation at a speed that just isn’t realistic solo.

If you’re curious about my broader take on how AI is reshaping software development, check out my blog post:  
👉 [What AI Is Doing to Software Development](https://johnsmusicandtech.com/posts/what-ai-is-doing-to-software-development/)

---

## Credits

- **liblokey:** Portable POKEY core ([liblokey](https://github.com/YOURNAME/liblokey)),  
  based on [Atari800](https://github.com/atari800/atari800)
  and [OpenEmu ProSystem 7800 Core](https://github.com/OpenEmu/ProSystem-Core).
- **Nuked-OPM:** High-accuracy YM2151 emulator ([nukeykt/Nuked-OPM](https://github.com/nukeykt/Nuked-OPM))
- **libxm:** MOD/XM playback ([Artefact2/libxm](https://github.com/Artefact2/libxm)) — planned

---

## License

GPLv2 (see [LICENSE](LICENSE)).
