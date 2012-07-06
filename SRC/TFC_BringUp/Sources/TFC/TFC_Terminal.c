#include "TFC\TFC.h"


//*****************************************************************
//Terminal Configuration
//*****************************************************************

#define MAX_TERMINAL_LINE_CHARS 64
#define MAX_TERMINAL_CMD_CHARS  32
#define NUM_TERMINAL_CMDS       5

typedef void (*TerminalCallback)(char *);

//These are the terminal command names that map to the callbacks
const char *TerminalCommands[NUM_TERMINAL_CMDS] = {"help","reboot",	"L","vprobe","V"};

void TerminalCmd_Help(char *arg);
void TerminalCmd_Reboot(char *arg);
void TerminalCmd_GetLineScan(char *arg);
void TerminalCmd_vprobe(char *arg);
void TerminalCmd_V(char *arg);
//Populate this array with the callback functions
TerminalCallback TerminalCallbacks[NUM_TERMINAL_CMDS] ={
                                                            TerminalCmd_Help,
                                                            TerminalCmd_Reboot,
                                                            TerminalCmd_GetLineScan,
                                                            TerminalCmd_vprobe,
                                                            TerminalCmd_V
                                                        };

//*****************************************************************
//Plumbing.....
//*****************************************************************


char TerminalLineBuf[MAX_TERMINAL_LINE_CHARS];
uint8_t TerminalPos;
char TerminalCmdBuf[MAX_TERMINAL_CMD_CHARS+1];
char TerminalArgs[MAX_TERMINAL_LINE_CHARS-MAX_TERMINAL_CMD_CHARS];
uint8_t NextCharIn;
uint8_t CmdFound;
 
void TerminalBootMsg()
{

TERMINAL_PRINTF("\r\n\r\n"); 
TERMINAL_PRINTF("***********************************\r\n"); 
TERMINAL_PRINTF("                       /|\r\n"); 
TERMINAL_PRINTF("     ____       __   -- |\r\n");     
TERMINAL_PRINTF("    (___ \\      \\ \\    _|_\r\n");    
TERMINAL_PRINTF("      __) )______\\ \\      \r\n");      
TERMINAL_PRINTF("     / __/(  __  )> \\     \r\n");     
TERMINAL_PRINTF("    | |___ | || |/ ^ \\    \r\n");    
TERMINAL_PRINTF("    |_____)|_||_/_/ \\_\\   \r\n"); 
TERMINAL_PRINTF("                           \r\n");
TERMINAL_PRINTF("TWR-TFC		           \r\n");
TERMINAL_PRINTF("Copyright (C) <2011>  Eli Hughes\r\n");
TERMINAL_PRINTF("Wavenumber LLC\r\n"); 
TERMINAL_PRINTF("***********************************\r\n\r\n>"); 

}

void TFC_InitTerminal()
{
	TerminalPos = 0;
	CmdFound = 0;
    TerminalBootMsg();
}

void TerminalCmd_Help(char *arg)
{
    uint8_t i;

    TERMINAL_PRINTF("\r\n\r\bCommandList:\r\n");
    TERMINAL_PRINTF("----------------------\r\n");

    for(i=0;i<NUM_TERMINAL_CMDS;i++)
    {
         TERMINAL_PRINTF("%s\r\n",TerminalCommands[i]);    
    }

}

void TerminalCmd_Reboot(char *arg)
{
      TerminalBootMsg();
}
uint8_t t;

void TerminalCmd_GetLineScan(char *arg)
{
	uint8_t i;

	//TFC_SetBatteryLED_Level(t++);
	//if(t>4)
	//	t=1;
	
	TERMINAL_PRINTF("\r\nL:");
	
	for(i=0;i<128;i++)
	{
		TERMINAL_PRINTF("%2X,",LineScanImage0[i]);
	}
//	for(i=0;i<128;i++)
//	{
//		TERMINAL_PRINTF("%2X,",LineScanImage1[i]);
//	}
	
	
}


