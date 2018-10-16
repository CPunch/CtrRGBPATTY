#eclipse-3ds-template

This template is basically a fork of [TricksterGuy's 3ds-template](https://github.com/TricksterGuy/3ds-template) which is essentially a fork of two other templates, which I'm not going to ramble on about.

##Modifications:
1) Supports eclipse now.
2) Eclipse also has build targets.

##To set up in eclipse:

Open eclipse and import a project into the workspace. Select the root of the folder (or select the ZIP of this repository). You must have devkitPro installed to /opt/devkitPro and thus devkitARM installed to /opt/devkitPro/devkitARM.

Atop this, you also need buildtools.

As a result, all build targets and includes should be added. If you'd like auto-corrections on libraries other than ctrulib.

##To set up for elsewhere (or windows.)

Modify the eclipse environment variables, C includes, and C++ includes to be where your install of devkitPro and CTRUlib is.
