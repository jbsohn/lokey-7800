# LOKEY

> ⚠️ **This is a proof-of-concept project in early development.**  
> It is unannounced, experimental, and functionality is incomplete. If you found this, congrats—you’re early. 😊

LOKEY is an open-source hardware and software project that brings modern homebrew sound capabilities to the Atari 7800 via a Raspberry Pi RP2040 microcontroller. It aims to emulate and extend classic audio chips like the POKEY and enable rich audio playback through formats such as `.mod` and `.xm`.

## Features (In Progress)

- POKEY audio emulation using code from the [Atari800 project](https://github.com/atari800/atari800)
- Support for `.mod` and `.xm` music via [libxm](https://github.com/Artefact2/libxm)
- Audio output via cartridge pin 38 (POKEY_OUT) and ground pin 36
- Designed to work with a 27C256 EPROM and RP2040 microcontroller
- Development and production use on the same board
- SDL-based test harness for desktop audio testing
- GPLv2 licensed (see LICENSE file)

## Credits

- Based on audio code from [Atari800](https://github.com/atari800/atari800)
- Tracker playback via [libxm](https://github.com/Artefact2/libxm)
- Built with ❤️ and sarcasm by the dynamic duo: John Sohn & ChatGPT
- “Free as in freedom, not as in cartridges.”
- “Sound from the future, in 1984.”

## License

Licensed under the GNU General Public License v2. See [LICENSE](LICENSE) for details.

---

🏗️ Expect breakage. Expect weird noises. Expect fun.  
This is a working prototype—a proof of concept—designed to evolve.