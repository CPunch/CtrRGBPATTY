#include <stdio.h>  // Basic functions
#include <stdlib.h> // malloc and free
#include <string.h> // String manipulation
#include <dirent.h> // For opendir() and readdir()
#include <unistd.h> // rmdir()
#include <fstream>
#include <sstream>
#include <3ds.h>    // Main 3ds lib (libctru)
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

typedef struct {
    uint8_t r[32];
    uint8_t g[32];
    uint8_t b[32];
} LED;

std::string menu[6]={
    "Set Notification RGB Hex Color",
    "Change pattern for LED",
    "Trigger Static ending",
    "Trigger Loop ending",
    "Install IPS Patch",
    "Shutdown 3DS"
};

int selected, CMDS = 6;

std::string paterns[4]={
    "Blink  ",
    "Explode",
    "Rainbow",
    "Static "
};

int selectedpat, PATS = 4;

// defaults
char color_HEX[] = "910b0b";

bool staticend = false;
uint8_t LOOPBYTE = 0xFF; // no loop

/* Documentation:
    LED struct has RGB patterns for 32 itterations. With this you can make an animation with the LED. (like the one MCU BRICKER does).
*/

void createLED(LED* patern, std::string hexCode, bool staticEND, int selcpat)
{
    // LED datastruct we will be returning
    int r, g, b;

    // Remove the hashtag ...
    if(hexCode.at(0) == '#') 
    {
        hexCode = hexCode.erase(0, 1);
    }

    // ... and extract the rgb values.
    std::istringstream(hexCode.substr(0,2)) >> std::hex >> r;
    std::istringstream(hexCode.substr(2,2)) >> std::hex >> g;
    std::istringstream(hexCode.substr(4,2)) >> std::hex >> b;

    printf("(%d, %d, %d)\n", r, g ,b);
    printf("writing to RGB struct...\n");

    memset(&patern->r[0], 0, 32); 
    memset(&patern->g[0], 0, 32); 
    memset(&patern->b[0], 0, 32); 

    switch(selcpat)
    {
        case 0: // Blink
            for (int i = 1; i<31; i+=10)
            {
                memset(&patern->r[i], r, 5); 
                memset(&patern->g[i], g, 5); 
                memset(&patern->b[i], b, 5);
            }
        break;
        case 1: // Explode
            for (int i = 1; i<=31; i+=10)
            {
                patern->r[i] = (r/32)+1 * (31-i);
                patern->g[i] = (g/32)+1 * (31-i);
                patern->b[i] = (b/32)+1 * (31-i);
            }
        break;
        case 2: // Rainbow (AKA MCU bricker lol)
            patern->r[0] = 128;
            patern->r[1] = 103;
            patern->r[2] = 79;
            patern->r[3] = 57;
            patern->r[4] = 38;
            patern->r[5] = 22;
            patern->r[6] = 11;
            patern->r[7] = 3;
            patern->r[8] = 1;
            patern->r[9] = 3;
            patern->r[10] = 11;
            patern->r[11] = 22;
            patern->r[12] = 38;
            patern->r[13] = 57;
            patern->r[14] = 79;
            patern->r[15] = 103;
            patern->r[16] = 128;
            patern->r[17] = 153;
            patern->r[18] = 177;
            patern->r[19] = 199;
            patern->r[20] = 218;
            patern->r[21] = 234;
            patern->r[22] = 245;
            patern->r[23] = 253;
            patern->r[24] = 255;
            patern->r[25] = 253;
            patern->r[26] = 245;
            patern->r[27] = 234;
            patern->r[28] = 218;
            patern->r[29] = 199;
            patern->r[30] = 177;
            patern->r[31] = 153;
            patern->g[0] = 238;
            patern->g[1] = 248;
            patern->g[2] = 254;
            patern->g[3] = 255;
            patern->g[4] = 251;
            patern->g[5] = 242;
            patern->g[6] = 229;
            patern->g[7] = 212;
            patern->g[8] = 192;
            patern->g[9] = 169;
            patern->g[10] = 145;
            patern->g[11] = 120;
            patern->g[12] = 95;
            patern->g[13] = 72;
            patern->g[14] = 51;
            patern->g[15] = 33;
            patern->g[16] = 18;
            patern->g[17] = 8;
            patern->g[18] = 2;
            patern->g[19] = 1;
            patern->g[20] = 5;
            patern->g[21] = 14;
            patern->g[22] = 27;
            patern->g[23] = 44;
            patern->g[24] = 65;
            patern->g[25] = 87;
            patern->g[26] = 111;
            patern->g[27] = 136;
            patern->g[28] = 161;
            patern->g[29] = 184;
            patern->g[30] = 205;
            patern->g[31] = 223;
            patern->b[0] = 18;
            patern->b[1] = 33;
            patern->b[2] = 51;
            patern->b[3] = 72;
            patern->b[4] = 95;
            patern->b[5] = 120;
            patern->b[6] = 145;
            patern->b[7] = 169;
            patern->b[8] = 192;
            patern->b[9] = 212;
            patern->b[10] = 229;
            patern->b[11] = 242;
            patern->b[12] = 251;
            patern->b[13] = 255;
            patern->b[14] = 254;
            patern->b[15] = 248;
            patern->b[16] = 238;
            patern->b[17] = 223;
            patern->b[18] = 205;
            patern->b[19] = 184;
            patern->b[20] = 161;
            patern->b[21] = 136;
            patern->b[22] = 111;
            patern->b[23] = 87;
            patern->b[24] = 64;
            patern->b[25] = 44;
            patern->b[26] = 27;
            patern->b[27] = 14;
            patern->b[28] = 5;
            patern->b[29] = 1;
            patern->b[30] = 2;
            patern->b[31] = 8;
        break;
        case 3:
            memset(&patern->r[0], r, 31); 
            memset(&patern->g[0], g, 31); 
            memset(&patern->b[0], b, 31);
        break;
    }

    if (staticEND)
    {
        patern->r[31] = r;
        patern->g[31] = g;
        patern->b[31] = b;
    }
}

