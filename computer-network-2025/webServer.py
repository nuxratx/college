#tThe objective of this lab is to teach me on how to create a socket, binding socket to a specific address(IP), port(door) AND send/receive HTTP packet. 
#Low level ntworking interface using python socket module. Create a web server that handles one HTTP request at a time 

# import socket module
from socket import *

# In order to terminate the program
import sys


#This is a webServer function 
def webServer(port=13331):
  serverSocket = socket(AF_INET, SOCK_STREAM)  # internet address AF_INET(IPv4), Using TCP prtocol to transport message 
  
  #Prepare a server socket, this line below is a TCP socket object or rather the welcome door 
  serverSocket.bind(("0.0.0.0", port))  #host and port. assigning the port number  to the server's socket. Empty string means
  
  #Fill in start
  serverSocket.listen(1) #the parameter specifies the maximum number of queued connection 
  
  #Fill in end
  print('the server is ready to receive')
  
  while True:
    #Establish the connection
    connectionSocket, addr = serverSocket.accept() #Fill in start -are you accepting connections?     #Fill in end
    print('Got connection from', addr ) 
  
    
    try:
      message = connectionSocket.recv(4096)#Fill in start -a client is sending you a message   #Fill in end 
      filename = message.split()[1]   #what data format does that come in, is your file trying to be
      strfile = filename.decode('utf-8')[1:]
      
      #opens the client requested file. 
      #Plenty of guidance online on how to open and read a file in python. How should you read it though if you plan on sending it through a socket? open a folder in python 
      f = open(strfile) #fill in start #fill in end)
      #fill in end
      outputdata = f.read()
      
      f.close()

      #This variable can store the headers you want to send for any valid or invalid request.   What header should be sent for a response that is ok?    
      #Fill in start 
              
      #Content-Type is an example on how to send a header as bytes. There are more!
      outputdata2 = b'HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: close\r\nServer: Socketserver\r\n\r\n' + bytes(outputdata,'utf-8')  #Missing header line use the RFC in the link , status line 
      

      #Note that a complete header must end with a blank line, creating the four-byte sequence "\r\n\r\n" Refer to https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/TCPSockets.html
 
      #Fill in end
     

               
      #for i in f: #for line in file
      connectionSocket.send(outputdata2)
       
      #Fill in start - append your html file contents #Fill in end 
        
      #Send the content of the requested file to the client (don't forget the headers you created)!
      #Send everything as one send command, do not send one line/item at a time!

      # Fill in start


      # Fill in end
        
      connectionSocket.close() #closing the connection socket
      
    
    except Exception as e:
      # Send response message for invalid request due to the file not being found (404)
      e = b'HTTP/1.1 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n'
      connectionSocket.send(e)
      
      # Remember the format you used in the try: block!
      #Fill in start
       
      #Fill in end


      #Close client socket
      connectionSocket.close()
      #Fill in start
      
      
      #Fill in end

  # Commenting out the below (some use it for local testing). It is not required for Gradescope, and some students have moved it erroneously in the While loop. 
  # DO NOT PLACE ANYWHERE ELSE AND DO NOT UNCOMMENT WHEN SUBMITTING, YOU ARE GONNA HAVE A BAD TIME
  #serverSocket.close()
  #sys.exit()  # Terminate the program after sending the corresponding data

        

if __name__ == "__main__":
  webServer(13331)