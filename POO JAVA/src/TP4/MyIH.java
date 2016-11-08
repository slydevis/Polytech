package TP4;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.Arrays;
import java.util.Random;

@My_Info(annee = 2016)
public class MyIH implements InvocationHandler {
    private Object object;

    public MyIH(Object o) {
        object = o;
    }

    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        System.out.println("Invocation !");
        System.out.println("De " + method.getName() + " avec l'argument " + args[0] + "ici : " + object);
        return method.invoke(object, args);
    }

    public static void main(String[] args) {
        Integer[] tab = {9, 10, 1, 2, 3, 4, 5, 6};
        Arrays.sort(tab);

        Proxy[] proxies = new Proxy[1000];
        Random random = new Random();

        for(int i = 0; i < 1000; ++i)
            proxies[i] = (Proxy) Proxy.newProxyInstance(null, Integer.class.getInterfaces(), new MyIH(i));

        int nb = random.nextInt(1500);
        System.out.println("\non cherche le chiffre " + nb + " on obtient " + Arrays.binarySearch(proxies, nb));
    }
}
