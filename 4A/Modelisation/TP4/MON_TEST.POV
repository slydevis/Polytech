global_settings { assumed_gamma 2.2 }

#include "colors.inc"
#include "shapes.inc"
#include "textures.inc"
#include "glass.inc"
#include "consts.inc"                  // Index of refraction constants

camera {
   location <0.0, 2, -10>
   direction <0.0, 0.0, 1>
   angle 40
   up  <0.0, 1.0, 0.0>
   right <4/3, 0.0, 0.0>
   look_at <0, 0, 0>
   rotate y*-40
}

light_source { <30, 50, -50> color White }

light_source { <-30, 10, 20> color Gray50 }

// Lumière dans le thor
light_source { <1, 1, 0> color White }

difference{    
    cylinder {
        <-1, 0, 0>,     // Center of one end
        <1, 0, 0>,     // Center of other end
        0.5            // Radius
        // open           
        // Remove end caps 
        pigment { Green }
    }


    cylinder {
        <-1.1, 0, 0>,     // Center of one end
        <1.1, 0, 0>,     // Center of other end
        0.5            // Radius
        // open           // Remove end caps  
        scale 0.95
        pigment { Red }
    }

    rotate z*90     // rotation de 50 degrés suivant z
    translate<-1, -1, 0>
}

difference{    
    cylinder {
        <-1, 0, 0>,     // Center of one end
        <1, 0, 0>,     // Center of other end
        0.5            // Radius
        // open           
        // Remove end caps 
        pigment { Green }
    }


    cylinder {
        <-1.1, 0, 0>,     // Center of one end
        <1.1, 0, 0>,     // Center of other end
        0.5            // Radius
        // open           // Remove end caps  
        scale 0.95
        pigment { Red }
    }

    translate<1, 1, 0>
}

difference {
    torus {
        1, 0.5
        rotate -87.5*x
        pigment { Green }
    }

    torus {
        1, 0.45
        rotate -87.5*x
        pigment { Red }
    }

    box {
        <1.5, 0, -1>, <-2, -2, 1>
    }

    box {
        <3.5, 2, -1>, <0, 0, 1>
    }
}

// Jointure
difference {
    cylinder {
        <-1, 0, 0>,
        <-0.4, 0, 0>,
        0.7 // Radius
        pigment { Gold }
    }

    cylinder {
        <-1.1, 0, 0>,
        <-0.3, 0, 0>,
        0.5 // Radius
        pigment { Red }
        rotate x*90
    }

    translate<0.5, 1, 0>
    rotate z*90
}

difference {
    cylinder {
        <-1, 0, 0>,
        <-0.4, 0, 0>,
        0.7 // Radius
        pigment { Gold }
    }

    cylinder {
        <-1.1, 0, 0>,
        <-0.3, 0, 0>,
        0.5 // Radius
        pigment { Red }
        rotate x*90
    }

    translate<1, 1, 0>
}