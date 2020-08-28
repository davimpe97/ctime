/*ctime: Simple program for execution time monitoring.
Takes as command line input the partial path of the program to execute (including .\\ and .exe) plus optional arguments.
Returns EXIT_FAILURE if:
-a target program has not been provided;
-the target command line's length exceeds the defined MAXLINE limit;
-the process creation for the target program fails.
Returns EXIT_SUCCESS otherwise.
Compiling in Visual Studio with _UNICODE defined is required for the Unicode variant.
Other compilers are fine for the ASCII version.*/

//Dependencies
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

//Command line length limit
#define MAXLINE 1000

//Additional definitions depending on whether Unicode is required
#ifdef UNICODE
#include <wchar.h>
#else
typedef char TCHAR;
#endif

//Unicode version
#ifdef UNICODE
int wmain(int argc, wchar_t* argv[]) {
    
    //Target check
    if (argc == 1) {
        printf("Usage: ctime <arguments>");
        exit(EXIT_FAILURE);
    }
    wchar_t* command_line = (wchar_t*)malloc(MAXLINE * sizeof(wchar_t));
    size_t command_len = 0;

    //Command line composition from the arguments provided in argv
    for (int i = 1; i < argc; i++) {
        size_t extra_size = wcslen(argv[i]);

        //Length check
        if (command_len + extra_size > MAXLINE) {
            printf("Exceeded max input size");
            exit(EXIT_FAILURE);
        }
        for (size_t j = 0; j < extra_size; j++) {
            command_line[command_len] = (wchar_t)argv[i][j];
            command_len++;
        }
        memset(command_line + command_len, L' ', 1);
        command_len++;
    }
    command_line[command_len] = (TCHAR)'\0';
    wprintf(command_line);
    printf("\n");

    //Further declarations required to create the target process
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    DWORD exit_code;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));
    si.cb = sizeof(si);

    //Timing start
    clock_t delta, end;
    delta = clock();

    //Process creation, check and wait for termination
    if (CreateProcessW(argv[1], command_line, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi) == 0) {
        printf("Process creation failure");
        exit(EXIT_FAILURE);
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    end = clock();
    printf("\n");

    //Target execution check
    GetExitCodeProcess(pi.hProcess, &exit_code);
    if (exit_code == EXIT_FAILURE) {
        printf("Process reported failure\n");
    }
    else {
        printf("Process reported success\n");
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    //Result printing
    double result = ((double)end - (double)delta) / (double)CLOCKS_PER_SEC;
    printf("Execution time: %f seconds", result);
    free(command_line);
    exit(EXIT_SUCCESS);
}

#else
//ASCII version
int main(int argc, char* argv[]){
    
    //Target check
    if(argc == 1){
        printf("Usage: ctime <arguments>");
        exit(EXIT_FAILURE);
    }
    TCHAR* command_line = (TCHAR*)malloc(MAXLINE * sizeof(TCHAR));
    size_t command_len = 0;

    //Command line composition from the arguments provided in argv
    for (int i = 1; i < argc; i++) {
        size_t extra_size = strlen(argv[i]);

        //Length check
        if (command_len + extra_size > MAXLINE) {
            printf("Exceeded max input size");
            exit(EXIT_FAILURE);
        }
        for (size_t j = 0; j < extra_size; j++) {
            command_line[command_len] = (TCHAR)argv[i][j];
            command_len++;
        }
        memset(command_line + command_len, (TCHAR)' ', 1);
        command_len++;
    }
    command_line[command_len] = (TCHAR)'\0';
    printf("%s\n", command_line);

    //Further declarations required to create the target process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exit_code;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));
    si.cb = sizeof(si);

    //Timing start
    clock_t delta, end;
    delta = clock();

    //Process creation, check and wait for termination
    if (CreateProcessA(argv[1], command_line, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi) == 0) {
        printf("Process creation failure");
        exit(EXIT_FAILURE);
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    end = clock();
    printf("\n");

    //Target execution check
    GetExitCodeProcess(pi.hProcess, &exit_code);
    if (exit_code == EXIT_FAILURE) {
        printf("Process reported failure\n");
    }
    else {
        printf("Process reported success\n");
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    //Result printing
    double result = ((double)end - (double)delta)/(double)CLOCKS_PER_SEC;
    printf("Execution time: %f seconds", result);
    free(command_line);
    exit(EXIT_SUCCESS);
}
#endif