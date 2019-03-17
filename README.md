# UDP_Chatting_software
# Chatting software using UDP.

This is a program setting up on 2 computers allowing the client computer to talk to the server computer and vice versa

##Getting Started 

```
This program requires 2 devices that can run windows visual studio with C++ compiler and internet connection. 
```

### List of project files
```
README.md 	:this file
capture.docx	:Traces of the program when its running, including wireshark captured, window netstat command and test run 
UDPclient.ccp	:Client program
UDPserver.ccp	:Server program
```
### Installing
On Client computer
```
Create new C++ Console Application project in Visual Studio
Copy UDPclient.ccp into sources folder
Right click in Solution, select properties.
In Debugging tab, in "Command Argument" property, write down the argument in this format : "Server_address port_number"
You can check the server address by opening cmd ( on window) and use command ipconfig on the server computer
```

On Server computer 
```
Create new C++ Console Application project in Visual Studio
Copy UDPclient.ccp into sources folder
Right click in Solution, select properties.
In Debugging tab, in "Command Argument" property, write down the argument in this format : "port_number"

```


## Running
Start by running the server application and then start the client server. 

## Deployment Note
The pprogram can run by using debugging mode in visual studio

##Authors
Duong Tuan Hiep
