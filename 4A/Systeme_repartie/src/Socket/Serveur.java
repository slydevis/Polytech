package Socket;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Serveur {
    private ServerSocket listenSocket;
    private Socket monSocket;
    private ArrayList<PrintWriter> writers;

    public Serveur() throws IOException {
        listenSocket = new ServerSocket(5000);
        monSocket = listenSocket.accept();
        writers = new ArrayList<>();
    }

    public void read() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(monSocket.getInputStream()));

        PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(monSocket.getOutputStream())));
        writers.add(writer);

        while(true) {
            String str = reader.readLine();
            if(str.equals("END")) {
                writer.println("END");
                break;
            }

            System.out.println("ECHO = " + str);
            writer.println(str);
        }

        reader.close();
        writer.close();
        monSocket.close();
    }

    public static void main(String[] args) throws IOException {
        Serveur server = new Serveur();
        server.read();
    }
}
