# Source Interface Dumper

This Project is just for "educational purposes" only.

Use this if you want to find more about source games ( **only singleplayer** )

# How to use?
Build it in `Release` and `x86` mode!
Inject the dll into any Source Game ( **singleplayer only** )
And then you have a console in the console you type your commands

# Commands
## findPossibleDlls
- Well `findPossibleDlls` list's all Modules ( Dll's ) that have interface support

## analyze
- Analyzes the given Module ( Dll ). You first type `analyze` and press enter and then you input the name of the Module ( Dll ) that you want to analyze now it gives you the list of the interfaces with the **offset** to the specified interface's method!

## unload
- Well i think you know what `unload` means

# Example

## 1. findPossibleDlls
```
--- CONSOLE ---
findPossibleDlls

[16:59:21] [Info] Following Modules have interface's!
[16:59:21] [Info] launcher.dll
[16:59:21] [Info] vstdlib.dll
[16:59:21] [Info] filesystem_stdio.dll
[16:59:21] [Info] engine.dll
[16:59:21] [Info] inputsystem.dll
[16:59:21] [Info] vphysics.dll
[16:59:21] [Info] materialsystem.dll
[16:59:21] [Info] datacache.dll
[16:59:21] [Info] studiorender.dll
[16:59:21] [Info] soundemittersystem.dll
[16:59:21] [Info] vscript.dll
[16:59:21] [Info] soundsystem.dll
[16:59:21] [Info] valve_avi.dll
[16:59:21] [Info] vguimatsurface.dll
[16:59:21] [Info] vgui2.dll
[16:59:21] [Info] panoramauiclient.dll
[16:59:21] [Info] video.dll
[16:59:21] [Info] panorama.dll
[16:59:21] [Info] shaderapidx9.dll
[16:59:21] [Info] imemanager.dll
[16:59:21] [Info] localize.dll
[16:59:21] [Info] panorama_text_pango.dll
[16:59:21] [Info] steamclient.dll
[16:59:21] [Info] vstdlib_s.dll
[16:59:21] [Info] crashhandler.dll
[16:59:21] [Info] stdshader_dbg.dll
[16:59:21] [Info] stdshader_dx9.dll
[16:59:21] [Info] matchmaking.dll
[16:59:21] [Info] client.dll
[16:59:21] [Info] server.dll
[16:59:21] [Info] scenefilecache.dll
[16:59:21] [Info] vaudio_miles.dll
[16:59:21] [Info] vaudio_celt.dll
[16:59:21] [Info] serverbrowser.dll
[16:59:21] [Info] --- END ---
[16:59:21] [Info] 34 / 195 modules are source engine modules!
```

## 2. analyze
```
--- CONSOLE ---
analyze

[17:00:19] [Info] Please enter the dll's name.
panorama.dll
[17:00:26] [Info] --- BEGIN ---
[17:00:26] [Info] CI Address : XXXX29B0
[17:00:26] [Info] CI [2] Address : XXXX2940
[17:00:26] [Info] MAP Address : XX2946
[17:00:26] [Info] --- Begin Interfaces ---
[17:00:26] [Info] Name | Construction Address (base+0x00000000)
[17:00:26] [Info] PanoramaUIEngine001 | 0x00011E60
```