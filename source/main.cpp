#include <switch.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

string kips[32];
string bct[2] = {"debugmode = ", "debugmode_user = "};
int bctValues[2] = {-1, -1};
int menuSelected = 0;
int kipsCount = 0;
bool kipsEnabled[32];
bool run = true;
bool bctSelected = false;
u64 kDown;

void updateInputs() {
  hidScanInput();
  kDown = hidKeysDown(CONTROLLER_P1_AUTO);
  if (kDown & KEY_PLUS) run = false;
}

void printError(int errorCode, string extra) {
  printf(CONSOLE_ESC(2J) CONSOLE_RED "An Error Has Occured! (Error Code: %d) Press '+' To Exit Back To HB-Menu\n\n", errorCode);
  switch (errorCode) {
    case 0:
    printf("Unable To Make Dirrectory: %s", extra.c_str());
    break;
    case 1:
    printf("No Kips Found!\nDid You Install Any?");
    break;
    case 2:
    printf("More Than 32 Kips Found!");
    break;
    case 3:
    printf("File Moved Failed!\nOffending Kip: %s\n\n\nThis Is Typicly Caused By A Kip Being Present In kips and kips_disabled\nAt The Same Time, Check These Folders First", extra.c_str());
    break;
    case 4:
    printf("Unabled To Open BCT.ini!");
    break;
    default:
    printf("UKNOWN ERROR\n(You're In DEEP Trouble If This Shows Up Lol :P)");
    break;
  }
  while (run) {
    consoleUpdate(NULL);
    updateInputs();
  }
}

void scanForKips() {
  kipsCount = 0;
  DIR* enabledKipDir;
  struct dirent* enabledKipEnt;
  enabledKipDir = opendir("/atmosphere/kips/");
  if (enabledKipDir == NULL) {
    if (mkdir("/atmosphere/kips/", 0700) == -1) {
      printError(0, "/atmosphere/kips/");
    }
  }
  else {
    while ((enabledKipEnt = readdir(enabledKipDir))) {
      kips[kipsCount] = enabledKipEnt->d_name;
      kipsEnabled[kipsCount] = true;
      kipsCount++;
      if (kipsCount == 32) {
        kipsCount = 0; //Set the kip count back to 0 to prevent a crash screen from showing
        printError(2, "");
        break;
      }
    }
  }
  DIR* disabledKipDir;
  struct dirent* disabledKipEnt;
  disabledKipDir = opendir("/atmosphere/kips_disabled/");
  if (disabledKipDir == NULL) {
    if (mkdir("/atmosphere/kips_disabled/", 0700) == -1) {
      printError(0, "/atmosphere/kips_disabled/");
    }
  }
  else {
    while ((disabledKipEnt = readdir(disabledKipDir))) {
      kips[kipsCount] = disabledKipEnt->d_name;
      kipsEnabled[kipsCount] = false;
      kipsCount++;
      if (kipsCount == 32) {
        kipsCount = 0; //Set the kip count back to 0 to prevent a crash screen from showing
        printError(2, "");
        break;
      }
    }
  }
  if (kipsCount == 0) {
    printError(1, "");
  }
}

void readBCT() {
  ifstream bctIfStream("/BCT.ini");
  string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
  bctIfStream.close();
  unsigned int debugModeLocation = bctString.find("debugmode = ", 0) + 12;
  unsigned int debugModeUserLocation = bctString.find("debugmode_user = ", 0) + 17;
  bctValues[0] = bctString[debugModeLocation] - 48;
  bctValues[1] = bctString[debugModeUserLocation] - 48;
}

void setKip(int kipId, bool enabled) {
  string name = kips[kipId];
  string start = "/atmosphere/";
  string end = "/atmosphere/";
  if (enabled) {
    start.append("kips_disabled/");
    end.append("kips/");
  }
  else {
    start.append("kips/");
    end.append("kips_disabled/");
  }
  start.append(name);
  end.append(name);
  if (rename(start.c_str(), end.c_str()) != 0) {
    printError(3, name);
  }
}

