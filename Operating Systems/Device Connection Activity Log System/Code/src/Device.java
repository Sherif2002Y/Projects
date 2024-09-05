import java.io.PrintStream;
class Device extends Thread {
    private final String name;
    private final String type;
    private final Router router;
    private final PrintStream out;

    public Device(String name, String type, Router router, PrintStream out) {
        this.name = name;
        this.type = type;
        this.router = router;
        this.out = out;
    }

    @Override
    public void run() {
        try {
            out.println("- " + name + " (" + type + ") arrived");
            router.connect(name);
            router.performOnlineActivity(name);
            router.disconnect(name);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

