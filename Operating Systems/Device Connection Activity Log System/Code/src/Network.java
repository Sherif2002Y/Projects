import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
public class Network {
    public static void main(String[] args) throws FileNotFoundException {
        PrintStream out = new PrintStream("output.txt");
        Scanner scanner = new Scanner(System.in);
        System.out.println("What is the number of WI-FI Connections?");
        int maxConnections = scanner.nextInt();
        System.out.println("What is the number of devices Clients want to connect?");
        int totalDevices = scanner.nextInt();
        Router router = new Router(maxConnections, out);
        List<Device> devices = new ArrayList<>();
        System.out.println("Enter the name and type of devices:");
        for (int i = 1; i <= totalDevices; i++) {
            String deviceName = scanner.next();
            String deviceType = scanner.next();
            Device device = new Device(deviceName, deviceType, router, out);
            devices.add(device);
        }
        for (Device device : devices) {
            device.start();
        }
        for (Device device : devices) {
            try {
                device.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        scanner.close();
        out.close();
    }
}