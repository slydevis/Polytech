package Socket;

import java.io.Serializable;
import java.util.Calendar;

public class Message implements Serializable {
    private String emetteur;
    private String texte;
    private Calendar heure;
}
