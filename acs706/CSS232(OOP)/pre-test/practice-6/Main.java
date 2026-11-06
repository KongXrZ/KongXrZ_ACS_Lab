
import java.util.Objects;

interface Notifier {
    void send(String message);
}

class EmailNotifier implements Notifier {
    @Override
    public void send(String message) {
        System.out.println("Email: " + message);
    }
}

class SmsNotifier implements Notifier {
    @Override
    public void send(String message) {
        System.out.println("SMS: " + message);
    }
}

class PushNotifier implements Notifier {
    @Override
    public void send(String message) {
        System.out.println("Push: " + message);
    }
}

class AlertService {
    private final Notifier notifier;

    AlertService(Notifier notifier) {
        this.notifier = Objects.requireNonNull(notifier);
    }

    public void alert() {
        notifier.send("Class starts");
    }
}


class RecordingNotifier implements Notifier {
    private String lastMessage;

    @Override
    public void send(String message) {
        this.lastMessage = message;
    }

    public String getLastMessage() {
        return this.lastMessage;
    }
}

public class Main {
    public static void main(String[] args) {
        RecordingNotifier recordingNotifier = new RecordingNotifier();
        AlertService alertService = new AlertService(recordingNotifier);
        alertService.alert();
        System.out.println(recordingNotifier.getLastMessage());
    }
}
