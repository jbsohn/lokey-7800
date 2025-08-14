# YM2151 Host Test

This is a **standalone** C++ project for testing [YMFM](https://github.com/aaronsgiles/ymfm)  
and YM2151 (a.k.a. OPM) sound chip emulation **on the host** (Linux, macOS, Windows).

It exists **outside** of the main `lokey-pokey-7800` project.  
This keeps it focused purely on verifying YM2151 behavior and audio output in a desktop environment.

---

## Why This Exists

The YM2151 is a complex FM synthesis chip used in many arcade and console systems.  
Before integrating it into embedded or game projects, we want to:

- Verify correct emulation using YMFM on a full desktop system.
- Compare host output with Pico output.
- Experiment with register programming and patch creation.
- Check real-time audio output and performance characteristics.
- Debug without the constraints of embedded hardware.
