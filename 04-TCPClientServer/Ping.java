import java.io.IOException;
import java.net.InetAddress;

public class Ping {
     public static void main(String[] args) {
          String host = "google.com";
          try {
               InetAddress add = InetAddress.getByName(host);
               if (add.isReachable(5000))
                    System.out.println("Ping " + host + " successful!");
               else
                    System.out.println("Ping " + host + " failed!");
          } catch (IOException e) {
               System.out.println("Ping " + host + " failed!");
          }
     }
}