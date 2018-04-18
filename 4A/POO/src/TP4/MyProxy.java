package TP4;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.Arrays;
import java.util.Random;

public class MyProxy implements InvocationHandler {
    private Object object;

    MyProxy(Object o) {
        object = o;
    }

    @Override
    public Object invoke(Object o, Method method, Object[] args) throws Throwable {
        System.out.println("Invocation !");
        System.out.println("De " + method.getName() + " avec l'argument " + args[0] + " ici : " + this.object);
        return method.invoke(object, args);
    }

    public static void main(String[] args) {
        Integer[] tab = {9, 10, 1, 2, 3, 4, 5, 6};
        Arrays.sort(tab);

        Proxy[] proxies = new Proxy[1000];

        for (int i = 0; i < proxies.length; ++i)
            proxies[i] = (Proxy) Proxy.newProxyInstance(null, Integer.class.getInterfaces(), new MyProxy(i));

        Random random = new Random();
        int nb = random.nextInt(10);
        System.out.println("\non recherche le chiffre " + nb + " on obtient " + Arrays.binarySearch(proxies, nb));
    }
}