void setBCT(int bcdId, bool enabled) {
  unsigned int loctaion = 0;
  ifstream bctIfStream("/BCT.ini");
  string bctString((std::istreambuf_iterator<char>(bctIfStream)), (std::istreambuf_iterator<char>()));
  bctIfStream.close();
  switch (bcdId) {
    case 0:
    loctaion = bctString.find("debugmode = ", 0) + 12;
    break;
    case 1:
    loctaion = bctString.find("debugmode_user = ", 0) + 17;
    break;
    default:
    break;
  }
  if (loctaion != 0) {
    bctString[loctaion] = 48 + enabled;
    ofstream bctOfStream("/BCT.ini");
    if (bctOfStream.is_open()) {
      bctOfStream << bctString;
      bctOfStream.close();
    }
    else {
      printError(4, "");
    }
  }
}

string getBctFormating(int d) {
  if (d == 1) {
    printf(CONSOLE_GREEN);
    return "1";
  }
  if (d == 0) {
    printf(CONSOLE_RED);
    return "0";
  }
  else {
    printf(CONSOLE_YELLOW);
    return "?";
  }
}

void updateScreen() {
  printf(CONSOLE_ESC(2J));
  printf(CONSOLE_MAGENTA CONSOLE_ESC(4m) "Kip Select V%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO);
  printf(CONSOLE_RESET " (+ To Exit Back To HB-Menu, - To Refresh)");
  printf(CONSOLE_ESC(45;68H) CONSOLE_MAGENTA "-By Sciguy429");
  printf(CONSOLE_ESC(4;1H) CONSOLE_RESET CONSOLE_ESC(4m) "Installed Kips:");
  printf(CONSOLE_ESC(4;59H) "BCT.ini:\n");
  printf(CONSOLE_RESET);
  for (int i = 0; i < kipsCount; i++) {
    if (kipsEnabled[i]) {
      printf(CONSOLE_GREEN);
    }
    else {
      printf(CONSOLE_RED);
    }
    if (menuSelected == i && !bctSelected) {
      printf(CONSOLE_ESC(7m));
    }
    printf(" * %s\n", kips[i].c_str());
    printf(CONSOLE_RESET);
  }
  printf(CONSOLE_ESC(5;1H));
  for (int i = 0; i < 2; i++) {
    printf(CONSOLE_ESC(58C));
    string bctStatus;
    switch (bctValues[i]) {
      case 0:
      bctStatus = "0";
      printf(CONSOLE_RED);
      break;
      case 1:
      bctStatus = "1";
      printf(CONSOLE_GREEN);
      break;
      default:
      bctStatus = "?";
      printf(CONSOLE_YELLOW);
      break;
    }
    if (menuSelected == i && bctSelected) {
      printf(CONSOLE_ESC(7m));
    }
    printf(" * %s%s\n", bct[i].c_str(), bctStatus.c_str());
    printf(CONSOLE_RESET);
  }
}

int main(int argc, char **argv)
{
  consoleInit(NULL);
  scanForKips();
  readBCT();
  updateScreen();
  while(appletMainLoop() && run)
  {
    updateInputs();
    if (kDown & KEY_MINUS) {
      menuSelected = 0;
      scanForKips();
      readBCT();
      updateScreen();
    }
    else if (kDown & KEY_LEFT) {
      if (bctSelected == true) {
        bctSelected = false;
        menuSelected = 0;
        updateScreen();
      }
    }
    else if (kDown & KEY_RIGHT) {
      if (bctSelected == false) {
        bctSelected = true;
        menuSelected = 0;
        updateScreen();
      }
    }
    else if (kDown & KEY_DDOWN) {
      menuSelected++;
      if (menuSelected >= (kipsCount * !bctSelected) + (2 * bctSelected)) {
        menuSelected = (kipsCount * !bctSelected) + (2 * bctSelected) - 1;
      }
      else {
        updateScreen();
      }
    }
    else if (kDown & KEY_DUP) {
      menuSelected--;
      if (menuSelected <= -1) {
        menuSelected = 0;
      }
      else {
        updateScreen();
      }
    }
    else if (kDown & KEY_A) {
      if (bctSelected) {
        if (bctValues[menuSelected] == 0) {
          bctValues[menuSelected] = 1;
          setBCT(menuSelected, true);
          updateScreen();
        }
        else if (bctValues[menuSelected] == 1) {
          bctValues[menuSelected] = 0;
          setBCT(menuSelected, false);
          updateScreen();
        }
      }
      else {
        kipsEnabled[menuSelected] = !kipsEnabled[menuSelected];
        setKip(menuSelected, kipsEnabled[menuSelected]);
        updateScreen();
      }
    }
    consoleUpdate(NULL);
  }
  consoleExit(NULL);
  return 0;
}
