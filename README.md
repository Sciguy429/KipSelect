# Kip Select
![screenshot](https://github.com/Sciguy429/KipSelect/raw/master/icon/ExampleScreenshot.jpg)
This is a WIP kip manager for atmosphere's fuse launcher, this homebrew will not work with Kosmos, or any other pack that boots from hekate, while it will run it wont do anything as hekate controls what kips load in those packs. This hombrew is intended only for use with 'vanilia' atmosphere, luanched with fuse.

## How To Use
This howmebrew enables and disables kips by moving them between the /atmosphere/kips/ folder and an addded folder called /atmosphere/kips_disabled/. Since fuse only checks the kips folder on boot, anything in kips_disabled gets ignored. The homebrew automaticly creates the required folders (/atmmosphere/kips/ & /atmosphere/kips_disabled/) if they are missing, all you need to do is make sure your kips are in one of the two folders before launching. The .nro has no other special requirements and should be launchable from anywhere (although simply placeing it in /switch/ is recommended).

## Notes
* This homebrew only supports a maximum of 32 kips, attempting to use more will result in a error and possibly even a console hard crash.
* Try and name your kips something resonable, the program should be able to work with any file name the sdcard fs supports but namming your kip with emoji's isn't going to help.
* I have no idea how safe this is to use on exFat, it shouldn't corrupt anything as the only write operation it uses is rename(), but should isn't won't, please be carefull.

## Credits
* [libnx](https://github.com/switchbrew/libnx)
