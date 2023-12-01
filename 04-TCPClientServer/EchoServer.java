import java.io.*;
import java.net.*;

public class EchoServer {
     public static void main(String[] args) throws IOException {
          ServerSocket serverSocket = null;
          try {
               serverSocket = new ServerSocket(10007);
          } catch (IOException e) {
               System.err.println("Could not listen on port: 10007.");
               System.exit(1);
          }

          Socket clientSocket = null;
          try {
               clientSocket = serverSocket.accept();
          } catch (IOException e) {
               System.err.println("Accept failed.");
               System.exit(1);
          }

          PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
          BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

          String inputLine;
          while ((inputLine = in.readLine()) != null) {
               out.println(inputLine);
          }

          out.close();
          in.close();
          clientSocket.close();
          serverSocket.close();
     }
}