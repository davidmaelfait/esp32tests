#include <Preferences.h>

const int MAX_COMMAND_BUFFER = 20;


Preferences pref;

char serial_command_buffer[MAX_COMMAND_BUFFER];

bool appendCharToCharArray( char *array, int n, char c )
{
    int sz = strlen( array );

    if ( sz + 1 < n ) 
    {
        array[sz] = c;
        array[sz + 1] = '\0';
    }       

    return ( sz + 1 < n );
}

void parseCommand(char* cmd, char* param, char* reply)
{

   reply[0] = '\0';

   int cmdIndex = 0;
  if(strcmp(cmd,"SSID"))==0) ///get or set SSID
  {
    
  }
}

void resetBuffer(char* command_buffer)
{
  memset(buffer,0,sizeof(command_buffer));
}

char* captureCommand(char newChar, char* command_buffer,const int maxBuffer)
{
  if(newChar>0 && strlen(buffer)<maxBuffer-1)
  {
     if(c != '\n' && c!='\r')
     {
        appendCharToCharArray(command_buffer,maxBuffer,c);

         if(strlen(command_buffer)>=MAX_SEARCH_PATTERN_LEN-1)
            resetBuffer();
     }
     else
          etxFound=true;
   }

  

   if(etxFound&& strlen(command_buffer)>=2)
      return command_buffer;
    else 
      return NULL;  
}

void evalSerialBuffer(char* result)
{
  if(Serial.available()> 0)
  {
    char* candidateCommand = captureCommand(Serial.read(),serial_command_buffer,MAX_COMMAND_BUFFER);
    
    if(candidateCommand!=NULL)
    {
      char* param = filterParam(candidateCommand);
      parseCommand(command_buffer,param result);

      resetBuffer();
    }
          
   }
}

void writeSerialResult(char* result)
{          
  if(strlen(result)>0)
  {
      strcat(result,"\r\n");
      Serial.write((const uint8_t*)result, strlen(result));
      delay(1);
   }
}


void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
}

void loop() {

  char* result =new char[30];
  
  // put your main code here, to run repeatedly:
  evalSerialBuffer(result);

  if(result!=NULL)
    writeSerialResult(result);
   
   delete[] result;
   result=NULL;
               
}