void writepatch(LED note)
{
    printf("making directory...\n");
    mkdir("/luma", 0777);
    mkdir("/luma/titles", 0777);
    mkdir("/luma/titles/0004013000003502", 0777);

    DIR* dir = opendir("/luma/titles/0004013000003502");
    if (dir)
    {
        // was copied/pasted from https://github.com/Pirater12/CustomRGBPattern/blob/master/main.c and then edited
        printf("writing IPS patch file...\n");

        FILE *file = fopen("/luma/titles/0004013000003502/code.ips", "wb+");

        // https://zerosoft.zophar.net/ips.php for documentation of the IPS file format

        // HEADER (5 BYTES)
        fwrite("PATCH", 5, 1, file);

        // PATCH #1

        // OFFSET (3 BYTES) 0x00A193 real address is 0x10A193
        fputc(0x00, file);
        fputc(0xA1, file);
        fputc(0x93, file);

        // SIZE (2 BYTES)
        fputc(0x00, file);
        fputc(0xC4, file); //  196 BYTES

        // DATA (196 BYTES)

        // 96 BYTES
        fputc(LOOPBYTE, file);
        fwrite(&note, sizeof(note), 1, file);
        // 3 BYTES
        fputc(0xFF, file); // 0x50
        fputc(0xFF, file); // 0x3C
        fputc(LOOPBYTE, file);
        // 96 BYTES
        fwrite(&note, sizeof(note), 1, file);

        // END OF PATCH #1
        // PATCH #2

        // OFFSET (3 BYTES) 0x00A1F7 real address is 0x10A1F7
        fputc(0x00, file);
        fputc(0xA1, file);
        fputc(0xF7, file);

        // SIZE (2 BYTES)
        fputc(0x00, file);
        fputc(0xC4, file); //  196 BYTES

        // DATA (196 BYTES)

        // 96 BYTES
        fputc(LOOPBYTE, file);
        fwrite(&note, sizeof(note), 1, file);
        // 3 BYTES
        fputc(0xFF, file);
        fputc(0xFF, file);
        fputc(LOOPBYTE, file);
        // 96 BYTES
        fwrite(&note, sizeof(note), 1, file);

        // EOF MARKER (3 BYTES)
        fwrite("EOF", 3, 1, file);

        // close file
        fclose(file);

        // check if our file was written
        if( access("/luma/titles/0004013000003502/code.ips", F_OK) != -1 ) 
        {
            printf("success!\n");
        } 
        else 
        {
            printf("failed!\n");
        }

        closedir(dir);
    }
    else if (ENOENT == errno)
    {
        printf("directory failed...\n");
    }
}

