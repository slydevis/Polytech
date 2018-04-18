var btn = document.getElementById('allumerBtn');
var img = document.getElementById('myImage');

function interrupteur() {
    if(btn.innerHTML === 'Allumer') {
        btn.innerHTML = 'Eteindre';    
        img.src = 'img/ampoule_allume.png';
    }
    else {
        btn.innerHTML = 'Allumer'
        img.src = 'img/ampoule_eteinte.png';
    }
}

btn.addEventListener('click', interrupteur);