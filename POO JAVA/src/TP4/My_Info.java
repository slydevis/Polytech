package TP4;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)

public @interface My_Info {
    String Author() default "Guillaume";
    int annee() default 2016;
}
