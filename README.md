# NOTICE
I am no longer working on this tool. It has gotten to the point where so much has changed with Atmosphere as a whole that in order to suport it I would need to rewrite this tool from scratch. Unfortunatly I just don't have the time for that anymore, so for now it will remain as it is.

# Kip Select
![Screenshot](https://github.com/Sciguy429/KipSelect/raw/master/graphics/screenshot/screenshot-1.jpg)
This is a WIP toolkit for the switch cfw Atmopshere, it started out as a simple KIP manager but has become much more over time. This toolkit is intended for use with Atmosphere Fusee, it will still somewhat work other packs like Kosmos but stuff may be broken. Further CFW support is planned for the future.

## Features
* Enabling And Disabling Of KIPS
    * KIPS, or **K**ernel **I**nitial **P**rocesses, are a commonly used homebrew format. This tool allows them to be enabled and disabled. A reboot is required after a KIP is toggled for it to load/unload. This fetaure requires Atmosphere to be launched via Fusee as it dirrectly manipulates the KIPS within /atmosphere/kips/ which are loaded only by the Fusee launcher. If you are useing Kosmos, use Hekate to manage your KIPS instead.
* Configureing BCT.ini
    * BCT.ini is a configuration file for Atmosphere. This tool allows modification of all true/false values in this file. It is worth noting however that in order for nogc toggleing to work you must first manually uncomment this line in BCT.ini. As of Atmosphere 0.8.2 nogc patches should enable themselves automatically if the right combiation of fuses is detected.
* Managing LayeredFS Titles
    * This homebrew can enable or disable layeredFS titles. Due to the way Atmosphere works Enableing or disabling a layeredFS title only requires that title to be restarted to take effect. Unless you are modding a system title, for themes for instance, a reboot should not be needed. This tool will attempt to retrive as much information about a title as it can searching both NSWreleases.xml as well as a local database of system title imformation. The newer Atmosphere 'system modules' will also show up here and are should enable/disable in the same way.
* Trigger A Console Restart
    * You can also trigger a console restart from within this tool. The console can be restarted dirrectly into RCM mode or with a newly added feature in Atmopshere 0.8.3, it can be dirrectly rebooted back into Atmosphere without the need for a payload dongle.

## Installing
This tool is currently available on the switch appstore, however if you would like to you can still download it from GitHub or even build it yourself. The nro has no special requiremnts about where it gets placed, I would still recommend your put it in /switch/ though.

## Building
This homebrew is a standered libnx project, make sure you have devkitPro installed correctly and simply run make from the project root. I personaly write this project useing VsCode and thus there is a CppProperties.json file already configured for proper syntax highlighting in the project root, this configuration should work with almost any other homebrew project although depending on where your devkitPro install is you may need to change some stuff around. VsCode doesn't really like windows environment variables.

## Dependicies
* libxml2: For handling xml data files, like NSWreleases.xml.
* libcurl: For downloading files.
* libfreetype2: For loading and displaying fonts.
* libpng: For loading png texture files.
* libbzip: Required for libpng and freetype2.

## Credits
* A huge thank you to MatinatorX for all of the graphics assets used by this tool. He had a hand in prety much all of there creation and without his work this tool would proboly look considerably worse than it dose now.
* [Libnx - The Framework This Tool Is Built On](https://github.com/switchbrew/libnx)
* [Switchbrew - For System Title Names/Information](https://switchbrew.org/wiki/Main_Page)
* [Atmospshere - For 'Reboot To Payload' Example Code](https://github.com/Atmosphere-NX/Atmosphere)
* [Hactool - For Kip Header Extraction Code](https://github.com/SciresM/hactool)
