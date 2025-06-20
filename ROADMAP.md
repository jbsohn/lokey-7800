# 🎯 LOKEY Project Roadmap

> _"Sound from the future, in 1984."_

## ✅ Phase 1: Proof of Concept (In Progress)
- [x] **SDL-based native test harness** for rapid Pokey sound iteration
- [x] Implement `demo_scale_frame(int ms_elapsed)` to confirm tone sequencing
- [x] Create simple waveform and scale tests (C major scale, sound test mimics)
- [x] Hook up `pokey.c` to actual audible output
- [x] Push live source to GitHub with `README.md` and project status info
- [x] Confirm no changes are required to `pokey.c` from Atari800
- [x] Begin roadmap tracking

## 🔜 Phase 2: Direct RP2040 Output
- [ ] Port current SDL test to run on bare RP2040
- [ ] Output Pokey audio to powered speaker via GPIO DAC or PWM
- [ ] Compare against SDL output for timing/sound accuracy
- [ ] Document supported features and timing considerations

## 🔮 Phase 3: 7800 Cartridge Integration
- [ ] Design flexible cartridge PCB with socketed RP2040 and EPROM support
- [ ] Provide working Gerbers for dev and production
- [ ] Route audio output to 7800 cartridge pin 38 (POKEY_OUT)
- [ ] Add optional RC filter and test speaker header

## 📣 Phase 4: Community Collaboration (Later)
- [ ] Open source full board schematics
- [ ] Add simple tutorial for building and flashing RP2040
- [ ] Create “LOKEY Labs” demo ROM with music/sfx
- [ ] Reach out to Atari 7800 homebrew devs for feedback and collab