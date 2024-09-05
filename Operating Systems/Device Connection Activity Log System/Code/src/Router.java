import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.io.PrintStream;
class Router {
    private final int maxConnections;
    private final CustomSemaphore semaphore;
    private final Map<Integer, List<String>> connections;
    private final Object connectionsLock = new Object();
    private int nextConnectionId = 1;
    private final PrintStream out;
    public Router(int maxConnections, PrintStream out) {
        this.maxConnections = maxConnections;
        this.semaphore = new CustomSemaphore(maxConnections);
        this.out = out;
        this.connections = new HashMap<>();
    }
    public void connect(String deviceName) throws InterruptedException {
        semaphore.acquire();
        int connectionId = assignConnection();
        synchronized (connectionsLock) {
            List<String> connectionDevices = connections.getOrDefault(connectionId, new ArrayList<>());
            connectionDevices.add(deviceName);
            connections.put(connectionId, connectionDevices);
        }
        out.println("- Connection " + connectionId + ": " + deviceName + " Occupied");
        out.println("- Connection " + connectionId + ": " + deviceName + " log in");
    }

    public void disconnect(String deviceName) {
        int connectionId = findConnectionId(deviceName);
        if (connectionId > 0) {
            synchronized (connectionsLock) {
                List<String> connectionDevices = connections.get(connectionId);
                connectionDevices.remove(deviceName);
                if (connectionDevices.isEmpty()) {
                    connections.remove(connectionId);
                }
            }
            out.println("- Connection " + connectionId + ": " + deviceName + " Logged out");
            semaphore.release();
        }
    }
    public void performOnlineActivity(String deviceName) throws InterruptedException {
        int connectionId = findConnectionId(deviceName);
        if (connectionId > 0) {
            out.println("- Connection " + connectionId + ": " + deviceName + " performs online activity");
            Thread.sleep(new Random().nextInt(5000) + 1000);
        }
    }
    private int assignConnection() {
        synchronized (connectionsLock) {
            int connectionId = nextConnectionId;
            nextConnectionId = (nextConnectionId % maxConnections) + 1;
            return connectionId;
        }
    }

    private int findConnectionId(String deviceName) {
        synchronized (connectionsLock) {
            for (Map.Entry<Integer, List<String>> entry : connections.entrySet()) {
                if (entry.getValue().contains(deviceName)) {
                    return entry.getKey();
                }
            }
        }
        return -1;
    }
}


