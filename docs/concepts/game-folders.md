What is a game folder?
----------------------

TODO

Why game folders?
-----------------

A game is more than just
the raw data originally encased in a game's ROM chip.
If a game allows you to save your progress,
that information needs to be stored somewhere.
If you use an emulator's [save states](#save-states),
those save states need to be stored somewhere.
If you use Game Genie or Pro Action Replay codes,
information about what codes exist,
what codes are enabled,
and what they do
needs to be stored somewhere.

On the technical side,
a physical game cartridge contains a circuit board
that makes the game data available to the console,
and different games used circuit boards that work differently.
That circuit-layout information needs to be stored somewhere.
Some games included custom processors
to do calculations the base console could not do quickly enough
(like the SuperFX chip used in _StarFox_ for the Super Famicom)
and information about extra chips needs to be stored somewhere.
Some of those custom processors require extra data to work
that's not part of the main game data
(like the DSP chip used in Super Mario Kart for the Super Famicom)
and that data needs to be stored somewhere too.

higan keeps all this game-related information together
in a single place:
a game folder in the higan library.

For a more detailed motivation for game folders,
see [Game Paks on the higan website][gp]

[gp]: https://byuu.org/emulation/higan/game-paks

What is a manifest?
-------------------

TODO

The most important file in a game folder is `manifest.bml`,
which describes how all the other files should be wired together
to create a runnable game cartridge.
However,
the manifest format has occasionally changed
as new emulation details were uncovered
that could not be represented in the old format.
Therefore,
icarus [defaults](#the-icarus-settings-dialog)
to not writing out manifests when it imports games,
and higan [defaults](#the-configuration-dialog)
to ignoring manifests that are present.
Instead,
when higan loads a game,
it will ask icarus to generate a temporary manifest in the latest format,
based on the files present in the game folder
and how they are likely to go together.
You can view this temporary manifest
in [the Manifest Viewer](#the-manifest-viewer).

What's in a game folder?
------------------------

As mentioned [above](#why-game-folders),
a game folder collects all the information relevant
to emulating a particular game.
Not all of the following files
are relevant to every emulated console,
or to every game on a given console,
but they may be relevantunder particular circumstances.

All the files directly in the game folder
are expected to be useful
to all emulators that support them:

  - `manifest.bml`:
    The [manifest](#what-is-a-manifest)
    for this game folder.
  - `program.rom`:
    For most consoles,
    this contains
    the executable instructions and graphics data
    from the cartridge's ROM chips.
    For the Famicom,
    this contains only the executable instructions.
  - `character.rom`:
    For the Famicom,
    this contains only the graphics data
    from the cartridge's ROM chips.
  - `ines.rom`:
    While other consoles typically include enough hints
    in `program.rom` for icarus to generate a manifest,
    the Famicom does not.
    Famicom games not stored in game folders
    typically include an "iNES header" to store that information,
    which icarus preserves after import as `ines.rom`.
  - `save.ram`:
    Games that include a save feature
    will create this file.
    Note that it is only written to disk
    when higan exits gracefully,
    if higan crashes or is forced to quit,
    in-game saves may be lost.
    Other emulators sometimes call this an "SRAM file",
    even though the same filename is used
    for cartridges that use EEPROM or Flash storage,
    not just battery-backed Static RAM.
  - `rtc.ram`:
    Games that include a calendar or real-time clock
    will create this file.
  - `*.data.rom`, `*.program.rom`:
    Files named like this are usually
    [co-processor firmware](#importing-and-playing-games-with-co-processor-firmware).
  - `msu1.rom`:
    Holds streamable data for
    [the MSU-1](#importing-and-playing-MSU-1-games).
  - `track-*.pcm`:
    Holds streamable audio for
    [the MSU-1](#importing-and-playing-MSU-1-games).

Files that are only useful to higan specifically
are placed in a `higan` subdirectory:

  - `cheats.bml`:
    All information present in
    [the Cheat Editor](#the-cheat-editor)
    is stored here.
  - `states/quick/slot-*.bst`:
    All the save states made to
    [Quick state slots](#quick-states).
  - `states/managed/slot-*.bst`:
    All the save states made with
    [the State Manager](#the-state-manager).