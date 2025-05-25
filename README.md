<!-- markdownlint-disable-file MD001 MD033 -->

<p align="center">
	<a href="https://github.com/xifil/zeroproxy/-/blob/master/LICENSE">
		<img src="https://img.shields.io/github/license/xifil/zeroproxy.svg" title="License" />
	</a>
	<a href="https://github.com/xifil/zeroproxy/-/issues">
		<img src="https://img.shields.io/github/issues/xifil/zeroproxy.svg" title="Open Issues" />
	</a>
	<a href="https://discord.gg/dPzJajt">
		<img src="https://img.shields.io/discord/769966964030046298?color=%237289DA&label=members&logo=discord&logoColor=%23FFFFFF" title="Discord" />
	</a>
</p>

<h1 align="center"><a href="https://github.com/xifil">xifil</a>/<a href="https://github.com/xifil/zeroproxy">zeroproxy</a></h1>

<p align="center">
  <img src="assets/github/banner.png?raw=true" />
</p>

> [!WARNING]
> You **must** legally own the Call of Duty® game you intend to run with this mod. Cracked/Pirated versions of the game are **NOT** supported.

### This repository contains a client mod for each of the following games:

Call of Duty®: Modern Warfare® 2 (2009)
<a href="https://apps.microsoft.com/detail/9P31HFP7L9WT"><img height="15px" src="assets/github/microsoft.svg" /></a><br/>
Call of Duty®: Black Ops II (2012)
<a href="https://apps.microsoft.com/detail/9NFB5MDCWF47"><img height="15px" src="assets/github/microsoft.svg" /></a>
<a href="https://steampowered.com/app/202970"><img height="15px" src="assets/github/steam.svg" />\*</a><br/>
Call of Duty®: Ghosts (2013)
<a href="https://apps.microsoft.com/detail/9PJH49B6K7DD"><img height="15px" src="assets/github/microsoft.svg" /></a><br/>
Call of Duty®: Black Ops III (2015)
<a href="https://apps.microsoft.com/detail/9P5QVB59FXRR"><img height="15px" src="assets/github/microsoft.svg" /></a>
<a href="https://steampowered.com/app/311210"><img height="15px" src="assets/github/steam.svg" />\*\*</a><br/>
Call of Duty®: WWII (2017)\*
<a href="https://apps.microsoft.com/detail/9P3QS4LX8BM9"><img height="15px" src="assets/github/microsoft.svg" /></a><br/>
Call of Duty®: Modern Warfare® (2019)
<a href="https://eu.shop.battle.net/en-us/product/call-of-duty-modern-warfare"><img height="15px" src="assets/github/battle_net.svg" /></a><br/>
Call of Duty®: Black Ops Cold War (2020)
<a href="https://eu.shop.battle.net/en-us/product/call-of-duty-black-ops-cold-war"><img height="15px" src="assets/github/battle_net.svg" /></a>
<a href="https://steampowered.com/app/1985810"><img height="15px" src="assets/github/steam.svg" />\*\*</a><br/>

> \* - currently doesn't function  
> \*\* - doesn't use Steam executable, uses executable of other platform

## Compile from source

- Clone the Git repo. Do NOT download it as ZIP, that won't work.
  > You can run
  >
  > ```
  > git clone https://github.com/xifil/zeroproxy.git --recurse-submodules
  > ```
  >
  > You always need the `--recurse-submodules` flag!
- Update the submodules and run `premake5 vs2022` (if available in path, otherwise use `.\tools\premake\premake5`) or simply use the provided `generate.bat`.
- Build via solution file in `ZeroProxy.sln` in Visual Studio 2022 (JetBrains Rider has not been tested!).

## Download from Actions

GitHub Actions automatically builds the DLL files on each
commit, you can find the latest build of zeroproxy clients
[here](https://xifil.github.io/zp-redirect).

## Installation

Download the correct client mod from the link above, then extract the zip and copy the `.dll` into the root of your game folder, then run the game's executable (make sure its not `<Game> Launcher.exe`, those are Battle.Net Launchers and are unsupported!)

## Credits

- [boiii-free](https://github.com/Ezz-lol/boiii-free) - general codebase
- [momo5502](https://github.com/momo5502) - Arxan/Steam research, former lead developer of [XLabsProject](https://github.com/XLabsProject)

## Disclaimer

This software has been created purely for the purposes of academic research. It is not intended to be used to attack other systems. Project maintainers are not responsible or liable for misuse of the software. Use responsibly.

Additionally this software is licensed under the Boost-Software-License 1.0, please read and respect the license when making forks. Also if you could give attributions back to ZeroProxy that would be pretty cool thanks.