void TerminalCmd_V(char *arg)
{
	uint8_t i,j;

	TFC_SetBatteryLED_Level(t++);
	if(t>4)
		t=1;
	
	TERMINAL_PRINTF("\r\nV:");
	
	
	//for(i=0;i<52;i++)
	//{
		//for(j=0;j<TFC_HORIZONTAL_PIXELS;j++)
	//	{
	//		TERMINAL_PRINTF("%2X,",TFC_NTSC_IMAGE[i*10][j]);
	//	}
//	}
}

void TerminalCmd_vprobe(char *arg)
{
	uint8_t i;
	
	TERMINAL_PRINTF("\r\nE:%dD:%d\r\n",EvenFieldLines,OddFieldLines);
	
}

void TFC_ProcessTerminal()
{
     uint8_t i,j;
     uint8_t ArgsFound;
        
    if(TERMINAL_READABLE)
    {
       NextCharIn = TERMINAL_GETC;
       
        switch(NextCharIn)
        {
            case '\r':
             
             TerminalLineBuf[TerminalPos++] = 0x0;
             TERMINAL_PUTC(NextCharIn);
           
             if(TerminalPos > 1)
             {
                 //find the command
                 i=0;
                 while(TerminalLineBuf[i]>0x20 &&  TerminalLineBuf[i]<0x7f)
                 {
                      TerminalCmdBuf[i] = TerminalLineBuf[i];
                      i++;
    
                    if(i==MAX_TERMINAL_CMD_CHARS)
                        {
                         break;
                        }
                 }
                    
                TerminalCmdBuf[i] = 0;
                TerminalCmdBuf[i+1] = 0;
                
                
                ArgsFound = TRUE;
                memset(TerminalArgs,0x00,sizeof(TerminalArgs));
                //scan for num terminator or next non whitespace
                while(TerminalLineBuf[i]<=0x20 && (i<MAX_TERMINAL_LINE_CHARS))
                {
                    if(TerminalLineBuf[i] == 0x00)
                    {
                    
                        //if we find a NULL terminator before a non whitespace character they flag for no arguments
                        ArgsFound = FALSE;
                        break;
                    }   
                    i++; 
                }
                
                if(ArgsFound == TRUE)
                {
                    strcpy(TerminalArgs,&TerminalLineBuf[i]);
                    
                    //trim trailing whitespace
                    i = sizeof(TerminalArgs)-1;
                    
                    while((TerminalArgs[i]<0x21) && (i>0))
                    {
                        TerminalArgs[i]= 0x00;
                        i--;
                    }       
                }
                
                CmdFound = FALSE;
                for(j=0;j<NUM_TERMINAL_CMDS;j++)
                {           
                    if(strcmp(TerminalCmdBuf,TerminalCommands[j]) == 0)
                    {
                        TERMINAL_PRINTF("\r\n");
                        if(TerminalCallbacks[j] != NULL)
                            TerminalCallbacks[j](TerminalArgs);
                    
                        CmdFound = TRUE;
                        break;
                    }             
                }        
                if(CmdFound == FALSE)
                {
                  TERMINAL_PRINTF("\r\n%s command not recognized.\r\n",TerminalCmdBuf);
                }
              }    
             TERMINAL_PRINTF("\r\n>");
             TerminalPos = 0;
            
            break;
            
            case '\b':
                if(TerminalPos > 0)
                {
                    TerminalPos--;    
                    TERMINAL_PUTC(NextCharIn);
                }
            break;
            
            default:
                
                if(TerminalPos == 0 && NextCharIn == 0x020)
                {
                     //Do nothing if space bar is pressed at beginning of line    
                }
                   else if(NextCharIn >= 0x20 && NextCharIn<0x7F)
                {
                    
                    if(TerminalPos < MAX_TERMINAL_LINE_CHARS-1)
                    {
                         TerminalLineBuf[TerminalPos++] = NextCharIn;
                        TERMINAL_PUTC(NextCharIn);
                    }
                }
            
            break;
        
        }
    }
 
}


