// ICShell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iterator>
#include <sstream>
#include <cerrno>
#include <deque>
#include <signal.h>


using namespace std;

#define EXITCMD "exit"
#define ECHOCMD "echo"

string waitForInput()
{
    string inputLine;
    getline(cin, inputLine);
    int len = inputLine.length();
    if (len == -1)
    {
        printf("ERROR: %s\n", strerror(errno));
        exit(EXIT_SUCCESS);
    }
    return inputLine;
}

deque<string> getArgumentQueue(string inputLine){
    stringstream stream(inputLine);
    deque<string> argv((istream_iterator<string>(stream)), istream_iterator<string>());
    return argv;
}

void doEcho(deque<string> commandQueue)
{
    for(int i = 0; i < commandQueue.size(); i++)
    {
        cout << commandQueue[i] << " ";
    }
    cout << endl;
    return;
}

void commandHandler(deque<string> commandQueue)
{
    string command = commandQueue[0];
    if (strcmp(command.c_str(), ECHOCMD) == 0) 
    {
        commandQueue.pop_front();
        doEcho(commandQueue);
        return;
    }
    else if (strcmp(command.c_str(), EXITCMD) == 0)
    {
        if (commandQueue.size() > 1)
        {
            int exitCode = stoi(commandQueue[1]);
            cout << "Bye" << endl;
            exit(exitCode);
        }
        cout << "Bye" << endl;
        exit(0);
    }
    else
    {
        cout << "Unknown Command!" << endl;
        return;
    }
}

int main(int argc, char *argv[])
{
    string prevInput;
    string inputLine;
    while(true)
    {
        cout << "icsh> ";
        inputLine = waitForInput();
        if (inputLine.empty()) continue;

        if (strcmp(inputLine.c_str(), "!!") == 0) inputLine = prevInput;
        else prevInput = inputLine;

        deque<string> argv = getArgumentQueue(inputLine);
        commandHandler(argv);
    }
    return 0;
}