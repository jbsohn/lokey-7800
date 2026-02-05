⚠️ **Project Archived**

Archived for now while other approaches are explored. This may come back — stay tuned.

# LOKEY-7800: Modern Audio for Atari 7800, Powered by RP2040

> ⚠️ **Early-stage hardware/firmware project. Unstable, experimental, and *loud*.**

**LOKEY-7800** brings modern, enhanced audio to the classic Atari 7800—using a cheap, hobbyist-friendly Raspberry Pi Pico (RP2040) in every cartridge. No more rare, expensive POKEY chips—LOKEY-7800 emulates POKEY (and more) with open-source firmware and hardware, so *every* new game can have great sound.

- **Why does this exist?**  
  The 7800’s TIA audio is legendary… for being bad. Cartridges like *Ballblazer* added POKEY for real music, but those chips are now unicorns. LOKEY-7800 replaces them with a $5 microcontroller—making enhanced audio affordable for everyone.

---

## Our Philosophy

Let’s be honest: If new POKEY and YM2151 chips were still in production at reasonable prices, we’d just use those.  
But they’re not—and the only way to bring classic sound to modern 7800 carts is to experiment, iterate, and see what’s possible with today’s tech.

**Will it work?**  
We honestly don’t know! That’s the fun. Half the joy is figuring it out as we go, solving problems in public, and maybe even failing a few times along the way. If we get there and it all comes together, awesome. If not, at least we’ll know *why*—and share what we learn.

---

## Architecture Goals

- **liblokey:**  
  Portable, embeddable POKEY/audio library with a clean C/C++ API.  
  Runs and tested on the Pico (RP2040) and desktop.
- **YMFM YM2151:**  
  High-accuracy FM synthesis core—*very early stages*: currently generating a single tone on Pico; full YM2151 audio not yet implemented.
- **This project:**  
  Firmware and hardware “glue” for the 7800.  
  Brings everything together:
    - Emulates POKEY audio (Atari800 and ProSystem 7800 cores)
    - Early YM2151 (YMFM) audio experiments
    - Handles 7800 cartridge bus comms
    - Outputs audio via pin 38 (POKEY_OUT)

---

## Features (In Progress)

- **POKEY audio emulation on real hardware** (tested on Pico via liblokey)
- **YM2151 FM synthesis emulation** (*very early: currently generates a simple tone on Pico; full YM2151 support TBD*)
- **Pico-to-pico communication** for simulated 7800-to-cartridge testing (proven functional)
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
- **Pico-to-pico communication working:** Simulates Atari 7800-to-cartridge communication for full-speed bus testing and development.
- **YM2151 (YMFM) is in the earliest proof-of-concept stage:** currently generates a simple tone on Pico hardware. Full YM support and integration are planned, but POKEY is our main concentration point.
- **libxm integration on hold** until core chip work is finalized.
- This repo: Wiring up for full 7800 support—hardware, firmware, and integration in progress.

---

## AI-Assisted Development

This project wouldn’t exist—at least not as a one-person, evenings-and-weekends effort—without real, practical help from AI. ChatGPT and related tools have made it possible to tackle firmware, C++ refactors, embedded hardware, and documentation at a speed that just isn’t realistic solo.

If you’re curious about my broader take on how AI is reshaping software development, check out my blog post:  
👉 [What AI Is Doing to Software Development](https://johnsmusicandtech.com/posts/what-ai-is-doing-to-software-development/)

---

## Credits

- **liblokey:** Portable POKEY core ([liblokey](https://github.com/jbsohn/liblokey)),  
  based on [Atari800](https://github.com/atari800/atari800)
  and [OpenEmu ProSystem 7800 Core](https://github.com/OpenEmu/ProSystem-Core).
- **YMFM:** High-accuracy YM2151 emulator ([aaronsgiles/ymfm](https://github.com/aaronsgiles/ymfm))
- **libxm:** MOD/XM playback ([Artefact2/libxm](https://github.com/Artefact2/libxm)) — planned

---

## License

GPLv2 (see [LICENSE](LICENSE))
