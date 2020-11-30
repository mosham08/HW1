/*  Some example code and prototype - 
    contains many, many problems: should check for return values 
    (especially system calls), handle errors, not use fixed paths,
    handle parameters, put comments, watch out for buffer overflows,
    security problems, use environment variables, etc.
 */
/*
 * Mohammad Abdellatif
 * 1001534657
 * CSE 3320-001
 * Assignment 1
 */
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

int main(void) {
    //pid_t child;
    DIR * d;
    struct dirent * de;
    int c, k;
    char s[256], cmd[256];
    time_t t;

    while (1) {

      t = time( NULL );
      printf("\n\n-----------------------------------------------\n" );
      printf( "\n\nTime: %s\n", ctime( &t ));


      getcwd(s, 200);
      printf( "\nCurrent Directory: %s \n", s);

      d = opendir( "." );
      if (d == NULL)  // checking for errors
    {
        printf("Could not open current directory" );
        return 0;
    }
      c = 0;
      char *directory[10];
      int m = 0;
      while ((de = readdir(d))){
          if ((de->d_type) & DT_DIR) {
             //printf( " ( %d Directory:  %s ) \n", c++, de->d_name);
             directory[m] = (de->d_name);
             m++;
             }
      }
      closedir( d );

      d = opendir( "." );
      if (d == NULL)  // checking for errors
    {
        printf("Could not open current directory" );
        return 0;
    }
      c = 0;
      char *arr[10];
      int i = 0;
      while ((de = readdir(d))){                    
          //if (((de->d_type) & DT_REG))
             //printf( " ( %d File:  %s ) \n", c++, de->d_name);
             arr[i] = (de->d_name);
             i++;

          /*if ( ( c % 5 ) == 0 ) {
             printf( "Hit N for Next\n" );
             k = getchar( );
             }*/
      }
      closedir( d );

      printf("Operations:\n");
      printf("\n\tD Display Directories\n\tF Display Files\n\tE Edit File\n\tR Run A Program\n\tC Change Directory\n\tS Sort Directory listing\n"
             "\tM Move to Directory\n\tR Remove File\n\tQ Quit\n\n");

      printf("\n\nInsert a command from the operations\n");
      c = getchar( ); getchar( );
      switch (c) {
        case 'Q': exit(0); /* quit */
        case 'E': printf( "Edit what?:" );
                  scanf( "%s", s );
                  strcpy( cmd, "pico ");
                  strcat( cmd, s );
                  system( cmd );
                  break;
        case 'R': printf( "Run what?:" );
                  scanf( "%s", cmd );
                  system( cmd );
                  break;
        case 'C': printf( "Change To?:" );
                  scanf( "%s", cmd );
                  chdir( cmd );   
                  break;
        case 'S': printf( "Sort Files by Name or Date?:" );
                  scanf( "%s", cmd );
                  chdir( cmd );
                  break;
        case 'D': printf("\nDisplaying Directory Files:\n");
        for(i = 0; i < 4; i++)
        {
            printf("\nDirectory: %s", directory[i]);
        }
        break;
        case 'F': printf("Files:\n\n");
        for(i = 0; i < 8; i++)
        {
            printf("\nFile: %s", arr[i]);
        }
        break;
      printf( "\n-----------------------------------------\n" );
                  break;
      }
       
    }
}
