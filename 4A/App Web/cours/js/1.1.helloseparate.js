function fctHello() {
    var name = document.getElementById('inName');
    var strToswho = 'Hello World';

    if(name.value) {
        strToswho = ' ' + name.value;
    }

    strToswho += ' !';

    alert(strToswho);
}

document.addEventListener("DOMContentLoaded", function () {
    console.log("DOM loaded");

    var btnHello = document.getElementById('btnHello');
    btnHello.addEventListener('click', fctHello);
});
