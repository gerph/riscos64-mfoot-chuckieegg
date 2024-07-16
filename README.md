# Chuckie Egg

Chuckie Egg is an old BBC game, which has been converted to run on RISC OS
by Michael Foot. His [webpage](https://mjfoot.netlify.app/riscos.htm) includes the downloads of the game.

This version of the game is a modification of one of the earlier versions
which I had lying around, to add support for rendering the game using sprite
operations. This means that the game can run on more modern machines that
don't have low resolution modes. However, the primary reason for making the
change was so that it can run on RISC OS Pyromaniac, which has no frame
buffer.

# Download

You can download the binaries from the Releases on GitHub.

# Compatibility

The game has been tested on RISC OS Pyromaniac, and appears to work ok,
although it is a little slow and some of the colours aren't quite right -
this is most likely a bug in RISC OS Pyromaniac.

It should run on RISC OS 3.5 to 7.

A separate binary is supplied for RISC OS 64.