// when done we want LUMA to reload so it can patch with our ips patches
// https://www.3dbrew.org/wiki/PTMSYSM:LaunchFIRMRebootSystem
void PTM_RebootAsync() 
{

    ptmSysmInit();

    Handle serviceHandle = 0;
    Result result = srvGetServiceHandle(&serviceHandle, "ptm:sysm");
    if (result != 0) {
        return;
    }

    u32 *commandBuffer = getThreadCommandBuffer();
    commandBuffer[0] = 0x04090080;
    commandBuffer[1] = 0x00000000;
    commandBuffer[2] = 0x00000000;

    svcSendSyncRequest(serviceHandle);
    svcCloseHandle(serviceHandle);

    ptmSysmExit();
}

void listMenu()
{
    iprintf("\x1b[2J");
    printf("\x1b[0;0H\x1b[30;0m");
    printf("===CtrRGBPATTY===\n");
    for (int i = 0; i <= CMDS-1; i++) 
    {
        if (i == selected)
            printf("\x1b[47;30m* %s\x1b[30;0m\n", menu[i].c_str());
        else
            printf("\x1b[30;0m* %s\n", menu[i].c_str());
    }
    printf("=================\n");
   
    printf("COLOR  : %s\n", color_HEX);
    printf("PATERN : %s\n", paterns[selectedpat].c_str());

    if (staticend)
    {
        printf("STATIC : FALSE\n");
    }
    else
    {
        printf("STATIC : TRUE\n");
    }

    if (LOOPBYTE == 0xFF)
    {
        printf("REPEAT : FALSE\n");
    }
    else
    {
        printf("REPEAT : TRUE\n");
    }
}

int main(int argc, char **argv) 
{
    srvInit();
    aptInit();
    gfxInitDefault();
	
    // Init console for text output
    consoleInit(GFX_TOP, NULL);

    selected = 0;
    listMenu();
	
    while (aptMainLoop()) 
    {
        hidScanInput();

        u32 kDown = hidKeysDown();

        if (kDown & KEY_START)
        {
            PTM_RebootAsync();
            break;
        }

        static SwkbdState swkbd;
        static SwkbdStatusData swkbdStatus;
        static SwkbdLearningData swkbdLearning;

       if (kDown & KEY_DDOWN)
        {
            selected=selected+1;
            if (selected>CMDS-1)
                selected = 0;
            listMenu();
        }

        if (kDown & KEY_DUP)
        {
            selected=selected-1;
            if (selected<0)
                selected = CMDS-1;
            listMenu();
        }

        if (kDown & KEY_A)
        {
            switch(selected)
            {
                case 0:
                    swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 3, -1);
                    swkbdSetInitialText(&swkbd, color_HEX);
                    swkbdSetHintText(&swkbd, "Color Hex Code");
                    swkbdSetStatusData(&swkbd, &swkbdStatus, false, true);
                    swkbdSetLearningData(&swkbd, &swkbdLearning, false, true);
                    swkbdInputText(&swkbd, (char*)color_HEX, sizeof(color_HEX));
                    listMenu();
                break;
                case 1:
                    selectedpat=selectedpat+1;
                    if (selectedpat>PATS-1)
                        selectedpat = 0;
                    listMenu();
                break;
                case 2:
                    staticend = !staticend;
                    listMenu();
                break;
                case 3:
                    if (LOOPBYTE == 0xFF)
                        LOOPBYTE = 0x20;
                    else
                        LOOPBYTE = 0xFF;
                    listMenu();
                break;
                case 4:
                    LED notification;
                    createLED(&notification, std::string(color_HEX), false, selectedpat);
                    writepatch(notification);
                break;
                case 5:
                    ptmSysmInit();
                    PTMSYSM_ShutdownAsync(0);
                    ptmSysmExit();
                break;
                default:
                    printf("err\n");
            }
        }

		
        gfxFlushBuffers();
        gfxSwapBuffers();
		gspWaitForVBlank();
    }

    gfxExit();
    aptExit();
    srvExit();
    return 0;
}
