package Socket;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class ClientSimplifie {
    public BufferedReader lecture;
    public PrintWriter ecriture;
    public Socket sock;

//    "127.0.0.1", 12321
    public ClientSimplifie() throws IOException {
        this.connexionServeur("127.0.0.1", 5000);
    }

    public void connexionServeur(String adresseIpServeur, int portServeur) throws IOException {
        sock = new Socket(adresseIpServeur, portServeur);
        lecture = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        ecriture = new PrintWriter(new OutputStreamWriter(sock.getOutputStream()));
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        ClientSimplifie client = new ClientSimplifie();

        Thread thread = new Thread(() -> {
            Scanner scanner = new Scanner(System.in);
            String str = scanner.nextLine();
            System.out.println("ECRITURE !!! " + str);
            client.ecriture.println(str);
            client.ecriture.flush();
        });

        Thread thread2 = new Thread(() -> {
            while(true) {
                try {
                    String str = client.lecture.readLine();

                    if(str.equals("END"))
                        break;

                    System.out.println("RECEIVED = " + str);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
        thread2.start();

        thread.join();
        thread2.join();
    }
}
